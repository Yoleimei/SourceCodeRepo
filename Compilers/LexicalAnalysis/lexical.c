#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE; 
typedef int yy_state_type;

struct yy_buffer_state {
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

static char yy_hold_char;
static int yy_n_chars;
int yyleng;

static YY_BUFFER_STATE * yy_buffer_stack = 0;
static YY_BUFFER_STATE yy_ylm_buffer = NULL;

static char *yy_c_buf_p = (char *) 0;
static int yy_init = 0;
static int yy_start = 0;

FILE *yyin = (FILE *)0, *yyout = (FILE *)0;  // line-345

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

void yy_do_before_action()
{
	yytext = yy_bp; 
	yyleng = (size_t)(yy_cp - yy_bp); 
	yy_hold_char = *yy_cp; 
	*yy_cp = '\0'; 
	yy_c_buf_p = yy_cp;
}

static void yy_load_buffer_state(void)
{
    yy_n_chars = yy_ylm_buffer->yy_n_chars;
	yytext = yy_c_buf_p = yy_ylm_buffer->yy_buf_pos;
	yyin = yy_ylm_buffer->yy_input_file;
	yy_hold_char = *yy_c_buf_p;
}

void yy_flush_buffer(YY_BUFFER_STATE  b )
{
    if ( ! b )
		return;

	b->yy_n_chars = 0;

	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

	b->yy_buf_pos = &b->yy_ch_buf[0];

	b->yy_at_bol = 1;
	b->yy_buffer_status = YY_BUFFER_NEW;

	yy_load_buffer_state( );
}

static void yy_init_buffer(YY_BUFFER_STATE  b, FILE * file )
{
	yy_flush_buffer(b );

	b->yy_input_file = file;
	b->yy_fill_buffer = 1;

    b->yy_bs_lineno = 1;
    b->yy_bs_column = 0;

    b->yy_is_interactive = 0;
}

YY_BUFFER_STATE yy_create_buffer(FILE * file, int size )
{
	YY_BUFFER_STATE b;
	
	b = (YY_BUFFER_STATE)malloc(sizeof(struct yy_buffer_state));
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_buf_size = size;

	b->yy_ch_buf = (char *)malloc(b->yy_buf_size + 2  );
	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_is_our_buffer = 1;

	yy_init_buffer(b,file );

	return b;
}

static yy_state_type yy_get_previous_state (void)
{
	register yy_state_type yy_current_state;
	register char *yy_cp;
    
	yy_current_state = (yy_start);

	for ( yy_cp = (yytext) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp ) {
		if ( *yy_cp ) {
			yy_current_state = yy_nxt[yy_current_state][YY_SC_TO_UI(*yy_cp)];
		} else
			yy_current_state = yy_NUL_trans[yy_current_state];
	}

	return yy_current_state;
}

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
			yy_ylm_buffer = yy_create_buffer(yyin,YY_BUF_SIZE );
		}
	}
	
	while (1) {
		yy_cp = yy_c_buf_p;
		*yy_cp = yy_hold_char;
		yy_bp = yy_cp;
		yy_current_state = yy_start;
yy_match:
		while((yy_current_state = yy_nxt[yy_current_state][YY_SC_TO_UI(*yy_cp)]) > 0)
			++yy_cp;
		yy_current_state = -yy_current_state;
yy_find_action:
		yy_act = yy_accept[yy_current_state];
		yy_do_before_action();
do_action:
		switch(yy_act) {
		case 1: return ADD; break;
		case 2: return SUB; break;
		case 3: return MUL; break;
		case 4: return DIV; break;
		case 5: 
			yy_val = atoi(yytext);
			return NUMBER; 
			break;
		case 6: return EOL; break;
		case 7: break;
		case 8: printf("Mystery character %c\n", *yytext); break;
		case 9:
			do { 
				if (fwrite( yytext, yyleng, 1, yyout )) {} 
			} while (0);
			break;
		case 11: return 0; break;
		case YY_END_OF_BUFFER:
			int yy_amount_of_matched_text = (int) (yy_cp - (yytext)) - 1;
			*yy_cp = yy_hold_char;
			if (yy_ylm_buffer->yy_buffer_status == YY_BUFFER_NEW) {
				yy_n_chars = yy_ylm_buffer->yy_n_chars;
				yy_ylm_buffer->yy_input_file = yyin;
				yy_ylm_buffer->yy_buffer_status = YY_BUFFER_NORMAL;
			}
			if ( (yy_c_buf_p) <= &yy_ylm_buffer->yy_ch_buf[(yy_n_chars)] ) {
				yy_state_type yy_next_state;
				yy_c_buf_p = (yytext) + yy_amount_of_matched_text;
				yy_current_state = yy_get_previous_state();
				
				yy_next_state = yy_try_NUL_trans( yy_current_state );

				yy_bp = (yytext) + YY_MORE_ADJ;
				
				if ( yy_next_state ) {
					yy_cp = ++(yy_c_buf_p);
					yy_current_state = yy_next_state;
					goto yy_match;
				} else {
					yy_cp = (yy_c_buf_p);
					goto yy_find_action;
				}
			} else {
				switch ( yy_get_next_buffer(  ) ) {
				case EOB_ACT_END_OF_FILE:
					(yy_did_buffer_switch_on_eof) = 0;
	
					if ( yywrap() ) {
						(yy_c_buf_p) = (yytext) + YY_MORE_ADJ;
	
						yy_act = YY_STATE_EOF(YY_START);
						goto do_action;
					} else {
						if ( ! (yy_did_buffer_switch_on_eof) )
							YY_NEW_FILE;
					}
					break;
				case EOB_ACT_CONTINUE_SCAN:
					(yy_c_buf_p) = (yytext) + yy_amount_of_matched_text;
	
					yy_current_state = yy_get_previous_state();
	
					yy_cp = (yy_c_buf_p);
					yy_bp = (yytext) + YY_MORE_ADJ;
					goto yy_match;
				case EOB_ACT_LAST_MATCH:
					(yy_c_buf_p) = &yy_ylm_buffer->yy_ch_buf[(yy_n_chars)];
	
					yy_current_state = yy_get_previous_state();
	
					yy_cp = (yy_c_buf_p);
					yy_bp = (yytext) + YY_MORE_ADJ;
					goto yy_find_action;
				}
				break;
			}
		default:
			YY_FATAL_ERROR("fatal flex scanner internal error--no action found" );
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

static yyconst flex_int16_t yy_nxt[][128] =
    {
    {
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,

        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0
    },

    {
        3,    4,    4,    4,    4,    4,    4,    4,    4,    5,
        6,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    5,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    7,    8,    4,    9,    4,   10,   11,   11,
       11,   11,   11,   11,   11,   11,   11,   11,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,

        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4
    },

    {
        3,    4,    4,    4,    4,    4,    4,    4,    4,    5,
        6,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    5,    4,    4,    4,    4,    4,    4,    4,

        4,    4,    7,    8,    4,    9,    4,   10,   11,   11,
       11,   11,   11,   11,   11,   11,   11,   11,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4
    },

    {
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,

       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,

       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
       -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3
    },

    {
        3,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,

       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4,
       -4,   -4,   -4,   -4,   -4,   -4,   -4,   -4
    },

    {
        3,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,

       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5,
       -5,   -5,   -5,   -5,   -5,   -5,   -5,   -5
    },

    {
        3,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,

       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,
       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6,

       -6,   -6,   -6,   -6,   -6,   -6,   -6,   -6
    },

    {
        3,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,

       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7,
       -7,   -7,   -7,   -7,   -7,   -7,   -7,   -7
    },

    {
        3,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,

       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
       -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8
    },

    {
        3,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,

       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
       -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9

    },

    {
        3,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,

      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10,
      -10,  -10,  -10,  -10,  -10,  -10,  -10,  -10
    },

    {
        3,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,   12,   12,
       12,   12,   12,   12,   12,   12,   12,   12,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,

      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
      -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11
    },

    {
        3,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,

      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,   12,   12,
       12,   12,   12,   12,   12,   12,   12,   12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,
      -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12
    },

    } ;
static yyconst flex_int16_t yy_accept[13] =
    {   0,
        0,    0,   10,    8,    7,    6,    3,    1,    2,    4,
        5,    5
    } ;

static yyconst yy_state_type yy_NUL_trans[13] =
    {   0,
        4,    4,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0
    } ;