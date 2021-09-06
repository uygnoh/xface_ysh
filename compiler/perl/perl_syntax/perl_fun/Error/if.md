### if 判断语句的返回值

```perl
if(open(DATA, $file)){
   ...
}else{
   die "Error: 无法打开文件 - $!";
}

程序中变量 $! 返回了错误信息。 我们也可以将以上代码简化为如下代码：
open(DATA, $file) || die "Error: 无法打开文件 - $!";
```


### unless 函数
+ unless 函数与 if 相反，只有在表达式返回 false 时才会执行，如下所示：
unless(chdir("/etc")){
   die "Error: 无法打开目录 - $!";
}
+ unless 语句在你要设置错误提醒时是非常有用的。我么也可以将以上代码简写为：
+ 以下错误信息只有在目录切换错误的情况下才会输出。
`die "Error: 无法打开目录!: $!" unless(chdir("/etc"));`


### 三元运算符
+ 以下是一个三元运算符的简单实例:
`print(exists($hash{value}) ? '存在' : '不存在',"\n");`
+ 以上实例我们使用了三元运算符来判断哈希的值是否存在。
+ 实例中包含了一个表达式两个值，格式为：
`表达式 ? 值一 : 值二`



### exit
语法： exit
说明： 退出执行的程序。
示例： print"i love cgi\n"; exit; 
      显示完"i love cgi"以后，将退出这个程序。
