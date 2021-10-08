1 #include <stddef.h>
2 #include <stdlib.h>
3 #include <stdio.h>
4 
5 extern void (*__preinit_array_start []) (void) __attribute__((weak));
6 extern void (*__preinit_array_end []) (void) __attribute__((weak));
7 extern void (*__init_array_start []) (void) __attribute__((weak));
8 extern void (*__init_array_end []) (void) __attribute__((weak));
9 extern void (*__fini_array_start []) (void) __attribute__((weak));
10 extern void (*__fini_array_end []) (void) __attribute__((weak));
11 
12 void _init();
13 void _fini();
14 void _exit(int return_code) __attribute__((noreturn));
15 
16 
17 static void __libc_init_array() {
18     size_t count, i;
19     
20     count = __preinit_array_end - __preinit_array_start;
21     for (i = 0; i < count; i++)
22         __preinit_array_start[i]();
23     
24     _init();
25 
26     count = __init_array_end - __init_array_start;
27     for (i = 0; i < count; i++)
28         __init_array_start[i]();
29 }
30 
31 static void __libc_fini_array() {
32     size_t count, i;
33     
34     count = __preinit_array_end - __preinit_array_start;
35     for (i = count - 1; i >= 0; i--)
36         __fini_array_start[i]();
37     
38     _fini();
39 }
40 
41 #define MAX_ATEXIT 32
42 
43 static volatile uint8_t atexit_count = 0;
44 static volatile atexit_func_t atexit_funcs[MAX_ATEXIT];
45 
46 int atexit(atexit_func_t func) {
47     uint8_t pos = __sync_fetch_and_add(&atexit_count, 1);
48     
49     if (pos >= MAX_ATEXIT) {
50         atexit_count = 32;
51         return -1;
52     }
53     
54     atexit_funcs[pos] = func;
55     return 0;
56 }
57 
58 void exit(int return_code) {
59     uint8_t i;
60     
61     for (i = 0; i < atexit_count; i++) {
62         atexit_funcs[i]();
63     }
64     
65     __libc_fini_array();
66     _exit(return_code);
67 }
68 
69 void libc_init() {
70     __sinit(_impure_ptr);
71     __libc_init_array();
72 }


