#ifndef TERM_H
#define TERM_H
#include <string>

using std::string;
class Term{
public:
  Term(string symbol) : _symbol(symbol){}
  string symbol(){return _symbol;}
  virtual string value() = 0;
  virtual bool match(Term &term) = 0;
  bool isAssignable(){ return _assignable;}
  void SetValue(string value){ _value = value;}
  void SetAssignable(bool assignable){ _assignable = assignable;}

protected:
  string const _symbol;
  string _value;
  bool _assignable = false;
};
#endif
