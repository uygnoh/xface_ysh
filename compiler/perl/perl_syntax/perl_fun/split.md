# split 操作符
+ split用于拆分字符串， 被拆分的字符串它存储在一个数组中
+ 如果字符串数据有空白的，它的前面的部分会保留，中间的也保留，它的后面的部分去掉
+ /\s+/用任意的空白作为分隔符，它得到的是一个 一个单词
+ $_用上了特殊变量 
+  /\s+/ 为split默认的正则表达式 
```perl
@fields = split /:/, "abc:def:g:H";
foreach (@fields) {
    print "$_\n";
}


@fields = split /:/, ":::::abc:::def:g:H:::::::";
foreach (@fields) {
    print "$_\n";
}


my $some_input = "This is a \t      test.  \n";
my @args = split /\s+/, $some_input;
foreach(@args) {
    print "$_\n";
}


$_ = "This is a \t      test.  \n";
my @args = split /\s+/;
foreach(@args) {
    print "$_\n";
}

$_ = "This is a \t      test.  \n";
my @args = split;
foreach(@args) {
    print "$_\n";
}

```


# join 函数
+ 把数组中的数连接起来变成一个字符串，在连接的时候用“：”放在字符串与字符串中间 
+ 它可以用各种各样的字符，不一定是“：”
```perl

@x = (1,2,3,4);
$y = join ":", @y;
print "$y\n";
```






