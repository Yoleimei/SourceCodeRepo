#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "lexical.h"

#define YY_READ_BUF_SIZE 8192
#define YY_BUF_SIZE	  	 16384
#define YY_MORE_ADJ	  	 0
#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE   1
#define EOB_ACT_LAST_MATCH	  2
#define YY_END_OF_BUFFER_CHAR 0
#define YY_END_OF_BUFFER	  10

#define YY_SC_TO_UI(c)		((unsigned int) (unsigned char) c)
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)
#define YY_START			(((yy_start) - 1) / 2)
#define YY_NEW_FILE		 	yyrestart(yyin)

typedef struct yy_buffer_state *YY_BUFFER_STATE; 

struct yy_buffer_state {
	FILE *yy_input_file;
	char *yy_ch_buf;		
	char *yy_buf_pos;		
	size_t yy_buf_size;
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

static YY_BUFFER_STATE yy_ylm_buffer = NULL;

static char *yy_c_buf_p = (char *) 0;
static int yy_init = 0;
static int yy_start = 0;
static int yy_did_buffer_switch_on_eof;

FILE *yyin = (FILE *)0, *yyout = (FILE *)0;

char *yytext;

enum yy_token_type {
	NUMBER = 1,  // [0-9]+   
	ADD	= 2,  // +	   
	SUB	= 3,  // -	   
	MUL	= 4,  // *	   
	DIV	= 5,  // /	   
	EOL	= 6   // \n	  
};
int yy_val;

extern int yywrap (void);

static void yy_fatal_error (char* msg )
{
	(void) fprintf( stderr, "%s\n", msg );
	exit( 2 );
}

void yy_input(char *buf, int *result, size_t max_size)
{
	int c = '*'; 
	size_t n; 
	for ( n = 0; n < max_size && (c = getc( yyin )) != EOF && c != '\n' && c != '\r'; ++n ) 
		buf[n] = (char) c; 
	if ( c == '\n' || c == '\r')
		buf[n++] = '\n';
	if ( c == EOF && ferror( yyin ) ) 
		yy_fatal_error( "input in flex scanner failed" ); 
	*result = n;
}

void yy_do_before_action(char *yy_cp, char *yy_bp)
{
	yytext = yy_bp; 
	yyleng = (size_t)(yy_cp - yy_bp); 
	yy_hold_char = *yy_cp; 
	*yy_cp = '\0'; 
	yy_c_buf_p = yy_cp;
}

void yyrestart(FILE * input_file)
{
	printf("yyrestart\n");
}

static void yy_load_buffer_state(YY_BUFFER_STATE b)
{
	yy_n_chars = b->yy_n_chars;
	yytext = yy_c_buf_p = b->yy_buf_pos;
	yyin = b->yy_input_file;
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

	b->yy_buffer_status = YY_BUFFER_NEW;

	yy_load_buffer_state(b);
}

static void yy_init_buffer(YY_BUFFER_STATE  b, FILE * file )
{
	yy_flush_buffer(b);

	b->yy_input_file = file;
}

YY_BUFFER_STATE yy_create_buffer(FILE * file, int size )
{
	YY_BUFFER_STATE b;

	b = (YY_BUFFER_STATE)malloc(sizeof(struct yy_buffer_state));
	if ( ! b )
		yy_fatal_error( "out of dynamic memory in yy_create_buffer()" );

	b->yy_buf_size = size;

	b->yy_ch_buf = (char *)malloc(b->yy_buf_size + 2);
	if ( ! b->yy_ch_buf )
		yy_fatal_error( "out of dynamic memory in yy_create_buffer()" );

	yy_init_buffer(b, file);

	return b;
}

static yy_state_type yy_get_previous_state (void)
{
	register yy_state_type yy_current_state;
	register char *yy_cp;

	yy_current_state = yy_start;

	for ( yy_cp = yytext + YY_MORE_ADJ; yy_cp < yy_c_buf_p; ++yy_cp ) {
		if ( *yy_cp )
			yy_current_state = yy_nxt[yy_current_state][YY_SC_TO_UI(*yy_cp)];
		else
			yy_current_state = yy_NUL_trans[yy_current_state];
	}

	return yy_current_state;
}

static yy_state_type yy_try_NUL_trans(yy_state_type yy_current_state )
{
	register int yy_is_jam;

	yy_current_state = yy_NUL_trans[yy_current_state];
	yy_is_jam = (yy_current_state == 0);

	return yy_is_jam ? 0 : yy_current_state;
}

static int yy_get_next_buffer (void)
{
	register char *dest = yy_ylm_buffer->yy_ch_buf;
	register char *source = yytext;
	register int number_to_move, i;
	int ret_val;

	if ( yy_c_buf_p > &yy_ylm_buffer->yy_ch_buf[yy_n_chars + 1] )
		yy_fatal_error("fatal flex scanner internal error--end of buffer missed" );

	number_to_move = (int) (yy_c_buf_p - yytext) - 1;

	for ( i = 0; i < number_to_move; ++i )
		*(dest++) = *(source++);

	if ( yy_ylm_buffer->yy_buffer_status == YY_BUFFER_EOF_PENDING )
		yy_ylm_buffer->yy_n_chars = yy_n_chars = 0;

	else {
		int num_to_read = yy_ylm_buffer->yy_buf_size - number_to_move - 1;

		while ( num_to_read <= 0 ) { // realloc

			YY_BUFFER_STATE b = yy_ylm_buffer;

			int yy_c_buf_p_offset = (int) (yy_c_buf_p - b->yy_ch_buf);

			int new_size = b->yy_buf_size * 2;

			if ( new_size <= 0 )
				b->yy_buf_size += b->yy_buf_size / 8;
			else
				b->yy_buf_size *= 2;

			b->yy_ch_buf = (char *)realloc((void *) b->yy_ch_buf,b->yy_buf_size + 2  );

			if ( ! b->yy_ch_buf )
				yy_fatal_error("fatal error - scanner input buffer overflow" );

			yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];

			num_to_read = yy_ylm_buffer->yy_buf_size - number_to_move - 1;
		}

		if ( num_to_read > YY_READ_BUF_SIZE )
			num_to_read = YY_READ_BUF_SIZE;

		yy_input( (&yy_ylm_buffer->yy_ch_buf[number_to_move]), &yy_n_chars, (size_t) num_to_read );

		yy_ylm_buffer->yy_n_chars = yy_n_chars;
	}

