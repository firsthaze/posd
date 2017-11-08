#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        _scanner.nextToken() ;
        vector<Term*> terms = getArgs();
        if(_currentToken == ')')
          return new Struct(*atom, terms);
      }
      else
        return atom;
    }else if(token == LIST){
        if(_scanner.currentChar() == ']')
        {
          std::cout << "end of list --";
          List *list = new List;
          _scanner.nextToken();
          return list;
        }
          vector<Term*> terms = getArgs();
          if(_currentToken == ')'){
            std::cout << "into error";
            throw std::string("unexpected token");
          }else
            return new List(terms);
    }
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    //std::cout << "into getArgs --";
    Term* term = createTerm();
    vector<Term*> args;
    if(term){
      std::cout << "term is created --";
      args.push_back(term);
    }
    while((_currentToken = _scanner.nextToken()) == ',' || _scanner.currentChar() == ']') {
      std::cout << "into while --";
      args.push_back(createTerm());
    }
    return args;
  }



private:
  Scanner _scanner;
  int _currentToken;
};
#endif
