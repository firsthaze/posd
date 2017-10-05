#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
#include "term.h"
using std::string;

class Number : public Term{
public:
  Number(int number):Term(std::to_string(number)){}
  string value(){return this->symbol();}
  bool match(Term &term){
    bool isMatch  = false;
    if(isdigit(term.symbol().at(0))){         //isNumber
      isMatch = this->value().compare(term.value());
    }
    else
    {
      if(isupper(term.symbol().at(0)))        //isVariable
      {
        if(term.isAssignable()){
           term.SetValue(this->value());
           term.SetAssignable(false);
           isMatch = true;
        }
      }
      //isAtom = false
      return isMatch;
    }
  }

private:
};

#endif
