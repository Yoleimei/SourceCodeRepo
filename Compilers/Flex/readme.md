01. Flex结构规范
flex程序有三部分构成: 定义部分、规则部分和用户子例程
...定义部分... (必需)          - 拷贝到C文件中
%%
...规则部分... (必需)          - 拷贝到yylex()中
%% (可以与用户子例程一起省略)
...用户子例程... (可以省略)

02. 
函数:
yylex()                 - 启动或重新开始扫描
yyrestart()             - 从打开的标准输入输出文件f来读取输入
yywrap()                - 到达文件末尾时，来切换文件
yyless()                - 推回记号的前n个字符
yymore()                - 把下一个记号也添加到当前记号中
yyterminate()           - 在一个动作中代替return，结束扫描并向扫描器的调用者返回0
yy_create_buffer()      - 创建缓冲区
yy_switch_to_buffer()   - 使用创建的缓冲区
yy_flush_buffer()       - 放弃缓冲区的内容
yy_init_buffer()        - 初始化缓冲区
yy_delete_buffer()      - 释放缓冲区
yy_scan_bytes()         - 分析字节流拷贝
yy_scan_string()        - 分析以空字符结尾的字符串拷贝
yy_scan_buffer()        - 分析字节流
yypush_buffer_state()   - 切换缓冲区，并把旧缓冲区压入堆栈
yypop_buffer_state()    - 删除当前缓冲区，继续使用上一个缓冲区
yyensure_buffer_stack() - 分配栈
变量:
yyin                    - 输入描述符
yyout                   - 输出描述符
yytext                  - 正则表达式匹配到的token
yyleng                  - 正则表达式匹配到的token的长度
yylineno                - 当前行号
类型:                   
YY_BUFFER_STATE         - 指向flex输入缓冲区的指针类型
宏定义                  
ECHO                    - 将yytext复制到输出文件中
BEGIN                   - 后跟一个开始状态名，将扫描器定位到对应的开始状态处
REJECT                  - 是扫描器针对当前的输入继续去匹配次优的规则

yylex() {
	yyensure_buffer_stack();
	yy_create_buffer();
	yy_load_buffer_state();
	yy_get_previous_state();
	yy_try_NUL_trans();
	yy_get_next_buffer();
}
yy_create_buffer() {
	yy_init_buffer();
}
yy_init_buffer() {
	yy_flush_buffer();
}
yy_flush_buffer() {
	yy_load_buffer_state();
}

编译时带-Cf参数，则只会生成 yy_ntx 和 yy_accept 
如果不带-Cf参数，则会生成多个数组，方法其实是一样的