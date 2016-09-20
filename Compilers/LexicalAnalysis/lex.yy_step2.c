#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#ifndef FLEXINT_H
	#define FLEXINT_H
	#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
		#ifndef __STDC_LIMIT_MACROS
			#define __STDC_LIMIT_MACROS 1
		#endif
		#include <inttypes.h>
		typedef int8_t flex_int8_t;
		typedef uint8_t flex_uint8_t;
		typedef int16_t flex_int16_t;
		typedef uint16_t flex_uint16_t;
		typedef int32_t flex_int32_t;
		typedef uint32_t flex_uint32_t;
	#else
		typedef signed char flex_int8_t;
		typedef short int flex_int16_t;
		typedef int flex_int32_t;
		typedef unsigned char flex_uint8_t; 
		typedef unsigned short int flex_uint16_t;
		typedef unsigned int flex_uint32_t;
	#endif
#endif

#ifdef __cplusplus
	#define YY_USE_CONST
#else	
	#if defined (__STDC__)
		#define YY_USE_CONST
	#endif	
#endif	

#ifdef YY_USE_CONST
	#define yyconst const
#else
	#define yyconst
#endif

#define YY_NULL 0
#define YY_SC_TO_UI(c) ((unsigned int) (unsigned char) c)
#define YY_START (((yy_start) - 1) / 2)
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)
#define YY_NEW_FILE yyrestart(yyin  )
#define YY_END_OF_BUFFER_CHAR 0

#ifndef YY_BUF_SIZE
	#ifdef __ia64__
		#define YY_BUF_SIZE 32768
	#else
		#define YY_BUF_SIZE 16384
	#endif 
#endif

#define YY_STATE_BUF_SIZE   ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))

typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern int yyleng;
extern FILE *yyin, *yyout;

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2
#define YY_LESS_LINENO(n)
	
