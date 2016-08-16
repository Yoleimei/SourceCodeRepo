%option noyywrap nodefault yylineno

%x COMMENT
%x IFILE

/* 通用字符名 */
UCN  (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
/* 浮点数指数部分 */
EXP  ([Ee][-+]?[0-9]+)
/* 整数长度 */
ILEN ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)

%{
	/* 符号表 */
	struct symbol {
		struct ref *reflist;
		char *name;
	};
	
	struct ref {
		struct ref *next;
		char *filename;
		int flags;
		int lineno;
	};
	
	#define NHASH 9997
	struct symbol symtab[NHASH];          // 哈希表，线性探测
	struct symbol *lookup(char*);         // 查找符号 
	void addref(int, char*, char*, int);  // 将 ref 添加到对应符号表
	char *curfilename;
	
	/* 文件堆栈 */
	struct bufstack {
		struct bufstack *prev;
		YY_BUFFER_STATE bs;
		int lineno;
		char *filename;
		FILE *f;
	} *curbs;
	
	int newfile(char *fn);
	int popfile(void);
	int defining;
%}

%%

 /* 注释 */
"/*"					{ BEGIN(COMMENT); }
<COMMENT>"*/"			{ BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.	{ /* ignore */ }
<COMMENT><<EOF>>		{ printf("%s:%d: Unterminated comment\n", curfilename, yylineno); return 0; }
"//".*\n

 /* 声明关键字 */
_Bool |
_Complex |
_Imaginary |
auto |
char |
const |
double |
enum |
extern |
float |
inline |
int |
long |
register |
restrict |
short |
signed |
static |
struct |
typedef |
union |
unsigned |
void |
volatile	{ defining = 1; }

 /* 关键字 */
break
case
continue
default
do
else
for
goto
if
return
sizeof
switch
while

 /* 整数 */
0[0-7]*{ILEN}?
[1-9][0-9]*{ILEN}?
0[Xx][0-9a-fA-F]+{ILEN}?

 /* 十进制浮点数 */
([0-9]*\.[0-9]+|[0-9]+\.){EXP}?[flFL]?
[0-9]+{EXP}[flFL]?
 /* 十六进制浮点数 */
0[Xx]([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]?

 /* 字符常量 */
\'([^'\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})+\'
 /* 字符串常量 */
L?\"([^"\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})*\"

 /* 标点符号 */
"{"|"<%"|";"	{ defining = 0; }
"["|"]"|"("|")"|"{"|"}"|"."|"->"
"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"
"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"
"?"|":"|";"|"..."
"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="
","|"#"|"##"
"<:"|":>"|"%>"|"%:"|"%:%:"

 /* 标识符 */
([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*	{ addref(yylineno, curfilename, yytext, defining); }

 /* 空白字符 */
[ \t\n]+

 /* 续行符 */
\\$

 /* 预处理器 */
"#"" "*if.*\n
"#"" "*else.*\n
"#"" "*endif.*\n
"#"" "*define.*\n
"#"" "*line.*\n

 /* 识别包含文件 */
^"#"[ \t]*include[ \t]*[\"<]	{ BEGIN IFILE; }
<IFILE>[^>\"]+					{
									{
										int c;
										while ((c=input()) && c!='\n');
									}
									newfile(strdup(yytext));
									BEGIN INITIAL;
								}
<IFILE>.|\n						{
									fprintf(stderr, "%s:%d bad include line\n", curfilename, yylineno);
									BEGIN INITIAL;
								}
<<EOF>>							{
									if (!popfile())
										yyterminate();
								}

 /* 无效字符 */
.								{
									printf("%s:%d: Mystery character '%s'\n", curfilename, yylineno, yytext);
								}

%%

// 检测两个符号表是否为同一个
static int symcompare(const void *xa, const void *xb)
{
	const struct symbol *a = xa;
	const struct symbol *b = xb;
	if (!a->name) {
		if (!b->name)
			return 0;
		return 1;
	}
	if (!b->name)
		return -1;
	return strcmp(a->name, b->name);
}

// 打印符号表中的引用
void printrefs()
{
	struct symbol *sp;
	qsort(symtab, NHASH, sizeof(struct symbol), symcompare);
	
	for (sp=symtab; sp->name && sp < symtab+NHASH; sp++) {
		char *prevfn = NULL;
		
		struct ref *rp = sp->reflist;
		struct ref *rpp = 0;
		struct ref *rpn;
		
		do {
			rpn = rp->next;
			rp->next = rpp;
			rpp = rp;
			rp = rpn;
		} while(rp);
		
		printf("%10s", sp->name);
		for (rp=rpp; rp; rp=rp->next) {
			if (rp->filename==prevfn) {
				printf(" %d", rp->lineno);
			} else {
				printf(" %s:%d", rp->filename, rp->lineno);
				prevfn = rp->filename;
			}
			if (rp->flags & 01)
				printf("*");
		}
		printf("\n");
	}
}

// 哈希算法
static unsigned symhash(char *sym)
{
	unsigned int hash = 0;
	unsigned c;
	while (c = *sym++)
		hash = hash * 9 ^ c;
	return hash;
}

// 查找符号表
struct symbol * lookup(char *sym)
{
	struct symbol *sp = &symtab[symhash(sym)%NHASH];
	int scount = NHASH;
	
	while (--scount >= 0) {
		if (sp->name && !strcmp(sp->name, sym))
			return sp;
			
		if (!sp->name) {
			sp->name = strdup(sym);
			sp->reflist = 0;
			return sp;
		}
		
		if (++sp >= symtab+NHASH)
			sp = symtab;
	}
	fputs("symbol table overflow\n", stderr);
	abort();
}

// 将引用添加到符号表
void addref(int lineno, char *filename, char *word, int flags)
{
	struct ref *r;
	struct symbol *sp = lookup(word);
	
	if (sp->reflist &&
		sp->reflist->lineno == lineno &&
		sp->reflist->filename == filename)
		return;
		
	r = malloc(sizeof(struct ref));
	if (!r) {
		fputs("out of space\n", stderr);
		abort();
	}
	r->next = sp->reflist;
	r->filename = filename;
	r->lineno = lineno;
	r->flags = flags;
	sp->reflist = r;
}

int main(int argc, char **argv)
{
	int i;
	
	if (argc < 2) {
		fprintf(stderr, "need filename\n");
		return 1;
	}
	for (i = 1; i < argc; i++) {
		if (newfile(argv[i]))
			yylex();
	}
	printrefs();
	return 0;
}

int newfile(char *fn)
{
	FILE *f = fopen(fn, "r");
	struct bufstack *bs = malloc(sizeof(struct bufstack));
	
	if (!f) {
		perror(fn);
		return 0;
	}
	if (!bs) {
		perror("malloc");
		exit(1);
	}
	if (curbs)
		curbs->lineno = yylineno;
	bs->prev = curbs;
	
	bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
	bs->f = f;
	bs->filename = fn;
	yy_switch_to_buffer(bs->bs);
	curbs = bs;
	yylineno = 1;
	curfilename = fn;
	return 1;
}

int popfile(void)
{
	struct bufstack *bs = curbs;
	struct bufstack *prevbs;
	
	if (!bs)
		return 0;
		
	fclose(bs->f);
	yy_delete_buffer(bs->bs);
	
	prevbs = bs->prev;
	free(bs);
	
	if (!prevbs)
		return 0;
		
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	return 1;
}
