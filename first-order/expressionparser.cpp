#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <stdlib.h>
#include "expressionparser.h"
using namespace std;

//Fill Constructur In With Any Important Fields To Be Initialized.
//As of right now, we are not making use of any Private Fields.
ExpressionParser::ExpressionParser(){

}

//Determines Whether The Current Input Character = Valid Operator.
bool ExpressionParser::isOperator(char currentOperator){
    return (currentOperator == '&' 
            || currentOperator == '|' 
            || currentOperator == '~'
            || currentOperator == '='
            || currentOperator == '>');
}

//Output The Logical Associativity For Given Operator.
//Default = 'L' Indicating Left Associativity.
char ExpressionParser::getAssociativity(char currentOperator){
    switch(currentOperator){
        case '&':
            return 'L';
        case '|':
            return 'L';
        case '=':
            return 'L';
        case '>':
            return 'L';
        case '~':
            return 'R';  
        default:
            return 'L';
    }
}

//Return The Precedence For Given Operator.
//Used By Shunting Yard Algorithm To Determine Values To Pop From Operator Stack.
//Default = -1.
int ExpressionParser::getPrecedence(char currentOperator){
    switch(currentOperator){
        case '&':
            return 2;
        case '|':
            return 1;
        case '=':
            return 0;
        case '>':
            return 0;
        case '~':
            return 4;
        default:
            return -1;
    }
}

//Simply Removes ' ' From Logical Expressions.
string ExpressionParser::formatInputValue(string currentInput){
    string tempInput = "";
    for(char currentChar : currentInput){
        if(currentChar != ' '){
            tempInput += currentChar;
        }
    }
    return tempInput;
    // char prevOneValue = ' ';
    // char prevTwoValue = ' ';
    // string newFormatInput = "";
    // for(int k=0; k<currentInput.size(); k++){
    //     char currentValue = currentInput[k];
    //     newFormatInput += currentValue;
    //     if(prevOneValue == '-' && currentValue == '>'){
    //         newFormatInput.pop_back();
    //         newFormatInput.pop_back();
    //         newFormatInput += '/';
    //     }
    //     if(prevTwoValue == '<' && prevOneValue == '-' && currentValue == '>'){
    //         newFormatInput.pop_back();
    //         newFormatInput.pop_back();
    //         newFormatInput.pop_back();
    //         newFormatInput += '%';
    //     }
    //     if(!isalpha(currentValue) && !isOperator(currentValue) 
    //         && currentValue != '<' && currentValue != '-' && currentValue != '>' 
    //         && currentValue != '(' && currentValue != ')' && currentValue != ' '){
    //         cout << currentValue << endl;
    //         return "";
    //     }
    //     prevTwoValue = prevOneValue;
    //     prevOneValue = currentValue;
    // }    
    // return newFormatInput;
}

//Below is the Implementation of the Well-Known Shunting Yard Algorithm.
//This Algorithm is described more in detail on the Wiki Pages of the ALPACA-LOGIC Branch.
//Simply, = O(n) Expression Parser For A Given String => Reverse Polish Notation.
string ExpressionParser::runShuntingYardAlgorithm(string inputExpression){
    //Main Output Queue:
    queue<char> outQueue;
    //Main Operator Stack:
    stack<char> opStack;
    //Formats Input String By Removing Any Spaces.
    inputExpression = formatInputValue(inputExpression);
    //Constants For Associativity Values:
    char leftValue = 'L';
    char rightValue = 'R';
    //Constants For Paranthesis Values:
    char leftP = '(';
    char rightP = ')';
    //While There Are More Tokens:
    for(char token: inputExpression){
        //Case 1: Valid Operator.
        if(isOperator(token)){
            while(!opStack.empty() 
                && isOperator(opStack.top())
                && ((getAssociativity(token) == leftValue && getPrecedence(opStack.top()) >= getPrecedence(token))
                    || (getAssociativity(token) ==  rightValue && getPrecedence(opStack.top()) > getPrecedence(token)))) {
                outQueue.push(opStack.top());
                opStack.pop();
            }
            opStack.push(token);   
        }
        //Case 2: Left Paranthesis '('
        else if(token == leftP){
            opStack.push(token);
        }
        //Case 3: Right Paranthesis ')'
        else if(token == rightP) {
            while(!opStack.empty() && opStack.top() != leftP){
                outQueue.push(opStack.top());
                opStack.pop();
            }
            //Error Check For Mismatched Paranthesis:
            //If Stack = Empty w/o Finding a Left Parenthesis, 
            //then there are Mismatched Parentheses => Invalid Expression.
            //"ERROR" = Communication to Client = Tree.cpp To Construct Tree.
            if(opStack.empty()){
                cout << "Error: Mismatched Parentheses." << endl;
                return "ERROR";
            }
            if(opStack.top() == '('){
                opStack.pop();
            }
        }
        else{
            //Error Check For Non-Operator + Non-Alpha Characters:
            //(e.g., Numerical Values, ...)
            if(!isalpha(token)){
                cout << "Error: Invalid Operator." << endl;
                return "ERROR";
            }
            //Append Current Value To Main Output Queue.
            outQueue.push(token);
        }
    }
    //Push Any Remaining Operators Onto Output Queue:
    while(!opStack.empty()){
        //Error Check For Mismatched Paranthesis:
        if(opStack.top() == '(' || opStack.top() == ')'){
            cout << "Error: Mismatched Parentheses." << endl;
            return "ERROR";
        }
        outQueue.push(opStack.top());
        opStack.pop();
    }
    //Format/Set Output Result String By Obtaining All Values From Output Queue.
    string resultValue = "";
    while(!outQueue.empty()) {
        resultValue += outQueue.front();
        outQueue.pop();
    }
    //Return Reverse Polish Notation of Input Expression.
    return resultValue;
}