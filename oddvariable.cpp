#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "term.h"
#include <iostream>
using std::string;
using std::vector;

class Variable : public Term{
public:
  Variable(string symbol):Term(symbol){ this->SetAssignable(true);}
  string value(){
    vector<Term*>::iterator it;
    for( it = this->GetEqualRelation()->begin(); it != this->GetEqualRelation()->end(); it++){
      if((*it)->IsGetStruct() || (*it)->GetElements())
      {
        return (*it)->value();
      }
    }
    return _value;
  }
  bool match(Term &term){
    bool isMatch  = false;
    if(this->isAssignable())
    {
      if(isupper(term.symbol().at(0)))        //isVariable
      {
        if(!term.isAssignable())              //Variable has value?
        {
          this->SetValue(term.value());
          this->SetAssignable(false);
        }
        else                                   //Variable match with variable
        {
          this->GetEqualRelation()->push_back(this);
          this->GetEqualRelation()->push_back(&term);
          vector<Term*>::iterator it;
          for( it =   this->GetEqualRelation()->begin(); it !=   this->GetEqualRelation()->end(); it++){
            term.GetEqualRelation()->push_back((*it));
          }
        }
      }
      else if(term.symbol().at(0) == '['){
        isMatch = true;
        for(vector<Term*>::iterator it = term.GetElements()->begin(); it != term.GetElements()->end(); it++) {
          if(this->symbol() == (*it)->symbol())
            return false;
        }
        if(isMatch){
          this->SetAssignable(false);
          this->GetEqualRelation()->push_back(&term);
        }
      }
      else                                     //Variable match with atom number struct
      {
        this->SetValue(term.value());
        this->SetAssignable(false);
        this->GetEqualRelation()->push_back(this);
        this->GetEqualRelation()->push_back(&term);
        vector<Term*>::iterator it;
        for( it =   this->GetEqualRelation()->begin(); it !=   this->GetEqualRelation()->end(); it++){
          (*it)->SetValue(term.value());
          (*it)->SetAssignable(false);
        }
      }
      isMatch = true;
    }
    else
    {
      if(this->value() == term.value())
        isMatch = true;
    }
    return isMatch;
  }
};

#endif
