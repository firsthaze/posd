#ifndef NODE_H
#define NODE_H

enum Operators {TERM, SEMICOLON, COMMA, EQUALITY};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):
    payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    if(payload == EQUALITY){
      //std::cout << "left->term->value() :" << left->term->value() << '\n';
      return left->term->match(*(right->term));
    }else if(payload == COMMA){
      bool isLeftTrue = left->evaluate();
      bool isRightTrue = right->evaluate();
      //std::cout << "left is" << isLeftTrue << "right is" << isRightTrue << '\n';
      return (isLeftTrue && isRightTrue);
    }else if(payload == SEMICOLON){
      bool isLeftTrue = left->evaluate();
      bool isRightTrue = right->evaluate();
      return (isLeftTrue || isRightTrue);
    }else{
      //DO NOTHING
    }
  }
  Operators payload;
  Term * term;
  Node * left;
  Node * right;
};

#endif
