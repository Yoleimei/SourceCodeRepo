RE  - Regular Expression               - 正则表达式 
NFA - Nondeterministic Finite Automata - 不确定的有限自动机 - 有一条或多条离开该状态的，以输入符号为标号的边，空串ε也可以作为标号
DFA - Deterministic Finite Automata    - 确定的有限自动机   - 有且只有一条离开该状态的，以输入符号为标号的边

RE -> NFA -> DFA
RE -> NFA: Thompson 算法

DFA由5部分构成
	>> 字母表，符号的有限集合
	>> 状态的有限集合
	>> 开始状态
	>> 接受状态
	>> 状态转移矩阵

