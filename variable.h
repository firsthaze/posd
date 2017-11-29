#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "term.h"
#include <iostream>
using std::string;
using std::vector;

class Variable : public Term {
public:
  Variable(string s):Term(s), _inst(0){}
  string value() {
    if (_inst){
      std::cout << "call real val" << '\n';
      return _inst->value();
    }
    else{
      std::cout << "call symbol" << '\n';
      return Term::value();
    }
  }
  bool match( Term & term ){
    if (this == &term)
      return true;
    if(!_inst){
      _inst = &term ;
      return true;
    }
    return _inst->match(term);
  }
private:
  Term * _inst;
};

#endif
