#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include <vector>
#include <queue>
using std::vector;
using std::queue;
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
  DFSIterator(T termPointer): _index(1), _termPointer(termPointer){}

  void first(){
    _index = 1;
    DFS(_termPointer);
    for(vector<Term*>::iterator it = _nodes.begin(); it!= _nodes.end(); ++it){
      std::cout << "Here is : " << (*it)->symbol() << '\n';
    }
    _index = 0; // 回傳nodes 抓currentIterm用
  }

  T currentItem() const{
    return _nodes.at(_index);
  }

  bool isDone() const{
    return _index >= _nodes.size();
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

template <class T>
class BFSIterator :public Iterator<T>{
public:
  BFSIterator(T termPointer): _index(1), _termPointer(termPointer){}

  void first(){
    _index = 1;
    BFS(_termPointer);
    for(vector<Term*>::iterator it = _nodes.begin(); it!= _nodes.end(); ++it){
      std::cout << "Here is : " << (*it)->symbol() << '\n';
    }
    _index = 1; // 回傳nodes 抓currentIterm用
  }

  T currentItem() const{
    return _nodes.at(_index);
  }

  bool isDone() const{
    return _index >= _nodes.size();
  }

  void next(){
    _index++;
  }

private:
  T BFS( T termPointer){
    queue<T> queForNotVisit;
    queForNotVisit.push(termPointer);

    while(!queForNotVisit.empty()){
      _nodes.push_back(queForNotVisit.front());
      Iterator<T> * it = queForNotVisit.front()->createIterator();
      for(it->first();!(it->isDone());it->next()){
        queForNotVisit.push(it->currentItem());
      }
      queForNotVisit.pop();
    }
  }
  int _index;
  T _termPointer;
  vector<T> _nodes;
};
#endif