/* Return all but the first "n" matched characters back to the input stream. */
#define yyless(n) \
	do { \
		/* Undo effects of setting up yytext. */ \
		int yyless_macro_arg = (n); \
		YY_LESS_LINENO(yyless_macro_arg);\
		*yy_cp = (yy_hold_char); \
		YY_RESTORE_YY_MORE_OFFSET \
		(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
	} while ( 0 )

struct yy_buffer_state {
	FILE *yy_input_file;
	char *yy_ch_buf;		// input buffer 
	char *yy_buf_pos;		// current position in input buffer 
	// Size of input buffer in bytes, not including room for EOB characters.
	size_t yy_buf_size;
	// Number of characters read into yy_ch_buf, not including EOBcharacters.
	int yy_n_chars;
	// Whether we "own" the buffer - i.e., we know we created it, and 
	// can realloc() it to grow it, and should free() it to delete it.
	int yy_is_our_buffer;
	// Whether this is an "interactive" input source; if so, and
	// if we're using stdio for input, then we want to use getc()
	// instead of fread(), to make sure we stop fetching input after
	// each newline.
	int yy_is_interactive;
	// Whether we're considered to be at the beginning of a line.
	// If so, '^' rules will be active on the next match, otherwise not.
	int yy_at_bol;
	int yy_bs_lineno; //< The line count. 
	int yy_bs_column; //< The column count. 
	// Whether to try to fill the input buffer when we reach the end of it.
	int yy_fill_buffer;
	int yy_buffer_status;
#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
#define YY_BUFFER_EOF_PENDING 2
};

static size_t yy_buffer_stack_top = 0; //< index of top of stack. 
static size_t yy_buffer_stack_max = 0; //< capacity of stack. 
static YY_BUFFER_STATE * yy_buffer_stack = 0; //< Stack as an array. 

#define YY_CURRENT_BUFFER ( (yy_buffer_stack) ? (yy_buffer_stack)[(yy_buffer_stack_top)] : NULL)
#define YY_CURRENT_BUFFER_LVALUE (yy_buffer_stack)[(yy_buffer_stack_top)]

/* yy_hold_char holds the character lost when yytext is formed. */
static char yy_hold_char;
static int yy_n_chars;		/* number of characters read into yy_ch_buf */
int yyleng;

/* Points to current character in buffer. */
static char *yy_c_buf_p = (char *) 0;
static int yy_init = 0;		/* whether we need to initialize */
static int yy_start = 0;	/* start state number */

// Flag which is used to allow yywrap()'s to do buffer switches
// instead of setting up a fresh yyin.  A bit of a hack ...
static int yy_did_buffer_switch_on_eof;

void yyrestart (FILE *input_file  );
YY_BUFFER_STATE yy_create_buffer (FILE *file,int size  );
void yy_flush_buffer (YY_BUFFER_STATE b  );

static void yyensure_buffer_stack (void );
static void yy_load_buffer_state (void );
static void yy_init_buffer (YY_BUFFER_STATE b,FILE *file  );

typedef unsigned char YY_CHAR;

FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;

typedef int yy_state_type;

extern int yylineno;

int yylineno = 1;

extern char *yytext;
#define yytext_ptr yytext

static yy_state_type yy_get_previous_state (void );
static yy_state_type yy_try_NUL_trans (yy_state_type current_state  );
static int yy_get_next_buffer (void );
static void yy_fatal_error (yyconst char msg[]  );

// Done after the current pattern has been matched and before the
// corresponding action - sets up yytext.
#define YY_DO_BEFORE_ACTION \
	(yytext_ptr) = yy_bp; \
	yyleng = (size_t) (yy_cp - yy_bp); \
	(yy_hold_char) = *yy_cp; \
	*yy_cp = '\0'; \
	(yy_c_buf_p) = yy_cp;

#define YY_END_OF_BUFFER 10

// 0  - back up
// 1  - ADD
// 2  - SUB
// 3  - MUL
// 4  - DIV
// 5  - NUMBER
// 6  - EOL
// 7  - ignore
// 8  - other 
// 9  - ECHO
// 10 - YY_END_OF_BUFFER
// 接受状态表
static yyconst flex_int16_t yy_accept[15] = {   
	0,
	0,	0, 10,	8,	7,	6,	3,	5,	1,	0,
	5,	1,	2,	0
} ;

static yyconst flex_int32_t yy_ec[256] = {   
	0,
	1,	1,	1,	1,	1,	1,	1,	1,	2,	3,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	2,	1,	1,	1,	1,	1,	1,	4,	1,
	1,	1,	1,	1,	5,	1,	1,	6,	6,	6,
	6,	6,	6,	6,	6,	6,	6,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,

	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,

	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1
} ;

static yyconst flex_int32_t yy_meta[7] = {   
	0,
	1,	1,	1,	2,	1,	3
} ;

static yyconst flex_int16_t yy_base[18] = {   
	0,
	0,	0,   12,   13,   13,   13,	3,	0,	0,	0,
	0,	0,   13,   13,	8,	8,	7
} ;

static yyconst flex_int16_t yy_def[18] = {
	0,
   14,	1,   14,   14,   14,   14,   14,   15,   16,   17,
   15,   16,   14,	0,   14,   14,   14
} ;

// 状态转移矩阵
static yyconst flex_int16_t yy_nxt[20] = {   
	0,
	4,	5,	6,	7,	4,	8,	9,   10,   13,   12,
   11,   14,	3,   14,   14,   14,   14,   14,   14
} ;

static yyconst flex_int16_t yy_chk[20] = {   
	0,
	1,	1,	1,	1,	1,	1,	7,	7,   17,   16,
   15,	3,   14,   14,   14,   14,   14,   14,   14
} ;

static yy_state_type yy_last_accepting_state;
static char *yy_last_accepting_cpos;

extern int yy_flex_debug;
int yy_flex_debug = 0;

// The intent behind this definition is that it'll catch
// any uses of REJECT which flex missed.
#define REJECT reject_used_but_not_detected
#define yymore() yymore_used_but_not_detected
#define YY_MORE_ADJ 0
#define YY_RESTORE_YY_MORE_OFFSET
char *yytext;
enum yytokentype {
	NUMBER = 258,
	ADD = 259,
	SUB = 260,
	MUL = 261,
	DIV = 262,
	EOL = 264
};
int yylval;

#define INITIAL 0

#include <unistd.h>

// Macros after this point can all be overridden by user definitions in section 1.
#ifndef YY_SKIP_YYWRAP
	#ifdef __cplusplus
		extern "C" int yywrap (void );
	#else
		extern int yywrap (void );
	#endif
#endif

/* Amount of stuff to slurp up with each read. */
#ifndef YY_READ_BUF_SIZE
	#ifdef __ia64__
		/* On IA-64, the buffer size is 16k, not 8k */
		#define YY_READ_BUF_SIZE 16384
	#else
		#define YY_READ_BUF_SIZE 8192
	#endif /* __ia64__ */
#endif

/* Copy whatever the last rule matched to the standard output. */
#ifndef ECHO
// This used to be an fputs(), but since the string might contain NUL's, we now use fwrite().
#define ECHO do { if (fwrite( yytext, yyleng, 1, yyout )) {} } while (0)
#endif

// Gets input and stuffs it into "buf".  number of characters read, or YY_NULL, is returned in "result".
#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) { \
		int c = '*'; \
		size_t n; \
		for ( n = 0; n < max_size && \
				 (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
			buf[n] = (char) c; \
		if ( c == '\n' ) \
			buf[n++] = (char) c; \
		if ( c == EOF && ferror( yyin ) ) \
			YY_FATAL_ERROR( "input in flex scanner failed" ); \
		result = n; \
	} else { \
		errno=0; \
		while ( (result = fread(buf, 1, max_size, yyin))==0 && ferror(yyin)) \
			{ \
			if( errno != EINTR) \
				{ \
				YY_FATAL_ERROR( "input in flex scanner failed" ); \
				break; \
				} \
			errno=0; \
			clearerr(yyin); \
			} \
	}
#endif

// No semi-colon after return; correct usage is to write "yyterminate();" -
// we don't want an extra ';' after the "return" because that will cause
// some compilers to complain about unreachable statements.
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif

/* Number of entries by which start-condition stack grows. */
#ifndef YY_START_STACK_INCR
#define YY_START_STACK_INCR 25
#endif

/* Report a fatal error. */
#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) yy_fatal_error( msg )
#endif

/* end tables serialization structures and prototypes */

/* Default declaration of generated scanner - a define so the user can
 * easily add parameters.
 */
#ifndef YY_DECL
#define YY_DECL_IS_OURS 1

extern int yylex (void);

#define YY_DECL int yylex (void)
#endif /* !YY_DECL */

// Code executed at the beginning of each rule, after yytext and yyleng
// have been set up.
#define YY_USER_ACTION

/* Code executed at the end of each rule. */
#define YY_BREAK break;

#define YY_RULE_SETUP YY_USER_ACTION

// The main scanner function which does all the work.
YY_DECL
{
	register yy_state_type yy_current_state;
	register char *yy_cp, *yy_bp;
	register int yy_act;

	if ( !(yy_init) ) {
		(yy_init) = 1;

		if ( ! (yy_start) )
			(yy_start) = 1;	// first start state 

		if ( ! yyin )
			yyin = stdin;

		if ( ! yyout )
			yyout = stdout;

		if ( ! YY_CURRENT_BUFFER ) {
			yyensure_buffer_stack ();
			YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin,YY_BUF_SIZE );
		}

		yy_load_buffer_state( );
	}

	while ( 1 ) {
		yy_cp = (yy_c_buf_p);

		// Support of yytext. 
		*yy_cp = (yy_hold_char);

		// yy_bp points to the position in yy_ch_buf of the start ofthe current run.
		yy_bp = yy_cp;

		yy_current_state = (yy_start);
yy_match:
		do {
			register YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)];
			if ( yy_accept[yy_current_state] ) {
				(yy_last_accepting_state) = yy_current_state;
				(yy_last_accepting_cpos) = yy_cp;
			}
			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state ) {
				yy_current_state = (int) yy_def[yy_current_state];
				if ( yy_current_state >= 15 )
					yy_c = yy_meta[(unsigned int) yy_c];
			}
			yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
			++yy_cp;
		} while ( yy_base[yy_current_state] != 13 );

