#ifndef UTTERM_H
#define UTTERM_H

#include "variable.h"
#include "atom.h"
#include "number.h"
#include <iostream>
//test Number.value()
TEST (Number,ctor) {
  Number number1(1);
  ASSERT_EQ("1", number1.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number number1(1);
  ASSERT_EQ("1", number1.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number number1(25);
  Number number2(25);
  EXPECT_TRUE(number1.match(number2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number number1(25);
  Number number2(0);
  EXPECT_FALSE(number1.match(number2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number number1(25);
  Atom tom("tom");
  EXPECT_FALSE(number1.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number number1(25);
  Variable X("X");
  EXPECT_TRUE(number1.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
  Atom tom("tom");
  Number number1(25);
  EXPECT_FALSE(tom.match(number1));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ(tom.value(), X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Atom tom("tom");
  Variable X("X");
  EXPECT_TRUE(X.match(tom));
  EXPECT_TRUE(tom.match(X));
  ASSERT_EQ(X.value(), tom.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable X("X");
  Atom jerry("jerry");
  Atom tom("tom");
  EXPECT_TRUE(X.match(jerry));
  EXPECT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
  Variable X("X");
  Number number1(5);
  EXPECT_TRUE(X.match(number1));
  ASSERT_EQ(X.value(), number1.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Number number1(25);
  Number number2(100);
  Variable X("X");
  EXPECT_TRUE(X.match(number1));
  EXPECT_FALSE(X.match(number2));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Number number1(25);
  Atom tom("tom");
  Variable X("X");
  EXPECT_TRUE(X.match(tom));
  EXPECT_FALSE(X.match(number1));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Number number1(25);
  Atom tom("tom");
  Variable X("X");
  EXPECT_TRUE(tom.match(X));
  EXPECT_FALSE(number1.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Atom tom("tom");
  Variable X("X");
  EXPECT_TRUE(tom.match(X));
  EXPECT_TRUE(X.match(tom));
}
#endif
