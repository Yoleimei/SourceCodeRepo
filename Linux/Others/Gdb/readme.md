gcc xx.c -o xx -g
-tui - text user interface
(gdb) file <filename>         - 加载可执行程序
(gdb) r                       - Run
(gdb) c                       - Continue
(gdb) b <line-num>            - BreakPoint
(gdb) b <function-name>       - BreakPoint
(gdb) d <number>              - Delete BreakPoint
(gdb) s                       - Step Into
(gdb) n                       - Step Over
(gdb) p <variable-name>       - Print variable
(gdb) q                       - Quit
(gdb) display <variable-name> - 记录变量，在单步执行的时候都会显示
