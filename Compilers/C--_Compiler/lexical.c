#ifndef LEXICAL_H
	#include "lexical.h"
#endif

#ifndef BASE_H
	#include "base.h"
#endif

int iToken;
int iTokenValue;

int *stCurrentId = NULL;
int *stSymbols;

char *pchSrc, *pchOldSrc;

void InitLex()
{
	stCurrentId = stSymbols = (int *)malloc(BUF_LEN);
	memset(stSymbols, 0, BUF_LEN);
	
	pchSrc = "enum char int if else while return sizeof";
	
	int iTokenTmp = TOK_ENUM;
	while (iTokenTmp <= TOK_SIZEOF) {
		lex();
		stCurrentId[Token] = iTokenTmp++;
	}
	
	pchSrc = pchOldSrc = (char *)malloc(BUF_LEN);
	memset(pchSrc, 0, BUF_LEN);
}

void lex() {
	char *last_pos;
	int hash;

	while (iToken = *pchSrc) {
		++pchSrc;
		
		// parse token here
		if (iToken == '\n') {
			++iLine;
		}
		else if (iToken == '#') {
			// skip macro, because we will not support it
			while (*pchSrc != 0 && *pchSrc != '\n') {
				++pchSrc;
			}
		}
		else if ((iToken >= 'a' && iToken <= 'z') || (iToken >= 'A' && iToken <= 'Z') || (iToken == '_')) {

			// parse identifier
			last_pos = pchSrc - 1;
			hash = iToken;

			while ((*pchSrc >= 'a' && *pchSrc <= 'z') || (*pchSrc >= 'A' && *pchSrc <= 'Z') || (*pchSrc >= '0' && *pchSrc <= '9') || (*pchSrc == '_')) {
				hash = hash * 147 + *pchSrc;
				++pchSrc;
			}

			// look for existing identifier, linear search
			stCurrentId = stSymbols;
			while (stCurrentId[Token]) {
				if (stCurrentId[Hash] == hash && !memcmp((char *)stCurrentId[Name], last_pos, pchSrc - last_pos)) {
					//found one, return
					iToken = stCurrentId[Token];
					return;
				}
				stCurrentId = stCurrentId + IdSize;
			}

			// store new ID
			stCurrentId[Name] = (int)last_pos;
			stCurrentId[Hash] = hash;
			iToken = stCurrentId[Token] = TOK_ID;
			return;
		}
		else if (iToken >= '0' && iToken <= '9') {
			// parse number, three kinds: dec(123) hex(0x123) oct(017)
			iTokenValue = iToken - '0';
			if (iTokenValue > 0) {
				// dec, starts with [1-9]
				while (*pchSrc >= '0' && *pchSrc <= '9') {
					iTokenValue = iTokenValue*10 + *pchSrc++ - '0';
				}
			} else {
				// starts with 0
				if (*pchSrc == 'x' || *pchSrc == 'X') {
					//hex
					iToken = *++pchSrc;
					while ((iToken >= '0' && iToken <= '9') || (iToken >= 'a' && iToken <= 'f') || (iToken >= 'A' && iToken <= 'F')) {
						iTokenValue = iTokenValue * 16 + (iToken & 15) + (iToken >= 'A' ? 9 : 0);
						iToken = *++pchSrc;
					}
				} else {
					// oct
					while (*pchSrc >= '0' && *pchSrc <= '7') {
						iTokenValue = iTokenValue*8 + *pchSrc++ - '0';
					}
				}
			}

			iToken = TOK_NUM;
			return;
		}
		else if (iToken == '"' || iToken == '\'') {
			// parse string literal, currently, the only supported escape
			// character is '\n', store the string literal into data.
			last_pos = pchData;
			while (*pchSrc != 0 && *pchSrc != iToken) {
				iTokenValue = *pchSrc++;
				if (iTokenValue == '\\') {
					// escape character
					iTokenValue = *pchSrc++;
					if (iTokenValue == 'n') {
						iTokenValue = '\n';
					}
				}

				if (iToken == '"') {
					*pchData++ = iTokenValue;
				}
			}

			pchSrc++;
			// if it is a single character, return Num iToken
			if (iToken == '"') {
				iTokenValue = (int)last_pos;
			} else {
				iToken = TOK_NUM;
			}

			return;
		}
		else if (iToken == '/') {
			if (*pchSrc == '/') {
				// skip comments
				while (*pchSrc != 0 && *pchSrc != '\n') {
					++pchSrc;
				}
			} else {
				// divide operator
				iToken = TOK_DIV;
				return;
			}
		}
		else if (iToken == '=') {
			// parse '==' and '='
			if (*pchSrc == '=') {
				pchSrc ++;
				iToken = TOK_EQ;
			} else {
				iToken = TOK_ASSIGN;
			}
			return;
		}
		else if (iToken == '+') {
			// parse '+' and '++'
			if (*pchSrc == '+') {
				pchSrc ++;
				iToken = TOK_INC;
			} else {
				iToken = TOK_ADD;
			}
			return;
		}
		else if (iToken == '-') {
			// parse '-' and '--'
			if (*pchSrc == '-') {
				pchSrc ++;
				iToken = TOK_DEC;
			} else {
				iToken = TOK_SUB;
			}
			return;
		}
		else if (iToken == '!') {
			// parse '!='
			if (*pchSrc == '=') {
				pchSrc++;
				iToken = TOK_NE;
			}
			return;
		}
		else if (iToken == '<') {
			// parse '<=', '<<' or '<'
			if (*pchSrc == '=') {
				pchSrc ++;
				iToken = TOK_LE;
			} else if (*pchSrc == '<') {
				pchSrc ++;
				iToken = TOK_SHL;
			} else {
				iToken = TOK_LT;
			}
			return;
		}
		else if (iToken == '>') {
			// parse '>=', '>>' or '>'
			if (*pchSrc == '=') {
				pchSrc ++;
				iToken = TOK_GE;
			} else if (*pchSrc == '>') {
				pchSrc ++;
				iToken = TOK_SHR;
			} else {
				iToken = TOK_GT;
			}
			return;
		}
		else if (iToken == '|') {
			// parse '|' or '||'
			if (*pchSrc == '|') {
				pchSrc ++;
				iToken = TOK_LOR;
			} else {
				iToken = TOK_OR;
			}
			return;
		}
		else if (iToken == '&') {
			// parse '&' and '&&'
			if (*pchSrc == '&') {
				pchSrc ++;
				iToken = TOK_LAN;
			} else {
				iToken = TOK_AND;
			}
			return;
		}
		else if (iToken == '^') {
			iToken = TOK_XOR;
			return;
		}
		else if (iToken == '%') {
			iToken = TOK_MOD;
			return;
		}
		else if (iToken == '*') {
			iToken = TOK_MUL;
			return;
		}
		else if (iToken == '[') {
			iToken = TOK_BRAK;
			return;
		}
		else if (iToken == '?') {
			iToken = TOK_COND;
			return;
		}
		else if (iToken == '~' || iToken == ';' || iToken == '{' || iToken == '}' || iToken == '(' || iToken == ')' || iToken == ']' || iToken == ',' || iToken == ':') {
			// directly return the character as token;
			return;
		}
	}
	return;
}

void match(int tk)
{
	if (iToken != tk) {
		printf("exprected token: %d, got token: %d", tk, iToken);
		exit(-1);
	}
	lex();
}
