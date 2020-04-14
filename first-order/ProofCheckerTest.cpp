#include <iostream>
#include <string>
#include "ProofChecker.h"
#include "FirstOrderTree.h"

int main(int argc, char* argv[]){
    // Test AND Intro
    ProofChecker expression = new ProofChecker("A & B");
    expression.addChild(new FirstOrderTree("A"));
    expression.addChild(new FirstOrderTree("B"));
    std::cout << "Result of AND Intro (A, B) => A & B: " + expression.check();

    // Test AND Elim
    expression = new ProofChecker("A");
    expression.addChild(new FirstOrderTree("A & B"));
    std::cout << "Result of AND Elim (A & B) => A: " + expression.check();

    // Test OR Intro
    expression = new ProofChecker("A | B");
    expression.addChild(new FirstOrderTree("A"));
    std::cout << "Result of OR Intro (A) => A | B: " + expression.check();

    // OR Elim and NOT Intro cannot be tested yet, as we have not figured out how to represent
    // subproofs

    // Test NOT Elim
    expression = new ProofChecker("A");
    expression.addChild(new FirstOrderTree("~~A"));
    std::cout << "Result of expression Intro (~~A) => A: " + expression.check();

    // IF Intro cannot be tested yet, as we have not figured out how to represent
    // subproofs

    // Test IF Elim
    expression = new ProofChecker("A > B");
    expression.addChild(new FirstOrderTree("A"));
    std::cout << "Result of expression Intro (A > B) => B: " + expression.check();

    // Test IFF Intro
    expression = new ProofChecker("A = B");
    expression.addChild(new FirstOrderTree("A > B"));
    expression.addChild(new FirstOrderTree("B > A"));
    std::cout << "Result of expression Intro (A > B, B > A) => A = B: " + expression.check();

    // Test IFF Elim
    expression = new ProofChecker("A");
    expression.addChild(new FirstOrderTree("A = B"));
    expression.addChild(new FirstOrderTree("B"));
    std::cout << "Result of expression Intro (A = B, B) => A: " + expression.check();


    // Tests for quantifiers have not yet been written, as it has not been decided
    // what the symbols for forall expression exists will be; thus, writing tests for these
    // is impossible.
}