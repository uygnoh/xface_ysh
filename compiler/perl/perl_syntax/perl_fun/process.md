### system 函数
```perl
for(1..10) {        ###perl语言进程(父进程)
    print $_ . "\n";
}

system("date");     ###perl语言进程创建一个子进程(perl语言进程在等待)(子进程)

for(111..100) {     ###子程序执行完，返回到perl语言进程(父进程)
    print $_ . "\n";
}
```
my $now = `date`;           ###date输出捕获到$now这个变量中
chomp(my $now = `date`);    ###去掉\n
print $now;


### 提取 `who` 信息
my @who_lines = `who`;
foreach(@who_lines) {
    
}
foreach(`who`) {
    my($user, $tty, $date) = /(\S+)\s+(\S+)\s+(.*)/;
}



### exec 函数
```perl
for(1..10) {        ###perl语言进程(父进程)
    print $_ . "\n";
}

exec("date");       ###它不会创建新的子进程，它会把原来的进程替换掉。

for(111..100) {     ###这里的语句不会执行。
    print $_ . "\n";
}
```
