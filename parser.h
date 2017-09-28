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
		//cout << "yay" << endl;
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
	if (token.lexeme.compare("function") == 0) {
		FuncList(file, token);
	}

	expect("begin", token, file);

	if ((!(token.lexeme.compare("end"))) == 0) {
		StmtList(file, token);
	}

	expect("end", token, file);

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

//Grace
void FuncList(ifstream& file, LexTok& token) {

	do {
		Func(file, token);
	} while (token.lexeme.compare("function") == 0);

	cout << "FuncList =>Func {Func}" << endl;
}

//Grace
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

//Grace
void ParamList(ifstream& file, LexTok& token) {

	Param(file, token);

	if (token.lexeme.compare(",") == 0) {
		//consume token
		expect(",", token, file);

		Param(file, token);
	}

	/*do {
		Param(file, token);
	} while (token.lexeme.compare(",") == 0);*/

	cout << "ParamList => Param {, Param}" << endl;
}

//Grace
void Param(ifstream& file, LexTok& token) {

	Type(file, token);

	if (token.token.compare("Identifier") == 0)
	{
		token = lexer(file);
	}

	cout << "Param => Type Ident" << endl;
}

//Grace
void Type(ifstream& file, LexTok& token) {

	if (token.lexeme.compare("int") == 0 || token.lexeme.compare("real") == 0 || token.lexeme.compare("string") == 0)
	{
		//consume the token first
		token = lexer(file);
		//then output
		cout << "Type => int | real | string" << endl;
	}
}

//Grace
void VarList(ifstream& file, LexTok& token) {

	if (token.token.compare("Identifier") == 0)
	{
		token = lexer(file);
	}

	//if comma is found, then 
	while (token.lexeme.compare(",") == 0) {
		//consume the token
		token = lexer(file);
		//check if next is another identifier
		if (token.token.compare("Identifier") == 0)
		{
			//get next token
			token = lexer(file);
		}
	}//loop again if ther is a comma following the identifier
	
	cout << "VarList => Ident {,Ident}" << endl;
}

//Grace
void StmtList(ifstream& file, LexTok& token) {

	Stmt(file, token);


	while (token.token.compare("Identifier") == 0 || token.lexeme.compare("read") == 0 || token.lexeme.compare("write") == 0 || token.lexeme.compare("if") == 0 || token.lexeme.compare("while") == 0 || token.lexeme.compare("do") == 0 || token.lexeme.compare("return") == 0) {
		Stmt(file, token);
	}

	
	cout << "StmtList => Stmt{Stmt}" << endl;
}

//Grace
void Stmt(ifstream& file, LexTok& token) {

	if (token.token.compare("Identifier") == 0)
	{
		Assign(file, token);
		cout << "Stmt => Assign" << endl;
	}
	else if (token.lexeme.compare("read") == 0)
	{
		Read(file, token);
		cout << "Stmt => Read" << endl;
	}
	else if (token.lexeme.compare("write") == 0)
	{
		Write(file, token);
		cout << "Stmt => Write" << endl;
	}
	else if (token.lexeme.compare("if") == 0)
	{
		If(file, token);
		cout << "Stmt => If" << endl;
	}
	else if (token.lexeme.compare("while") == 0)
	{
		While(file, token);
		cout << "Stmt => While" << endl;
	}
	else if (token.lexeme.compare("do") == 0)
	{
		Do(file, token);
		cout << "Stmt => Do" << endl;
	}
	else if (token.lexeme.compare("return") == 0)
	{
		Return(file, token);
		cout << "Stmt => Return" << endl;
	}

	//cout << "Stmt => Assign | Read | Write | If | While | Do | Return" << endl;
}

//Grace
void Assign(ifstream& file, LexTok& token) {

	if (token.token.compare("Identifier") == 0)
	{
		token = lexer(file);
	}


	expect(":=", token, file);

	Expr(file, token);

	expect(";", token, file);
	
	cout << "Assign => Ident := Expr;" << endl;
}

//BRIAN 9/25 NOT TESTED
void Read(ifstream& file, LexTok& token) {

	expect("read", token, file);

	expect("(", token, file);

	VarList(file, token);

	expect(")", token, file);

	expect(";", token, file);

	cout << "Read => read ( VarList ) ; " << endl;
}
//Brian 9/25 NOT TESTED
void Write(ifstream& file, LexTok& token) {
	//after consuming write lexeme
	expect("write", token, file);

	expect("(", token, file);

	//keeps on finding an expression as long as the token matches with the comma
	Expr(file, token);

	while (token.lexeme.compare(",") == 0) {
		token = lexer(file);
		Expr(file, token);
	}


	/*do {
		Expr(file, token);
	} while (token.lexeme.compare(",") == 0);*/

	expect(")", token, file);

	expect(";", token, file);
	//output
	cout << "Write => write ( Expr {, Expr} ) ;" << endl;
}

