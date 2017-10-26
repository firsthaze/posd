#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List (): Term("[]"), _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  vector<Term *> *GetElements(){ return &_elements;}
  Term * head(){
    if(_elements.size() == 0){
      throw std::string("Accessing head in an empty list");
    }
    else{
      vector<Term*>::iterator it = _elements.begin();
      return (*it);
    }
  }
  List * tail(){
    if(_elements.size() == 0){
      throw std::string("Accessing tail in an empty list");
    }
    else{
      vector<Term *> args;
      vector<Term*>::iterator it = _elements.begin()+1;
      for(it; it != _elements.end(); ++it){
        args.push_back(*it);
      }
      List * tailList = new List(args);
      return tailList;
    }
  }
  string symbol(){
    string ret = "[";
    if(_elements.size() == 0){
      ret += "]";
    }
    else{
      for(int i = 0; i < _elements.size()-1 ; i++)
        ret += _elements.at(i)-> symbol() + ", ";
      ret += _elements.at(_elements.size()-1)-> symbol() + "]";
    }
    return  ret;
  }
  string value(){
    string ret = "[";
    if(_elements.size() == 0)
      ret += "]";
    else{
      for(int i = 0; i < _elements.size() - 1 ; i++){
        if(_elements.at(i)->value() != "")
          ret += _elements.at(i)->value() + ", ";
        else
          ret += _elements.at(i)->symbol() + ", ";
      }
      if(_elements.at(_elements.size()-1)->value() != ""){        //is value have string
          ret += _elements.at(_elements.size()-1)-> value () + "]";
      }
      else{
          ret += _elements.at(_elements.size()-1)-> symbol () + "]";
      }
    }
    return  ret;
  }
  bool match(Term * term){
    bool isMatch = true;
    if(term->GetElements()){
      int i =0;
      for(vector<Term*>::iterator it = term->GetElements()->begin(); it != term->GetElements()->end(); it++){
        if((*it)->value() != this->_elements.at(i)->value()){
          if((*it)->isAssignable())
            (*it)->SetValue(this->_elements.at(i)->value());
          else if(this->_elements.at(i)->isAssignable())
            this->_elements.at(i)->SetValue((*it)->value());
          else
            isMatch = false;
        }
        i++;
      }
    }
    else if(term->value() == this->value())
      isMatch = true;
    else
      isMatch = false;
    return isMatch;
  }

private:
  vector<Term *> _elements;
};

#endif
