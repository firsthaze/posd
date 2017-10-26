#ifndef TERM_H
#define TERM_H
#include <string>
#include <vector>

using std::string;
using std::vector;
class Term{
public:
  Term(){}
  Term(string symbol) : _symbol(symbol){}
  vector<Term *> * GetEqualRelation(){ return &_equalRelation;}
  vector<Term *> _equalRelation;
  virtual vector<Term *> *GetElements(){ return NULL;};
  bool IsGetStruct(){return _isGetStruct;}
  virtual string symbol(){return _symbol;}
  virtual string value() = 0;
  virtual bool match(Term *term) = 0;
  bool isAssignable(){ return _assignable;}
  void SetValue(string value){ _value = value;}
  void SetAssignable(bool assignable){ _assignable = assignable;}

protected:
  string const _symbol;
  string _value;
  bool _assignable = false;
  bool _isGetStruct = false;
};
#endif
