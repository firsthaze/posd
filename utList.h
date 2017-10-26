#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;
using std::vector;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List list;
  EXPECT_EQ("[]", list.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number number1(496);
  Number number2(8128);
  List list({&number1,&number2});
  EXPECT_EQ("[496, 8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  List list({&terence_tao, &alan_mathison_turing});
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  List list({&X, &Y});
  EXPECT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number number1(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  List list({&number1, &X, &terence_tao});
  ASSERT_FALSE(list.match(tom));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number number2(8128);
  Number number1(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  List list({&number1, &X, &terence_tao});
  ASSERT_FALSE(list.match(number2));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number number1(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  List list({&number1, &X, &terence_tao});
  vector<Term *> vector1;
  vector1.push_back(&X);
  Struct s1(Atom("s1"),&vector1);
  ASSERT_FALSE(s1.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Number number1(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  List list({&number1, &X, &terence_tao});
  Y.match(list);
  EXPECT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number number1(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  List list({&number1, &X, &terence_tao});
  ASSERT_FALSE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number number1(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  List list1({&number1, &X, &terence_tao});
  List list2({&number1, &X, &terence_tao});
  ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number number1(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  List list1({&number1, &X, &terence_tao});
  List list2({&number1, &Y, &terence_tao});
  ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number number1(496);
  Number number2(8128);
  Variable X("X");
  Atom terence_tao("terence_tao");
  List list1({&number1, &X, &terence_tao});
  List list2({&number1, &number2, &terence_tao});
  list1.match(list2);
  EXPECT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number number1(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  List list1({&number1, &X, &terence_tao});
  Y.match(list1);
  X.match(alan_mathison_turing);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", list1.value());
  EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ("first", l.head()->symbol());
  EXPECT_EQ("[second, third]", l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ("second", l.tail()->head()->value());
  EXPECT_EQ("[third]", l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args1 = {&f};
  List h(args1);
  vector<Term *> args2 = {&h,&s,&t};
  List l(args2);
  EXPECT_EQ("[first]", l.head()->symbol());
  EXPECT_EQ("[second, third]", l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List h(args);
  EXPECT_EQ("third", h.tail()->tail()->head()->symbol());
  EXPECT_EQ("[]", h.tail()->tail()->tail()->symbol());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List list;
  string S;
  try{ list.head();}catch(string s){S = s;}
  EXPECT_EQ("Accessing head in an empty list", S);
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List list;
  string S;
  try{ list.tail();}catch(string s){S = s;}
  EXPECT_EQ("Accessing tail in an empty list", S);
}




#endif
