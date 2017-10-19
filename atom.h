#ifndef ATOM_H
#define ATOM_H
#include "term.h"
#include <string>
using std::string;

class Atom : public Term{
public:
  Atom (string symbol):Term(symbol) {}
  string value(){return this->symbol();}
  bool match(Term *term){
    bool isMatch  = false;
    if(!isdigit(term->symbol().at(0))){         //isNotNumber
      if(isupper(term->symbol().at(0)))        //isVariable
      {
        if(term->isAssignable())
        {

           term->SetValue(this->value());
           term->SetAssignable(false);
           isMatch = true;
        }
        else
        {
          std::cout << "this value" <<this->value();
          if(this->value() == term->value())
          {
            isMatch = true;
          }
        }
      }
      else                                    //isAtom
      {
        if(this->value() == term->value())
          isMatch = true;
        else
          isMatch = false;
      }
    }
    return isMatch;
  }
};

#endif
