#ifndef PARSER_H //header file protectors
#define PARSER_H

#include "lexer.h"

//Function Prototypes
bool accept(string, LexTok&, ifstream&);
void expect(string, LexTok&, ifstream&);
void Program(ifstream&, LexTok&);
void DeclList(ifstream&, LexTok&);
void Decl(ifstream&, LexTok&);
void FuncList(ifstream&, LexTok&);
void Func();
void ParamList();
void Param();
void Type();
void VarList();
void StmtList();
void Stmt();
void Assign();
void Read();
void Write();
void If();
void While();
void Return();
void Cond();
void RelOp();
void Expr();
void Term();
void Factor();
void FuncCall();
void ArgList();




void parser(ifstream &file) {
	LexTok& curToken = lexer(file);

	
	Program(file, curToken);


}

//lexeme check
bool accept(string s, LexTok& check, ifstream &file) {

	//checks the string with the lexeme
	if (s.compare(check.lexeme) == 0) {
		check = lexer(file);
		cout << "yay" << endl;
		return true;
	}
	else {
		return false;
	}
}

void expect(string s, LexTok& check, ifstream &file) {
	if (!accept(s, check, file)) {
		//writeError()
		cout << "ERROR" << endl;
	}

}




void Program(ifstream& file, LexTok& token) {
	expect("program", token, file);

	if (token.token.compare("Type") == 0) {

		DeclList(file, token);

	}
	//else if (curToken.lexeme == "function") {

	//	FuncList();
	//}


	//expect("begin");

	//if (curToken.lexeme != "end") {

	//	StmtList();

	//}
	//expect(".");

	cout << "Program => program [DeclList] [FuncList] begin [StmtList] end." << endl;
}

void DeclList(ifstream& file, LexTok& current) {


	do {

		Decl(file, current);

	} while (current.token == "Type");


	cout << "DeclList => Decl {Decl}" << endl;
}

void Decl(ifstream& file, LexTok& current) {

	//Type();
	//VarList();

	expect(";", current, file);
	cout << "Decl => Type VarList ;" << endl;
}

//
//void FuncList() {
//
//	do {
//		Func();
//	} while (curToken.lexeme == "function");
//
//	cout << "FuncList =>Func {Func}" << endl;
//}
//void Func() {
//	expect("function");
//	Ident();
//
//	expect("(");
//
//	if (curToken.lexeme != ")") {
//		ParamList();
//	}
//
//	expect(")");
//
//	expect(":");
//	Type();
//	expect(";");
//
//	if (curToken.lexeme != "begin") {
//		DeclList();
//	}
//	expect("begin");
//	if (curToken.lexeme != "end") {
//		StmtList();
//
//	}
//	expect("end");
//
//	cout << "Func => function Ident ( [ParamList] ): Type ; [DeclList] begin [StmtList] end " << endl;
//}
//void ParamList() {
//
//
//	cout << "ParamList => Param {, Param}" << endl;
//}
//
//void Param() {
//
//	cout << "Param => Type Ident" << endl;
//}
//void Type() {
//
//	cout << "Type => int | real | string" << endl;
//}
//
//void VarList() {
//
//	cout << "VarList => Ident {,Ident}" << endl;
//}
//
//void StmtList() {
//
//	cout << "StmtList => Stmt{Stmt}" << endl;
//}
//
//void Stmt() {
//
//	cout << "Stmt => Assign | Read | Write | If | While | Do | Return" << endl;
//}
//void Assign() {
//
//	cout << "Assign => Ident := Expr;";
//}
//void Read() {
//
//	cout << "Read => read ( VarList ) ; " << endl;
//}
//
//void Write() {
//
//
//	cout << "Write => write ( Expr {, Expr} ) ;" << endl;
//
//}
//
//void If() {
//
//	cout << "If => if ( Cond ) begin StmtList end { elsif ( Cond ) begin StmtList end } [else begin StmtList end ]" << endl;
//}
//void While() {
//
//
//
//	cout << "While => while ( Cond ) begin [StmtList] end" << endl;
//}
//
//void Do() {
//	cout << "do => do [StmtList] until ( Cond ) ;" << endl;
//}
//
//void Return() {
//
//	cout << "Return => return Expr ;" << endl;
//}
//
//void Cond() {
//	cout << "Cond => Expr RelOp Expr" << endl;
//}
//void RelOp() {
//	cout << "RelOp => > | < | >= | <= | = | <> " << endl;
//}
//void Expr() {
//	cout << "Expr => Term { (+|-) Term }" << endl;
//}
//void Term() {
//
//	cout << "Term => Factor { (*|/) Factor } " << endl;
//}
//
//void Factor() {
//	
//	cout << "Factor => Ident | IntConst | RealConst | StrConst | ( Expr ) | FuncCall ";
//}
//void FuncCall() {
//	cout << "Ident ( [ArgList] ) " << endl;
//}
//
//void ArgList() {
//
//	cout << "Expr { ,Expr} " << endl;
//}



#endif