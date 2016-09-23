#ifndef LEXICAL_H
#define LEXICAL_H

#ifndef BASE_H
	#include "base.h"
#endif

enum {
	TOK_NUM = 128, // [0-9]+
	TOK_ID,        // [A-z][A-z_0-9]*
	TOK_ENUM,      // "enum"
	TOK_CHAR,      // "char"
	TOK_INT,       // "int"
	TOK_IF,        // "if"
	TOK_ELSE,      // "else"
	TOK_WHILE,     // "while"
	TOK_RETURN,    // "return"
	TOK_SIZEOF,    // "sizeof"
	TOK_ASSIGN,    // "="
	TOK_COND,      // "?"
	TOK_LOR,       // "|"
	TOK_LAN,       // "&"
	TOK_OR,        // "||"
	TOK_XOR,       // "^"
	TOK_AND,       // "&&"
	TOK_EQ,        // "=="
	TOK_NE,        // "!="
	TOK_LT,        // "<"
	TOK_GT,        // ">"
	TOK_LE,        // "<="
	TOK_GE,        // ">="
	TOK_SHL,       // "<<"
	TOK_SHR,       // ">>"
	TOK_ADD,       // "+"
	TOK_SUB,       // "-"
	TOK_MUL,       // "*"
	TOK_DIV,       // "/"
	TOK_MOD,       // "%"
	TOK_INC,       // "++"
	TOK_DEC,       // "--"
	TOK_BRAK       // "["
// ~ , : ; ( ) ] { }
};

enum {
	TYPE_CHAR,
	TYPE_INT,
	TYPE_PTR
};

enum {
	CLASS_FUN,     // user defined function
	CLASS_SYS,     // built-in function
	CLASS_GLO,     // global variable
	CLASS_LOC,     // local variable
};

enum {
	Token,   // Id, Char, Int, ...
	Hash,    //
	Name,    //
	Type,    // INT, CHAR, PTR
	Class,   // local, global, fun, sys
	Value,   // value or address
	BType,   // BXxx used for global id while local id and global id are all existed
	BClass,
	BValue,
	IdSize   // size of symbol unit
};

extern int iToken;
extern int iTokenValue;

extern char *pchSrc, *pchOldSrc;

extern int *stCurrentId;
extern int *stSymbols;

extern void InitLex();
extern void lex();

#endif