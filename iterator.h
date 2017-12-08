#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include <vector>
using std::vector;
template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class NullIterator : public Iterator<T>{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  T currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};


template <class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct * _s;
};

template <class T>
class ListIterator :public Iterator<T>{
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};

template <class T>
class DFSIterator :public Iterator<T>{
public:
  DFSIterator(T termPointer): _index(0), _termPointer(termPointer){}

  T first(){
    _index = 1;
    DFS(_termPointer);
    for(vector<Term*>::iterator it = _nodes.begin(); it!= _nodes.end(); ++it){
      std::cout << "Here is : " << (*it)->symbol() << '\n';
    }
    _index = 0;
    return _nodes.at(_index);
  }

  T currentItem() const{
    return _nodes.at(_index);
  }

  bool isDone() const{
    return _index >= _termPointer->arity();
  }

  void next(){
    _index++;
  }

private:
  T DFS( T termPointer){
    Iterator<T> * it = termPointer->createIterator();
    for(it->first(); !(it->isDone()); it->next()){
      _nodes.push_back(it->currentItem());
      DFS(it->currentItem());
    }
  }
  int _index;
  T _termPointer;
  vector<T> _nodes;
};
#endif
