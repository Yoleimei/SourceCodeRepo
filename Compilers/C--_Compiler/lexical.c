enum {
	TOK_NUM = 128, // [0-9]+
	TOK_ID,        // [A-z][A-z_0-9]*
	TOK_CHAR,      // "char"
	TOK_ELSE,      // "else"
	TOK_ENUM,      // "enum"
	TOK_IF,        // "if"
	TOK_INT,       // "int"
	TOK_RETURN,    // "return"
	TOK_SIZEOF,    // "sizeof"
	TOK_WHILE,     // "while"
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
}

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

void next() {
	char *last_pos;
	int hash;

	while (token = *src++) {

	   // parse token here
	   if (token == '\n') {
		   ++line;
	   }
	   else if (token == '#') {
		   // skip macro, because we will not support it
		   while (*src != 0 && *src != '\n') {
			   ++src;
		   }
	   }
	   else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_')) {

		   // parse identifier
		   last_pos = src - 1;
		   hash = token;

		   while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || (*src == '_')) {
			   hash = hash * 147 + *src;
			   ++src;
		   }

		   // look for existing identifier, linear search
		   current_id = symbols;
		   while (current_id[Token]) {
			   if (current_id[Hash] == hash && !memcmp((char *)current_id[Name], last_pos, src - last_pos)) {
				   //found one, return
				   token = current_id[Token];
				   return;
			   }
			   current_id = current_id + IdSize;
		   }

		   // store new ID
		   current_id[Name] = (int)last_pos;
		   current_id[Hash] = hash;
		   token = current_id[Token] = Id;
		   return;
		}
		else if (token >= '0' && token <= '9') {
			// parse number, three kinds: dec(123) hex(0x123) oct(017)
			token_val = token - '0';
			if (token_val > 0) {
				// dec, starts with [1-9]
				while (*src >= '0' && *src <= '9') {
					token_val = token_val*10 + *src++ - '0';
				}
			} else {
				// starts with 0
				if (*src == 'x' || *src == 'X') {
					//hex
					token = *++src;
					while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
						token_val = token_val * 16 + (token & 15) + (token >= 'A' ? 9 : 0);
						token = *++src;
					}
				} else {
					// oct
					while (*src >= '0' && *src <= '7') {
						token_val = token_val*8 + *src++ - '0';
					}
				}
			}

			token = Num;
			return;
		}
		else if (token == '"' || token == '\'') {
			// parse string literal, currently, the only supported escape
			// character is '\n', store the string literal into data.
			last_pos = data;
			while (*src != 0 && *src != token) {
				token_val = *src++;
				if (token_val == '\\') {
					// escape character
					token_val = *src++;
					if (token_val == 'n') {
						token_val = '\n';
					}
				}

				if (token == '"') {
					*data++ = token_val;
				}
			}

			src++;
			// if it is a single character, return Num token
			if (token == '"') {
				token_val = (int)last_pos;
			} else {
				token = Num;
			}

			return;
		}
		else if (token == '/') {
			if (*src == '/') {
				// skip comments
				while (*src != 0 && *src != '\n') {
					++src;
				}
			} else {
				// divide operator
				token = Div;
				return;
			}
		}
		else if (token == '=') {
			// parse '==' and '='
			if (*src == '=') {
				src ++;
				token = Eq;
			} else {
				token = Assign;
			}
			return;
		}
		else if (token == '+') {
			// parse '+' and '++'
			if (*src == '+') {
				src ++;
				token = Inc;
			} else {
				token = Add;
			}
			return;
		}
		else if (token == '-') {
			// parse '-' and '--'
			if (*src == '-') {
				src ++;
				token = Dec;
			} else {
				token = Sub;
			}
			return;
		}
		else if (token == '!') {
			// parse '!='
			if (*src == '=') {
				src++;
				token = Ne;
			}
			return;
		}
		else if (token == '<') {
			// parse '<=', '<<' or '<'
			if (*src == '=') {
				src ++;
				token = Le;
			} else if (*src == '<') {
				src ++;
				token = Shl;
			} else {
				token = Lt;
			}
			return;
		}
		else if (token == '>') {
			// parse '>=', '>>' or '>'
			if (*src == '=') {
				src ++;
				token = Ge;
			} else if (*src == '>') {
				src ++;
				token = Shr;
			} else {
				token = Gt;
			}
			return;
		}
		else if (token == '|') {
			// parse '|' or '||'
			if (*src == '|') {
				src ++;
				token = Lor;
			} else {
				token = Or;
			}
			return;
		}
		else if (token == '&') {
			// parse '&' and '&&'
			if (*src == '&') {
				src ++;
				token = Lan;
			} else {
				token = And;
			}
			return;
		}
		else if (token == '^') {
			token = Xor;
			return;
		}
		else if (token == '%') {
			token = Mod;
			return;
		}
		else if (token == '*') {
			token = Mul;
			return;
		}
		else if (token == '[') {
			token = Brak;
			return;
		}
		else if (token == '?') {
			token = Cond;
			return;
		}
		else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
			// directly return the character as token;
			return;
		}
	}
	return;
}