yy_find_action:
		yy_act = yy_accept[yy_current_state];
		if ( yy_act == 0 ) { /* have to back up */
			yy_cp = (yy_last_accepting_cpos);
			yy_current_state = (yy_last_accepting_state);
			yy_act = yy_accept[yy_current_state];
		}

		YY_DO_BEFORE_ACTION;

do_action:	/* This label is used only to access EOF actions. */
		switch ( yy_act ) { /* beginning of action switch */
		case 0: /* must back up */
			/* undo the effects of YY_DO_BEFORE_ACTION */
			*yy_cp = (yy_hold_char);
			yy_cp = (yy_last_accepting_cpos);
			yy_current_state = (yy_last_accepting_state);
			goto yy_find_action;

		case 1:
			YY_RULE_SETUP
			{ return ADD; }
			YY_BREAK
		case 2:
			YY_RULE_SETUP
			{ return SUB; }
			YY_BREAK
		case 3:
			YY_RULE_SETUP
			{ return MUL; }
			YY_BREAK
		case 4:
			*yy_cp = (yy_hold_char); /* undo effects of setting up yytext */
			(yy_c_buf_p) = yy_cp = yy_bp + 1;
			YY_DO_BEFORE_ACTION; /* set up yytext again */
			YY_RULE_SETUP
			{ return DIV; }
			YY_BREAK
		case 5:
			YY_RULE_SETUP
			{ yylval = atoi(yytext); return NUMBER; }
			YY_BREAK
		case 6:
			/* rule 6 can match eol */
			YY_RULE_SETUP
			{ return EOL; }
			YY_BREAK
		case 7:
			YY_RULE_SETUP
			{ /* ignore */ }
			YY_BREAK
		case 8:
			YY_RULE_SETUP
			{ printf("Mystery character %c\n", *yytext); }
			YY_BREAK
		case 9:
			YY_RULE_SETUP
			ECHO;
			YY_BREAK
		case YY_STATE_EOF(INITIAL):
			yyterminate();

		case YY_END_OF_BUFFER: 
			/* Amount of text matched not including the EOB char. */
			int yy_amount_of_matched_text = (int) (yy_cp - (yytext_ptr)) - 1;
			
			/* Undo the effects of YY_DO_BEFORE_ACTION. */
			*yy_cp = (yy_hold_char);
			YY_RESTORE_YY_MORE_OFFSET
			
			if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW ) {
				/* We're scanning a new file or input source.  It's
				* possible that this happened because the user
				* just pointed yyin at a new source and called
				* yylex().  If so, then we have to assure
				* consistency between YY_CURRENT_BUFFER and our
				* globals.  Here is the right place to do so, because
				* this is the first action (other than possibly a
				* back-up) that will match for the new input source.
				*/
				(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
				YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
				YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
			}
			
			/* Note that here we test for yy_c_buf_p "<=" to the position
			* of the first EOB in the buffer, since yy_c_buf_p will
			* already have been incremented past the NUL character
			* (since all states make transitions on EOB to the
			* end-of-buffer state).  Contrast this with the test
			* in input().
			*/
			if ( (yy_c_buf_p) <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] ) { /* This was really a NUL. */
				yy_state_type yy_next_state;
			
				(yy_c_buf_p) = (yytext_ptr) + yy_amount_of_matched_text;
			
				yy_current_state = yy_get_previous_state(  );
			
				/* Okay, we're now positioned to make the NUL
				* transition.  We couldn't have
				* yy_get_previous_state() go ahead and do it
				* for us because it doesn't know how to deal
				* with the possibility of jamming (and we don't
				* want to build jamming into it because then it
				* will run more slowly).
				*/
			
				yy_next_state = yy_try_NUL_trans( yy_current_state );
			
				yy_bp = (yytext_ptr) + YY_MORE_ADJ;
			
				if ( yy_next_state ) {
					/* Consume the NUL. */
					yy_cp = ++(yy_c_buf_p);
					yy_current_state = yy_next_state;
					goto yy_match;
				} else {
					yy_cp = (yy_c_buf_p);
					goto yy_find_action;
				}
			} else switch ( yy_get_next_buffer(  ) ) {
				case EOB_ACT_END_OF_FILE: 
				{
					(yy_did_buffer_switch_on_eof) = 0;
			
					if ( yywrap( ) ) {
						/* Note: because we've taken care in
						* yy_get_next_buffer() to have set up
						* yytext, we can now set up
						* yy_c_buf_p so that if some total
						* hoser (like flex itself) wants to
						* call the scanner after we return the
						* YY_NULL, it'll still work - another
						* YY_NULL will get returned.
						*/
						(yy_c_buf_p) = (yytext_ptr) + YY_MORE_ADJ;
			
						yy_act = YY_STATE_EOF(YY_START);
						goto do_action;
					} else {
						if ( ! (yy_did_buffer_switch_on_eof) )
							YY_NEW_FILE;
					}
					break;
				}
			
				case EOB_ACT_CONTINUE_SCAN:
					(yy_c_buf_p) =
						(yytext_ptr) + yy_amount_of_matched_text;
			
					yy_current_state = yy_get_previous_state(  );
			
					yy_cp = (yy_c_buf_p);
					yy_bp = (yytext_ptr) + YY_MORE_ADJ;
					goto yy_match;
			
				case EOB_ACT_LAST_MATCH:
					(yy_c_buf_p) =
					&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)];
			
					yy_current_state = yy_get_previous_state(  );
			
					yy_cp = (yy_c_buf_p);
					yy_bp = (yytext_ptr) + YY_MORE_ADJ;
					goto yy_find_action;
				}
			break;

		default:
		YY_FATAL_ERROR("fatal flex scanner internal error--no action found" );
		} /* end of action switch */
	} /* end of scanning one token */
} /* end of yylex */

