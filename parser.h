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
void Func(ifstream&, LexTok&);
void ParamList(ifstream&, LexTok&);
void Param(ifstream&, LexTok&);
void Type(ifstream&, LexTok&);
void VarList(ifstream&, LexTok&);
void StmtList(ifstream&, LexTok&);
void Stmt(ifstream&, LexTok&);
void Assign(ifstream&, LexTok&);
void Read(ifstream&, LexTok&);
void Write(ifstream&, LexTok&);
void If(ifstream&, LexTok&);
void While(ifstream&, LexTok&);
void Do(ifstream&, LexTok&);
void Return(ifstream&, LexTok&);
void Cond(ifstream&, LexTok&);
void RelOp(ifstream&, LexTok&);
void Expr(ifstream&, LexTok&);
void Term(ifstream&, LexTok&);
void Factor(ifstream&, LexTok&);
void FuncCall(ifstream&, LexTok&);
void ArgList(ifstream&, LexTok&);


void parser(ifstream &file) {
	LexTok curToken = lexer(file);


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
	else if (token.lexeme.compare("function") == 0) {
		FuncList(file, token);
	}

	expect("begin", token, file);

	if ((!(token.lexeme.compare("end"))) == 0) {
		StmtList(file, token);
	}

	expect(".", token, file);

	cout << "Program => program [DeclList] [FuncList] begin [StmtList] end." << endl;
}

void DeclList(ifstream& file, LexTok& token) {

	do {
		Decl(file, token);
	} while (token.token.compare("Type") == 0);

	cout << "DeclList => Decl {Decl}" << endl;
}

void Decl(ifstream& file, LexTok& token) {

	Type(file, token);

	VarList(file, token);

	expect(";", token, file);

	cout << "Decl => Type VarList ;" << endl;
}


void FuncList(ifstream& file, LexTok& token) {

	do {
		Func(file, token);
	} while (token.lexeme.compare("function") == 0);

	cout << "FuncList =>Func {Func}" << endl;
}

void Func(ifstream& file, LexTok& token) {

	expect("function", token, file);

	if (token.token.compare("Identifier") == 0)
	{
		token = lexer(file);
	}

	expect("(", token, file);

	if ((!token.lexeme.compare(")")) == 0) {
		ParamList(file, token);
	}

	expect(")", token, file);

	expect(":", token, file);

	Type(file, token);

	expect(";", token, file);

	if ((!(token.lexeme.compare("begin"))) == 0) {
		DeclList(file, token);
	}

	expect("begin", token, file);

	if ((!(token.lexeme.compare("end"))) == 0) {
		StmtList(file, token);
	}

	expect("end", token, file);

	cout << "Func => function Ident ( [ParamList] ): Type ; [DeclList] begin [StmtList] end " << endl;
}

void ParamList(ifstream& file, LexTok& token) {

	Param(file, token);

	do {
		Param(file, token);
	} while (token.lexeme.compare(",") == 0);

	cout << "ParamList => Param {, Param}" << endl;
}

void Param(ifstream& file, LexTok& token) {

	Type(file, token);

	//Ident(file, token);

	cout << "Param => Type Ident" << endl;
}

void Type(ifstream& file, LexTok& token) {

	if (token.lexeme.compare("int") == 0 || token.lexeme.compare("real") == 0 || token.lexeme.compare("string") == 0)
	{
		cout << "Type => int | real | string" << endl;
	}
}

void VarList(ifstream& file, LexTok& token) {

	//Ident(file, token);

	do {
		//Ident(file, token);
	} while (token.lexeme.compare(","));

	cout << "VarList => Ident {,Ident}" << endl;
}

void StmtList(ifstream& file, LexTok& token) {

	Stmt(file, token);

	do {
		Stmt(file, token);
	} while (token.token.compare("Identifier") == 0 || token.lexeme.compare("read") == 0 || token.lexeme.compare("write") == 0 || token.lexeme.compare("if") == 0 || token.lexeme.compare("while") == 0 || token.lexeme.compare("do") == 0 || token.lexeme.compare("return") == 0);

	cout << "StmtList => Stmt{Stmt}" << endl;
}

void Stmt(ifstream& file, LexTok& token) {

	if (token.token.compare("Identifier"))
	{
		//Assign(file, token);
	}
	else if (token.lexeme.compare("read"))
	{
		//Read(file, token);
	}
	else if (token.lexeme.compare("write"))
	{
		//Write(file, token);
	}
	else if (token.lexeme.compare("if"))
	{
		//If(file, token);
	}
	else if (token.lexeme.compare("while"))
	{
		//While(file, token);
	}
	else if (token.lexeme.compare("do"))
	{
		//Do(file, token);
	}
	else if (token.lexeme.compare("return"))
	{
		//Return(file, token);
	}

	cout << "Stmt => Assign | Read | Write | If | While | Do | Return" << endl;
}

