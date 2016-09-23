#ifndef EXPRESSION_H
	#include "expression.h"
#endif

#ifndef BASE_H
	#include "base.h"
#endif

#ifndef LEXICAL_H
	#include "lexical.h"
#endif

int iExprType;

// unit_unary ::= unit | unit unary_op | unary_op unit
// expr ::= unit_unary (bin_op unit_unary ...)
void expression(int level)
{
	// unit_unary()
	int *id;
	int tmp;
	int *addr;
	{
		if (!iToken) {
			// EOF
			exit(-1);
		}
		if (TOK_NUM == iToken) {
			match(TOK_NUM);
			
			*++text = IMM; // 立即数
			*++text = iTokenValue;
			iExprType = TYPE_INT;
		}
		else if ('"' == iToken) {
			*++piText = IMM;
			*++piText = iTokenValue;
			
			match('"');
			
			while ('"' == iToken) {
				match('"');
			}
			
			pchData = (char *)((int)pchData + sizeof(int));
			iExprType = PTR;
		}
		else if (TOK_SIZEOF == iToken) {
			match(TOK_SIZEOF);
			match('(');
			iExprType = TYPE_INT;
			
			if (TOK_INT == iToken) {
				match(TOK_INT);
			} 
			else if (TOK_CHAR == iToken) {
				match(TOK_CHAR);
			}
		}
	}
}