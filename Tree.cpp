#include "Tree.h"

StatementParser::StatementParser(){
	head = nullptr;
}

StatementParser::StatementParser(StatementParser& s1, StatementParser& s2) {
	head = new StatementNode();
	head->left = s1.head;
	head->right = s2.head;
	head->connector = '&';
	delete(s1);
	delete(s2);
}

StatementParser::StatementParser(const std::string& statement){
	//this->head = nullptr;
	//split it up
	head = new StatementNode();
	if (statement.find('(') >= 0){

	}
	else{
		if (statement.find('&') >= 0){

		}
		else if(statement.find('|') >= 0){

		}
		else if(statement.find('@') >= 0){

		}
		else{
			if(statement.find('~') >= 0){
				head.negation = true;
			}
			else{
				head.negation = false;
			}
			head.
			head.value = statement;
		}
	}
	
}

void StatementParser::changeHeadValue(const std::string& statement) {
	head->value = statement;
}