	if ( yy_n_chars == 0 ) {
		if ( number_to_move == YY_MORE_ADJ ) {
			ret_val = EOB_ACT_END_OF_FILE;
			yyrestart(yyin);
		} else {
			ret_val = EOB_ACT_LAST_MATCH;
			yy_ylm_buffer->yy_buffer_status = YY_BUFFER_EOF_PENDING;
		}
	} else
		ret_val = EOB_ACT_CONTINUE_SCAN;

	if ((size_t) (yy_n_chars + number_to_move) > yy_ylm_buffer->yy_buf_size) { // realloc
		size_t new_size = yy_n_chars + number_to_move + (yy_n_chars >> 1);
		yy_ylm_buffer->yy_ch_buf = (char *) realloc((void *) yy_ylm_buffer->yy_ch_buf, new_size);
		if ( ! yy_ylm_buffer->yy_ch_buf )
			yy_fatal_error( "out of dynamic memory in yy_get_next_buffer()" );
	}

	yy_n_chars += number_to_move;
	yy_ylm_buffer->yy_ch_buf[(yy_n_chars)] = YY_END_OF_BUFFER_CHAR;
	yy_ylm_buffer->yy_ch_buf[(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;

	yytext = &yy_ylm_buffer->yy_ch_buf[0];

	return ret_val;
}

int yylex() 
{
	register yy_state_type yy_current_state;
	register char *yy_cp, *yy_bp;
	register int yy_act;

	int yy_amount_of_matched_text;

	if (!yy_init) {
		yy_init = 1;

		if (!yy_start)
			yy_start = 1;

		yyin = stdin;
		yyout = stdout;
		yy_ylm_buffer = yy_create_buffer(yyin, YY_BUF_SIZE);

		yy_load_buffer_state(yy_ylm_buffer);
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
		yy_do_before_action(yy_cp, yy_bp);
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
		case 9: // echo
			do { 
				if (fwrite( yytext, yyleng, 1, yyout )) {} 
			} while (0);
			break;
		case 11: return 0; break;
		case YY_END_OF_BUFFER: // 10
			yy_amount_of_matched_text = (int) (yy_cp - yytext) - 1;
			*yy_cp = yy_hold_char;
			if (yy_ylm_buffer->yy_buffer_status == YY_BUFFER_NEW) {
				yy_n_chars = yy_ylm_buffer->yy_n_chars;
				yy_ylm_buffer->yy_input_file = yyin;
				yy_ylm_buffer->yy_buffer_status = YY_BUFFER_NORMAL;
			}
			if ( yy_c_buf_p <= &yy_ylm_buffer->yy_ch_buf[(yy_n_chars)] ) {
				yy_state_type yy_next_state;
				yy_c_buf_p = yytext + yy_amount_of_matched_text;
				yy_current_state = yy_get_previous_state();

				yy_next_state = yy_try_NUL_trans( yy_current_state );

				yy_bp = yytext + YY_MORE_ADJ;

				if ( yy_next_state ) {
					yy_cp = ++yy_c_buf_p;
					yy_current_state = yy_next_state;
					goto yy_match;
				} else {
					yy_cp = (yy_c_buf_p);
					goto yy_find_action;
				}
			} else {
				switch ( yy_get_next_buffer()) {
				case EOB_ACT_END_OF_FILE:
					yy_did_buffer_switch_on_eof = 0;

					if ( yywrap() ) {
						yy_c_buf_p = yytext + YY_MORE_ADJ;

						yy_act = YY_STATE_EOF(YY_START);
						goto do_action;
					} else {
						if ( ! (yy_did_buffer_switch_on_eof) )
							YY_NEW_FILE;
					}
					break;
				case EOB_ACT_CONTINUE_SCAN:
					yy_c_buf_p = yytext + yy_amount_of_matched_text;

					yy_current_state = yy_get_previous_state();

					yy_cp = yy_c_buf_p;
					yy_bp = yytext + YY_MORE_ADJ;
					goto yy_match;
				case EOB_ACT_LAST_MATCH:
					yy_c_buf_p = &yy_ylm_buffer->yy_ch_buf[(yy_n_chars)];

					yy_current_state = yy_get_previous_state();

					yy_cp = (yy_c_buf_p);
					yy_bp = (yytext) + YY_MORE_ADJ;
					goto yy_find_action;
				}
			}
			break;
		default:
			yy_fatal_error("fatal flex scanner internal error--no action found" );
		}
	}
}

int main()
{
	int tok;
	while (tok = yylex()) {
		printf("%d", tok);
		if (NUMBER == tok)
			printf(" = %d", yy_val);
		printf("\n");
	}
}