/* yy_get_next_buffer - try to read in a new buffer
 *
 * Returns a code representing an action:
 *	EOB_ACT_LAST_MATCH -
 *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
 *	EOB_ACT_END_OF_FILE - end of file
 */
static int yy_get_next_buffer (void)
{
	register char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
	register char *source = (yytext_ptr);
	register int number_to_move, i;
	int ret_val;

	if ( (yy_c_buf_p) > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] )
		YY_FATAL_ERROR("fatal flex scanner internal error--end of buffer missed" );

	if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 ) { /* Don't try to fill the buffer, so this is an EOF. */
		if ( (yy_c_buf_p) - (yytext_ptr) - YY_MORE_ADJ == 1 ) {
			return EOB_ACT_END_OF_FILE;
		} else {
			return EOB_ACT_LAST_MATCH;
		}
	}

	/* Try to read more data. */

	/* First move last chars to start of buffer. */
	number_to_move = (int) ((yy_c_buf_p) - (yytext_ptr)) - 1;

	for ( i = 0; i < number_to_move; ++i )
		*(dest++) = *(source++);

	if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars) = 0;
	else {
		int num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;

		while ( num_to_read <= 0 ) { /* Not enough room in the buffer - grow it. */
			/* just a shorter name for the current buffer */
			YY_BUFFER_STATE b = YY_CURRENT_BUFFER;

			int yy_c_buf_p_offset = (int) ((yy_c_buf_p) - b->yy_ch_buf);

			if ( b->yy_is_our_buffer ) {
				int new_size = b->yy_buf_size * 2;

				if ( new_size <= 0 )
					b->yy_buf_size += b->yy_buf_size / 8;
				else
					b->yy_buf_size *= 2;

				b->yy_ch_buf = (char *)
					/* Include room in for 2 EOB chars. */
					realloc((void *) b->yy_ch_buf,b->yy_buf_size + 2  );
			} else
				/* Can't grow it, we don't own it. */
				b->yy_ch_buf = 0;

			if ( ! b->yy_ch_buf )
				YY_FATAL_ERROR("fatal error - scanner input buffer overflow" );

			(yy_c_buf_p) = &b->yy_ch_buf[yy_c_buf_p_offset];

			num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
		}

		if ( num_to_read > YY_READ_BUF_SIZE )
			num_to_read = YY_READ_BUF_SIZE;

		/* Read in more data. */
		YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]), (yy_n_chars), (size_t) num_to_read );

		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
	}

	if ( (yy_n_chars) == 0 ) {
		if ( number_to_move == YY_MORE_ADJ ) {
			ret_val = EOB_ACT_END_OF_FILE;
			yyrestart(yyin  );
		} else {
			ret_val = EOB_ACT_LAST_MATCH;
			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_EOF_PENDING;
		}
	} else
		ret_val = EOB_ACT_CONTINUE_SCAN;

	if ((size_t) ((yy_n_chars) + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
		/* Extend the array by 50%, plus the number we really need. */
		size_t new_size = (yy_n_chars) + number_to_move + ((yy_n_chars) >> 1);
		YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) realloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size  );
		if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
			YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
	}

	(yy_n_chars) += number_to_move;
	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] = YY_END_OF_BUFFER_CHAR;
	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;

	(yytext_ptr) = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];

	return ret_val;
}

