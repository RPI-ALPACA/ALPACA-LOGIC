//LogicGate.h

#ifndef LogicGate_h
#define LogicGate_h

#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>
#include <map>

//typedef std::map<long double, std::pair<char, std::pair<char, char>>> SOMETHING;

class LogicGate {
public:
	bool addStatement(char addState);
	bool removeStatement(char removeState);
	// Likely will not be doing much, more of prototype for GUI to use later
	void asciiDraw();
	bool changeOnOff(char stateName, bool newSwitch);
	void clearStates();
	bool containsState(char checkState);
	// Adding operators
	bool addOperator(char stateOne, char stateTwo, char opAdd);

private:
	std::unordered_map<char, bool> initStatements;
	//std::map<long double, std::pair<char, std::pair<char, char>>>
	//If seen optimizations are found, do not need to go deeper with statement evaluation
	//std::vector<char, bool, bool> pruneOptimize
};

#endif

/*
	Idea: Have Nodes and operation
	Operation orders can be changed -- likely via a tree?
	Give each operator a code number?
*/
