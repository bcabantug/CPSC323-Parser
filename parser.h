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
	
		cout << "Func => function Ident ( [ParamList] ): Type ; [DeclList] begin [StmtList] end " << endl;
	}
	void ParamList(){
	
	
		cout << "ParamList => Param {, Param}" << endl;
	}

	void Param(){
		
		cout << "Type Ident" << endl;
	}
	void Type(){
		
		cout << "Type => int | real | string" << endl;
	}

	void VarList(){
		
		cout << "VarList => Ident {,Ident}" << endl;
	}

	void StmtList(){
	
		cout << "StmtList => Stmt{Stmt}" << endl;
	}

	void Stmt(){
	
		cout << "Assign | Read | Write | If | While | Do | Return" << endl;
	}
	void Assign(){
	
		cout << "Assign => Ident := Expr;"
	}
	void Read(){
	
		cout << "Read => read ( VarList ) ; " << endl;
	}

	void Write(){
		

		cout << "read ( VarList ) ;" << endl;
	
	}

	void If(){
		
		cout << "if ( Cond ) begin StmtList end { elsif ( Cond ) begin StmtList end } [else begin StmtList end ]" << endl;
	}
	void While(){



		cout << "while ( Cond ) begin [StmtList] end" << endl;
	}

	void Do(){
		cout << "do [StmtList] until ( Cond ) ;" << endl;
	}

	void Return(){
	
		cout << "return Expr ;" << endl;
	}

	void Cond(){
		cout << "Expr RelOp Expr" << endl;
	}
	void RelOp(){
		cout << "> | < | >= | <= | = | <> " << endl;
	}
	void Expr(){
		cout << "Term { (+|-) Term }" << endl;
	}
	void Term(){
	
		cout << "Factor { (*|/) Factor } " << endl;
	}
	void FuncCall(){
		cout << "Ident ( [ArgList] ) " << endl;
	}

	void ArgList(){
		
		cout << "Expr { ,Expr} " << endl;
	}




	
}

#endif