/* yy_get_previous_state - get the state just before the EOB char was reached */
static yy_state_type yy_get_previous_state (void)
{
	register yy_state_type yy_current_state;
	register char *yy_cp;
	
	yy_current_state = (yy_start);

	for ( yy_cp = (yytext_ptr) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp ) {
		register YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
		if ( yy_accept[yy_current_state] ) {
			(yy_last_accepting_state) = yy_current_state;
			(yy_last_accepting_cpos) = yy_cp;
		}
		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state ) {
			yy_current_state = (int) yy_def[yy_current_state];
			if ( yy_current_state >= 15 )
				yy_c = yy_meta[(unsigned int) yy_c];
		}
		yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
	}

	return yy_current_state;
}

/* yy_try_NUL_trans - try to make a transition on the NUL character
 *
 * synopsis
 *	next_state = yy_try_NUL_trans( current_state );
 */
static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state )
{
	register int yy_is_jam;
	register char *yy_cp = (yy_c_buf_p);

	register YY_CHAR yy_c = 1;
	if ( yy_accept[yy_current_state] ) {
		(yy_last_accepting_state) = yy_current_state;
		(yy_last_accepting_cpos) = yy_cp;
	}
	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state ) {
		yy_current_state = (int) yy_def[yy_current_state];
		if ( yy_current_state >= 15 )
			yy_c = yy_meta[(unsigned int) yy_c];
	}
	yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
	yy_is_jam = (yy_current_state == 14);

	return yy_is_jam ? 0 : yy_current_state;
}

