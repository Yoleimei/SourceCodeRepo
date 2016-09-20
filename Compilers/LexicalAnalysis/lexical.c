#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE; // line-161

struct yy_buffer_state {  // line-197
	FILE *yy_input_file;
	char *yy_ch_buf;		
	char *yy_buf_pos;		
	yy_size_t yy_buf_size;
	int yy_n_chars;
	int yy_is_our_buffer;
	int yy_is_interactive;
	int yy_at_bol;
    int yy_bs_lineno;
    int yy_bs_column;
	int yy_fill_buffer;
	int yy_buffer_status;

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
#define YY_BUFFER_EOF_PENDING 2
};

static size_t yy_buffer_stack_top = 0; // line-261
static YY_BUFFER_STATE * yy_buffer_stack = 0;

#define YY_CURRENT_BUFFER ( (yy_buffer_stack) ? (yy_buffer_stack)[(yy_buffer_stack_top)] : NULL) // line-271 
#define YY_CURRENT_BUFFER_LVALUE (yy_buffer_stack)[(yy_buffer_stack_top)]

static int yy_init = 0;  // line-287
static int yy_start = 0;

static void yyensure_buffer_stack (void) { // line-303
	int num_to_alloc;
	if (!(yy_buffer_stack)) {
		num_to_alloc = 1;
		(yy_buffer_stack) = (struct yy_buffer_state**)yyalloc
								(num_to_alloc * sizeof(struct yy_buffer_state*)
								);
		if ( ! (yy_buffer_stack) )
			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
								  
		memset((yy_buffer_stack), 0, num_to_alloc * sizeof(struct yy_buffer_state*));
				
		(yy_buffer_stack_max) = num_to_alloc;
		(yy_buffer_stack_top) = 0;
		return;
	}

	if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max)) - 1){
		int grow_size = 8 

		num_to_alloc = (yy_buffer_stack_max) + grow_size;
		(yy_buffer_stack) = (struct yy_buffer_state**)yyrealloc
								((yy_buffer_stack),
								num_to_alloc * sizeof(struct yy_buffer_state*)
								);
		if ( ! (yy_buffer_stack) )
			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );

		memset((yy_buffer_stack) + (yy_buffer_stack_max), 0, grow_size * sizeof(struct yy_buffer_state*));
		(yy_buffer_stack_max) = num_to_alloc;
	}
}

FILE *yyin = (FILE *)0, *yyout = (FILE *)0;  // line-345
typedef int yy_state_type;

char *yytext;  // line-460

enum yy_token_type {  // line-463
	NUMBER = 1,  // [0-9]+   
	ADD    = 2,  // +       
	SUB    = 3,  // -       
	MUL    = 4,  // *       
	DIV    = 5,  // /       
	EOL    = 6   // \n      
};
int yy_val;  // line-471

int yylex() { // line-653
	register yy_state_type yy_current_state;
	register char *yy_cp, *yy_bp;
	register int yy_act;
	
	if (!yy_init) {
		yy_init = 1;
		
		if (!yy_start)
			yy_start = 1;
		
		if (!yyin)
			yyin = stdin;
		
		if (!yyout)
			yyout = stdout;
		
		if (!YY_CURRENT_BUFFER) {
			yyensure_buffer_stack();
			YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin,YY_BUF_SIZE );
		}
	}
}

int main()
{
	int tok;
	while (tok = yy_lex()) {
		printf("%d", tok);
		if (NUMBER == tok)
			printf(" = %d", yy_val);
		else
			printf("\n");
	}
}