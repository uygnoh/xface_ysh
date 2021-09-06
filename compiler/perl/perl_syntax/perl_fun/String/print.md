# print
```
语法：print Filehandle LIST
说明：这个Filehandle可以看作在I(INPUT)/O(OUTPUT)之间的一个桥梁,
% 在为大家介绍PRINT这个函数之前,先让我们来看看PRINT函数中特殊打印字符： 
    符号     其作用
    \n      换行 new line
    \r      光标换行 return
    \t      tab键
    \f      换页 form feed
    \b      退回一格
    \v      垂直tab键
    \a      响铃Bell
    \e      escape键
    \007    十进制ASC II码
    \xff    十六进制码
    \c[     控制字符
```



# chop, chomp
+ 指令：chop 语法：chop($url)
+ 说明：把最后一个字符删除。
示例：     
+ $url="www.nease.net/~zmd/";
+ chop($url); 
这时$url="www.nease.net/~zmd"
而这两行也可以写成chop($url="www.nease.net/~zmd/");

`chop; 是用来删除最后一个字符, chomp; 是用来删除换行符`



# say