/** Immediately switch to a different input stream.
 * @param input_file A readable stream.
 * 
 * @note This function does not reset the start condition to @c INITIAL .
 */
void yyrestart  (FILE * input_file )
{
	
	if ( ! YY_CURRENT_BUFFER ) {
		yyensure_buffer_stack ();
		YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin,YY_BUF_SIZE );
	}

	yy_init_buffer(YY_CURRENT_BUFFER,input_file );
	yy_load_buffer_state( );
}

static void yy_load_buffer_state  (void)
{
	(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
	(yytext_ptr) = (yy_c_buf_p) = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
	(yy_hold_char) = *(yy_c_buf_p);
}

/** Allocate and initialize an input buffer state.
 * @param file A readable stream.
 * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.
 * 
 * @return the allocated buffer state.
 */
YY_BUFFER_STATE yy_create_buffer  (FILE * file, int  size )
{
	YY_BUFFER_STATE b;
	
	b = (YY_BUFFER_STATE) malloc(sizeof( struct yy_buffer_state )  );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_buf_size = size;

	b->yy_ch_buf = (char *) malloc(b->yy_buf_size + 2  );
	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_is_our_buffer = 1;

	yy_init_buffer(b,file );

	return b;
}

#ifndef __cplusplus
extern int isatty (int );
#endif /* __cplusplus */
	
// Initializes or reinitializes a buffer.
// This function is sometimes called more than once on the same buffer,
// such as during a yyrestart() or at EOF.
static void yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file )
{
	int oerrno = errno;
	
	yy_flush_buffer(b );

	b->yy_input_file = file;
	b->yy_fill_buffer = 1;

	if (b != YY_CURRENT_BUFFER){
		b->yy_bs_lineno = 1;
		b->yy_bs_column = 0;
	}

	b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
	
	errno = oerrno;
}