void Assign(ifstream& file, LexTok& token) {

	//Ident(file, token);

	expect(":=", token, file);

	//Expr(file, token);

	cout << "Assign => Ident := Expr;";
}

//BRIAN 9/25 NOT TESTED
void Read(ifstream& file, LexTok& token){

	expect("(", token, file);

	VarList(file, token);

	expect(")", token, file);
	
	expect(";", token, file);

	cout << "Read => read ( VarList ) ; " << endl;
}
//Brian 9/25 NOT TESTED
void Write(ifstream& file, LexTok& token) {
	//after consuming write lexeme
	expect("(", token, file);

	//keeps on finding an expression as long as the token matches with the comma
	do{
		Expr(file, token);
	} while (token.lexeme.compare(",") == 0);

	expect(")", token, file);

	expect(";", token, file);
	//output
	cout << "Write => write ( Expr {, Expr} ) ;" << endl;
}

//BRIAN 9/25 
void If(ifstream& file, LexTok& token) {
	//assuming if has been consumed

	expect("(", token, file);

	//Cond(file, token); //not complete

	expect(")", token, file);

	expect("begin", token, file);

	StmtList(file, token);

	expect("end", token, file);

	//elseif statements if there are any

	do{
		//consume initial elsif
		expect("(", token, file);

		//Cond(file, token); //not complete

		expect(")", token, file);

		expect("begin", token, file);

		StmtList(file, token);

		expect("end", token, file);
	
	} while (token.lexeme.compare("elsif") == 0);

	//checking for else statement

	if (token.lexeme.compare("else") == 0){
		//consume else token
		expect("begin", token, file);
		StmtList(file, token);
		expect("end", token, file);
	}

	cout << "If => if ( Cond ) begin StmtList end { elsif ( Cond ) begin StmtList end } [else begin StmtList end ]" << endl;
}
void While(ifstream& file, LexTok& token) {
	//consume while token/keyword

	expect("(", token, file);

	//Cond(file, token);

	expect(")", token, file);

	expect("begin", token, file);
	//checks for stmtList if there
	
	if (token.token.compare("Identifier") == 0 || token.lexeme.compare("read") == 0 || token.lexeme.compare("write") == 0 || token.lexeme.compare("if") == 0 || token.lexeme.compare("while") == 0 || token.lexeme.compare("do") == 0 || token.lexeme.compare("return") == 0){
		StmtList(file, token);
		
	}

	expect("end", token, file);


	cout << "While => while ( Cond ) begin [StmtList] end" << endl;
}
//Brian 9/25
void Do(ifstream& file, LexTok& token) {
	
	//consume do lexeme (will check if implemented)

	if (token.token.compare("Identifier") == 0 || token.lexeme.compare("read") == 0 || token.lexeme.compare("write") == 0 || token.lexeme.compare("if") == 0 || token.lexeme.compare("while") == 0 || token.lexeme.compare("do") == 0 || token.lexeme.compare("return") == 0){
		StmtList(file, token);
	}

	expect("until", token, file);

	expect("(", token, file);
	
	//Cond(file, token);
	
	expect(")", token, file);

	expect(";", token, file);
	
	cout << "do => do [StmtList] until ( Cond ) ;" << endl;
}
//Brian 
void Return(ifstream& file, LexTok& token) {
	
	//expect return token to be consumed

	Expr(file, token);

	expect(";", token, file);

	cout << "Return => return Expr ;" << endl;
}
//
//void Cond(ifstream& file, LexTok& token) {
//	cout << "Cond => Expr RelOp Expr" << endl;
//}
//void RelOp(ifstream& file, LexTok& token) {
//	cout << "RelOp => > | < | >= | <= | = | <> " << endl;
//}
//void Expr(ifstream& file, LexTok& token) {
//	cout << "Expr => Term { (+|-) Term }" << endl;
//}
//void Term(ifstream& file, LexTok& token) {
//
//	cout << "Term => Factor { (*|/) Factor } " << endl;
//}
//
//void Factor(ifstream& file, LexTok& token) {
//
//	cout << "Factor => Ident | IntConst | RealConst | StrConst | ( Expr ) | FuncCall ";
//}
//void FuncCall(ifstream& file, LexTok& token) {
//	cout << "Ident ( [ArgList] ) " << endl;
//}
//
//void ArgList(ifstream& file, LexTok& token) {
//
//	cout << "Expr { ,Expr} " << endl;
//}



#endif
