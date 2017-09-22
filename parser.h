#ifndef PARSER_H //header file protectors
#define PARSER_H

#include "lexer.h"



void parser(ifstream &file){
	string getToken();
	LexTok curToken = lexer(file);

	bool accept(string s){
		if (s == curToken){
			curToken = getToken();
			return true;
		}
		else{
			return false;
		}
	}




	void program(){
		expect("program");
		
		if (curToken.token == "Type"){
		
			DeclList();

		}
		else if(curToken.lexeme == "function"){
		
			FuncList();
		}


		expect("begin");
		
		if (curToken.lexeme != "end"){
			
			StmtList();
			
		}
		expect(".");

		cout << "Program => program [DeclList] [FuncList] begin [StmtList] end." << endl;
	}

	void DeclList(){
		
		
		do{
		
			Decl();
		} while (curToken.token == "Type");


		cout << "DeclList => Decl {Decl}" << endl;
	}

	void Decl(){
	
		Type();
		VarList();

		expect(";");
		cout << "Decl => Type VarList ;" << endl;
	}

	void FuncList(){
		
		do{
			Func();
		} while (curToken.lexeme == "function");

		cout << "FuncList =>Func {Func}" << endl;
	}
	void Func(){
		expect("function");
		Ident();

		expect("(");

		if (curToken.lexeme != ")"){
			ParamList();
		}

		expect(")");

		expect(":");
		Type();
		expect(";");

		if (curToken.lexeme != "begin"){
			DeclList();
		}
		expect("begin");
		if (curToken.lexeme != "end"){
			StmtList();

		}
		expect("end");
	
		cout << "function Ident ( [ParamList] ): Type ; [DeclList] begin [StmtList] end " << endl;
	}
	void ParamList(){
	
	
	
	}

	void Ident(){}
}

#endif