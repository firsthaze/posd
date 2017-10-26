#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>
#include "term.h"
using std::string;

class Struct:public Term
{
public:
  Struct(Atom const & name, std::vector<Term *> *args):_name(name), _args(args) { this->_isGetStruct = true;
  }

  string value(){
    string ret = _name.symbol() + "(";
    for(int i = 0; i < _args->size() - 1 ; i++){
      if(_args->at(i)->value() != "")
        ret += _args->at(i)->value() + ", ";
      else
        ret += _args->at(i)->symbol() + ", ";
    }
    if(_args->at(_args->size()-1)->value() != ""){        //is value have string
        ret += _args->at(_args->size()-1)-> value () + ")";
    }
    else{
        ret += _args->at(_args->size()-1)-> symbol () + ")";
    }
    return  ret;
  }

  Term * args(int index) {
    return _args->at(index);
  }

  Atom * name() {
    return &_name;
  }
  string symbol(){
    string ret = _name.symbol() + "(";
    for(int i = 0; i < _args->size()-1 ; i++){
      ret += _args->at(i)-> symbol() + ", ";
    }
    ret += _args->at(_args->size()-1)-> symbol() + ")";
    return  ret;
  }

  bool match(Term &term){
    if (term.IsGetStruct()){
      Struct * ps = dynamic_cast<Struct *>(&term);
      if (!this->_name.match(*(ps->name())))
        return false;
      if(_args->size()!= ps->_args->size())
        return false;
      for(int i=0;i<_args->size();i++){
        if(_args->at(i)->symbol() != ps->_args->at(i)->symbol())
            return false;
      }
      return true;
    }
    return false;
  }
private:
  Atom _name;
  std::vector<Term *> *_args;
};

#endif