//BRIAN 9/25
void If(ifstream& file, LexTok& token) {
	//assuming if has been consumed



	
	expect("if", token, file);

	expect("(", token, file);

	Cond(file, token); //not complete

	expect(")", token, file);

	expect("begin", token, file);

	StmtList(file, token);

	expect("end", token, file);

	//elseif statements if there are any
	if (token.lexeme.compare("elsif") == 0) {

		do {
			//consume initial elsif
			expect("elsif", token, file);

			expect("(", token, file);

			Cond(file, token); //not complete

			expect(")", token, file);

			expect("begin", token, file);

			StmtList(file, token);

			expect("end", token, file);

		} while (token.lexeme.compare("elsif") == 0);

	}

	//checking for else statement

	if (token.lexeme.compare("else") == 0) {
		//consume else token
		expect("else", token, file);
		expect("begin", token, file);
		StmtList(file, token);
		expect("end", token, file);
	}

	cout << "If => if ( Cond ) begin StmtList end { elsif ( Cond ) begin StmtList end } [else begin StmtList end ]" << endl;
}
void While(ifstream& file, LexTok& token) {
	//consume while token/keyword
	if (token.lexeme.compare("while") == 0) {
		token = lexer(file);
	}

	expect("(", token, file);

	Cond(file, token);

	expect(")", token, file);

	expect("begin", token, file);
	//checks for stmtList if there

	if (token.token.compare("Identifier") == 0 || token.lexeme.compare("read") == 0 || token.lexeme.compare("write") == 0 || token.lexeme.compare("if") == 0 || token.lexeme.compare("while") == 0 || token.lexeme.compare("do") == 0 || token.lexeme.compare("return") == 0) {
		StmtList(file, token);

	}

	expect("end", token, file);


	cout << "While => while ( Cond ) begin [StmtList] end" << endl;
}
//Brian 9/25
void Do(ifstream& file, LexTok& token) {

	//consume do lexeme (will check if implemented)
	expect("do", token, file);

	if (token.token.compare("Identifier") == 0 || token.lexeme.compare("read") == 0 || token.lexeme.compare("write") == 0 || token.lexeme.compare("if") == 0 || token.lexeme.compare("while") == 0 || token.lexeme.compare("do") == 0 || token.lexeme.compare("return") == 0) {
		StmtList(file, token);
	}

	expect("until", token, file);

	expect("(", token, file);

	Cond(file, token);

	expect(")", token, file);

	expect(";", token, file);

	cout << "do => do [StmtList] until ( Cond ) ;" << endl;
}
//Brian 
void Return(ifstream& file, LexTok& token) {

	expect("return", token, file); //token to be consumed

	Expr(file, token);

	expect(";", token, file);

	cout << "Return => return Expr ;" << endl;
}

//Grace
void Cond(ifstream& file, LexTok& token) {

	Expr(file, token);

	RelOp(file, token);

	Expr(file, token);

	cout << "Cond => Expr RelOp Expr" << endl;
}

//Grace
void RelOp(ifstream& file, LexTok& token) {

	//Do we display each one? On his output he doesn't even have this...

	if (token.token.compare("RelOp") == 0)
	{
		//consume lexer
		token = lexer(file);
	//	cout << "RelOp => > | < | >= | <= | = | <> " << endl;
	}

}

//Grace
void Expr(ifstream& file, LexTok& token) {

	Term(file, token);

	if (token.lexeme.compare("+") == 0 || token.lexeme.compare("-") == 0) {
		//consume token
		token = lexer(file);
		//call the factor if it is factor
		Term(file, token);
	}

	cout << "Expr => Term { (+|-) Term }" << endl;
}

//Grace
void Term(ifstream& file, LexTok& token) {

	Factor(file, token);

	if (token.lexeme.compare("*") == 0 || token.lexeme.compare("/") == 0) {
		//consume token
		token = lexer(file);
		//call the factor if it is factor
		Factor(file, token);
	}

	/*do {
		Factor(file, token);
	} while (token.lexeme.compare("*") == 0 || token.lexeme.compare("/") == 0);*/

	cout << "Term => Factor { (*|/) Factor } " << endl;
}

//Grace
void Factor(ifstream& file, LexTok& token) {

	if (token.token.compare("Identifier") == 0)
	{
		token = lexer(file);
		//check if funcCall or Identifiers
		if (token.lexeme.compare("(") == 0) {
			FuncCall(file, token);
			cout << "Factor => FuncCall" << endl;
		}

		else {
			cout << "Factor => Ident" << endl;
		}
	}
	else if (token.token.compare("IntConst") == 0)
	{
		token = lexer(file);
		cout << "Factor => IntConst" << endl;
	}
	else if (token.token.compare("RealConst") == 0)
	{
		token = lexer(file);
		cout << "Factor => RealConst" << endl;
	}
	else if (token.token.compare("StrConst") == 0)
	{
		token = lexer(file);
		cout << "Factor => StrConst" << endl;
	}
	else if (token.lexeme.compare("(") == 0)
	{

		expect("(", token, file);
		Expr(file, token);

		expect(")", token, file);

		cout << "Factor => ( Expr )" << endl;
	}

	////Not sure how to check for this?? MAY have to put it in as a conditional with the 
	//else if (token.token.compare("") == 0)
	//{
	//	//FuncCall(file, token);

	//	cout << "Factor => FuncCall" << endl;
	//}
	//cout << "Factor => Ident | IntConst | RealConst | StrConst | ( Expr ) | FuncCall ";
}

//Grace
void FuncCall(ifstream& file, LexTok& token) {
	//assuming the Identifier lexeme has already been consumed

	expect("(", token, file);

	if ((!token.lexeme.compare(")")) == 0) {
		ArgList(file, token);
	}

	expect(")", token, file);
	
	/*if (token.token.compare("Identifier") == 0)
	{
		expect("(", token, file);

		if ((!token.lexeme.compare(")")) == 0) {
			ArgList(file, token);
		}

		expect(")", token, file);
	}*/

	cout << "Ident ( [ArgList] ) " << endl;
}

//Grace
void ArgList(ifstream& file, LexTok& token) {

	Expr(file, token);

	while(token.lexeme.compare(",") == 0) {
		expect(",", token, file);

		Expr(file, token);
	}

	cout << "Expr { ,Expr} " << endl;
}



#endif