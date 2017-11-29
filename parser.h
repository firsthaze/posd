#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <algorithm>
#include <stack>
using std::string;
using std::stack;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == LIST){
      return list();
    }

    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  Node* matchings(){
    getAllNode();
    reverseToPreorder();
    connectNode();
  }

  Node * expressionTree(){
    return _expressionTree;
  }

  void getAllNode(){
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      Node * firstNode = new Node(TERM, term, 0, 0);
      checkNodeSymbolExist(firstNode);
      nodes.push_back(firstNode);
      while((_currentToken = _scanner.nextToken()) == ',' || _currentToken == ';' || _currentToken == '=') {
        Node * node;
        if(_currentToken == ',')
          node = new Node(COMMA);
        else if(_currentToken == ';'){
          node = new Node(SEMICOLON);
          IndexOfNodesTable++;
        }
        else if(_currentToken == '=')
          node = new Node(EQUALITY);
        else{}
        nodes.push_back(node);
        Term * newTerm = createTerm();
        _terms.push_back(newTerm);
        Node * newNode = new Node(TERM, newTerm, 0, 0);
        checkNodeSymbolExist(newNode);
        nodes.push_back(newNode);
      }
    }
  }

  void checkNodeSymbolExist(Node* node){
    bool isExist = false;
    if(node->term->IsGetStruct()){
      Struct * ps = dynamic_cast<Struct *>(node->term);
      for(int i=0; i < ps->arity(); i++){
        Node * node = new Node(TERM, ps->args(i), 0, 0);
        checkNodeSymbolExist(node);
      }
    }else{
      for(vector<Node*>::iterator it = nodesTable[IndexOfNodesTable].begin(); it !=  nodesTable[IndexOfNodesTable].end(); ++it){
        if(node->term->symbol() == (*it)->term->symbol()){
          (*it)->term->match(*(node->term));
          isExist = true;
        }
      }
      if(!isExist)
        nodesTable[IndexOfNodesTable].push_back(node);
    }
  }

  void reverseToPreorder(){
    vector<Node*> tempNodes;
    stack<Node *> stackForPreOrder;
    int i=0;
    for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it){
      i++;
      if((*it)->payload == TERM){
        tempNodes.push_back((*it));
      }
      else{
        if(stackForPreOrder.empty()){
          stackForPreOrder.push((*it));
        }
        else{
          while(!stackForPreOrder.empty() && (*it)->payload < stackForPreOrder.top()->payload){
            tempNodes.push_back(stackForPreOrder.top());
            stackForPreOrder.pop();
          }
          stackForPreOrder.push((*it));
        }
      }
      if(i == nodes.size()){
        while(!stackForPreOrder.empty()){
            tempNodes.push_back(stackForPreOrder.top());
            stackForPreOrder.pop();
        }
      }
    }
    nodes.clear();
    nodes = tempNodes;
  }

  void connectNode(){
    stack<Node *> stackForPreOrder;
    for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it){
      switch ((*it)->payload) {
        case TERM :
        {
          stackForPreOrder.push((*it));
        }
        break;
        case EQUALITY:
        case COMMA:
        case SEMICOLON :
        {
          Node* left;
          Node* right;
          right = stackForPreOrder.top();
          stackForPreOrder.pop();
          left = stackForPreOrder.top();
          stackForPreOrder.pop();
          (*it)->left = left;
          (*it)->right = right;
          stackForPreOrder.push((*it));
        }
        break;
      }
      _expressionTree = (*it);
    }
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }
  vector<Node*> nodesTable[10];
  int IndexOfNodesTable=0;
  vector<Node*> nodes;
  Node * _expressionTree;
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
};
#endif
