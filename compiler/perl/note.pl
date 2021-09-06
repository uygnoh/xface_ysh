# perl的命令行参数保存在@ARGV中，而<>以@ARGV为默认参数
# 当然可以对@ARGV进行赋值操作，以改变<>的输入文件
# 命令行的当前执行文件名保存在$0中
#
# 当@ARGV为空的时候即命令行输入为./perl5.pl(执行文件名)时，
# <>的意思为从STDIN中输入，以文件结束符为结尾。
# 当@ARGV不为空的时候，<>将后面的参数按空格区分为文件名，一个个进行打开操作
#
# <>操作符查看@ARGV来决定使用那些文件
# 如果为空，则使用标准输入流，否则使用其找到的相应的文件
# 也就是说，在启动程序之后，使用 <> 之前，还可以修改@ARGV的值
#
# 角符 <> 和 <STDIN> 的区别
# <>可以由指定的档案取得资料，而该档案的档案名可以放在命令列表中加以指定
# <STDIN>是由标准输入取得资料
#
@ARGV = qw{ larry readme }; #强制使用这2个文件
while (<>) {
    chomp;
    print "It was $_ that I saw in some stooge-like file\n";
}



### 在perl中引号不一定要写成符号
```note
    q()     #表示单引号
    qq()    #表示双引号
    qx()    #表示反引号
其中这里的括号也可以替换成其它成对的符号
    q{}     q//     q%%
    qq{}    qq//    qq%%
    qx{}    qx//    qx%%
```



## 在perl中, <STDIN>
```note
1. 读取标准输入，只能读取一行
vim test.pl
#!/usr/bin/perl
$data=<STDIN>;
print "$data";

> echo "abcdef" | perl test.pl


1. 读取标准输入，读取多行
foreach $line (<STDIN>) {
    print "$line";
}

> echo "abcd\njkfm" | perl test.pl

#和上面语法等效
    foreach $_ (<STDIN>) {
        print "$_";
    }
```

## 在perl中, <>
```note
读取文件中的数据 
我们可以将文件作为perl命令行参数，perl会使用”<>“去读取文件中的内容

foreach $_ (<>) {
    print "$_";
}

> perl test.pl /etc/passwd

#去掉默认的换行符
    foreach $_ (<>) {
        chomp $_;
        print "$_";
    }

```



### 在perl中, 匹配字符串 =~
```note
$name="aAbBcC";
if ($name =~ m/ab/i) {
    print "pre match:  $`\n";
    print "match:      $&\n";
    print "post match: $'\n";
}
```




### perl命令行加上“-e”选项，就能在perl命令行中直接写perl表达式
> echo "hello" | /usr/bin/perl -e '$name=<STDIN>;print $name;'







