#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <typeinfo>
#include <string>
#include "variable.h"

using std::string;
template <class T>
class Iterator;
class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom & name() {
    return _name;
  }
  string symbol() {
    if(_args.empty())
    return  _name.symbol() + "()";
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+")";
    return ret;
  }

  string value() {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
  int arity()  {return _args.size();}
  Iterator<Term*> * createIterator();
  Iterator<Term*> * createDFSIterator();
  bool match(Term &term){
    if (typeid(term) ==  typeid(Variable))
      return term.match(*this);
    else
      return symbol() == term.symbol();
  }
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
