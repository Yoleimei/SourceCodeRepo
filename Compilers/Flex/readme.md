01. Flex�ṹ�淶
flex�����������ֹ���: ���岿�֡����򲿷ֺ��û�������
...���岿��... (����)          - ������C�ļ���
%%
...���򲿷�... (����)          - ������yylex()��
%% (�������û�������һ��ʡ��)
...�û�������... (����ʡ��)

02. 
����:
yylex()                 - ���������¿�ʼɨ��
yyrestart()             - �Ӵ򿪵ı�׼��������ļ�f����ȡ����
yywrap()                - �����ļ�ĩβʱ�����л��ļ�
yyless()                - �ƻؼǺŵ�ǰn���ַ�
yymore()                - ����һ���Ǻ�Ҳ��ӵ���ǰ�Ǻ���
yyterminate()           - ��һ�������д���return������ɨ�貢��ɨ�����ĵ����߷���0
yy_create_buffer()      - ����������
yy_switch_to_buffer()   - ʹ�ô����Ļ�����
yy_flush_buffer()       - ����������������
yy_init_buffer()        - ��ʼ��������
yy_delete_buffer()      - �ͷŻ�����
yy_scan_bytes()         - �����ֽ�������
yy_scan_string()        - �����Կ��ַ���β���ַ�������
yy_scan_buffer()        - �����ֽ���
yypush_buffer_state()   - �л������������Ѿɻ�����ѹ���ջ
yypop_buffer_state()    - ɾ����ǰ������������ʹ����һ��������
yyensure_buffer_stack() - ����ջ
����:
yyin                    - ����������
yyout                   - ���������
yytext                  - ������ʽƥ�䵽��token
yyleng                  - ������ʽƥ�䵽��token�ĳ���
yylineno                - ��ǰ�к�
����:                   
YY_BUFFER_STATE         - ָ��flex���뻺������ָ������
�궨��                  
ECHO                    - ��yytext���Ƶ�����ļ���
BEGIN                   - ���һ����ʼ״̬������ɨ������λ����Ӧ�Ŀ�ʼ״̬��
REJECT                  - ��ɨ������Ե�ǰ���������ȥƥ����ŵĹ���

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

����ʱ��-Cf��������ֻ������ yy_ntx �� yy_accept 
�������-Cf������������ɶ�����飬������ʵ��һ����