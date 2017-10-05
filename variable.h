#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include <iostream>
using std::string;

class Variable : public Term{
public:
  Variable(string symbol):Term(symbol){ this->SetAssignable(true);}
  string value(){ return _value; }
  bool match(Term &term){
    bool isMatch  = false;
    if(this->isAssignable())
    {
      std::cout << "1";
      if(isupper(term.symbol().at(0)))        //isVariable
      {
        std::cout << "2";
        if(!term.isAssignable())              //Variable has value?
        {
          std::cout << "3";
          this->SetValue(term.value());
          this->SetAssignable(false);
        }
      }
      else
      {
        std::cout << "4";
        this->SetValue(term.value());
        this->SetAssignable(false);
      }
      isMatch = true;
    }
    else
    {
      std::cout << "5";
      if(this->value() == term.value())
        isMatch = true;
    }
    return isMatch;
  }
};

#endif
