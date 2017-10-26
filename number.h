#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
#include <sstream>
#include "term.h"
using std::string;

std::string double_to_string(double number){
  std::stringstream ss;
  ss << number;
  return ss.str();
}
class Number : public Term{
public:
  Number(double number):Term(double_to_string(number)){}
  string value(){ return this->symbol();}
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