// Discard all buffered characters. On the next scan, YY_INPUT will be called.
// @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
void yy_flush_buffer (YY_BUFFER_STATE  b )
{
	if ( ! b )
		return;

	b->yy_n_chars = 0;

	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

	b->yy_buf_pos = &b->yy_ch_buf[0];

	b->yy_at_bol = 1;
	b->yy_buffer_status = YY_BUFFER_NEW;

	if ( b == YY_CURRENT_BUFFER )
		yy_load_buffer_state( );
}

// Allocates the stack if it does not exist. Guarantees space for at least one push.
static void yyensure_buffer_stack (void)
{
	int num_to_alloc;
	
	if (!(yy_buffer_stack)) {

		// First allocation is just for 2 elements, since we don't know if this
		// scanner will even need a stack. We use 2 instead of 1 to avoid an
		// immediate realloc on the next call.
		num_to_alloc = 1;
		(yy_buffer_stack) = (struct yy_buffer_state**)malloc(num_to_alloc * sizeof(struct yy_buffer_state*));
		if ( ! (yy_buffer_stack) )
			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
								  
		memset((yy_buffer_stack), 0, num_to_alloc * sizeof(struct yy_buffer_state*));
				
		(yy_buffer_stack_max) = num_to_alloc;
		(yy_buffer_stack_top) = 0;
		return;
	}

	if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max)) - 1){

		// Increase the buffer to prepare for a possible push. 
		int grow_size = 8;

		num_to_alloc = (yy_buffer_stack_max) + grow_size;
		(yy_buffer_stack) = (struct yy_buffer_state**)realloc((yy_buffer_stack), num_to_alloc * sizeof(struct yy_buffer_state*));
		if ( ! (yy_buffer_stack) )
			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );

		// zero only the new slots.
		memset((yy_buffer_stack) + (yy_buffer_stack_max), 0, grow_size * sizeof(struct yy_buffer_state*));
		(yy_buffer_stack_max) = num_to_alloc;
	}
}

#ifndef YY_EXIT_FAILURE
#define YY_EXIT_FAILURE 2
#endif
static void yy_fatal_error (yyconst char* msg )
{
	(void) fprintf( stderr, "%s\n", msg );
	exit( YY_EXIT_FAILURE );
}

/* Redefine yyless() so it works in section 3 code. */
#undef yyless
#define yyless(n) \
	do { \
		/* Undo effects of setting up yytext. */ \
		int yyless_macro_arg = (n); \
		YY_LESS_LINENO(yyless_macro_arg);\
		yytext[yyleng] = (yy_hold_char); \
		(yy_c_buf_p) = yytext + yyless_macro_arg; \
		(yy_hold_char) = *(yy_c_buf_p); \
		*(yy_c_buf_p) = '\0'; \
		yyleng = yyless_macro_arg; \
	} while ( 0 )

int main(int argc, char **argv)
{
	int tok;
	while (tok = yylex()) {
		printf("%d", tok);
		if (NUMBER == tok)
			printf(" = %d\n", yylval);
		else
			printf("\n");
	}
}
