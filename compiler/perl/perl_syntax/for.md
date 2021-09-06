### for, foreach
```perl
for (1..10) {
    print "$_\n";
}


foreach $i (1..10) {
    print "foreach: $i\n";
}

@a = (1..10);
for(@a) {
    print "$_\n";
}


foreach $pal ('tom', 'jack', 'mob') {
    print "hi $pal!\n";
}


for $pal ('tom', 'jack', 'mob') {
    print "hi $pal!\n";
}


for ('tom', 'jack', 'mob') {
    print "hi $_!\n";
}
```


### while
```perl
$num = 1;
while ($num <=10) {
    print "$num\n";
    $num++;
}


$num = 1;
until ($num == 10) {
    print "$num\n";
    $num++;
}


$num = 1;
do {
    print "do-while: $num\n";
    $num++;
} while ($num <=10);
```



### 循环条件修饰符
+ last 结束循环(break)
+ next 提前进入下一步循环(continue)
+ redo 重作当前的循环， 它不++，也不判断循环条件
```perl
for ($i=0; $i<6; $i++) {
    print "$i\n";
    print "$i\n";
    if ($i == 3) {last;}
    if ($i == 3) {next;}
    if ($i == 3) {redo;}    # 此处会进入死循环
    print "$i\n";
    print "$i\n";
}
```
打字练习demo,redo: 重作当前的循环 
```perl
my @words = qw{Fred Barney pebles dino wilma betty};
my $errors = 0;
foreach (@words) {
    print "Type the word '$_':";
    chomp(my $try=<STDIN>);
    if ($try ne $_) {
        print "Sorry - That's not right.\n\n";
        $errors++;
        redo;
    }
}
```


```perl
while (<>) {
    if (/__END__/) {
        last;
    } elsif (/Harry Potter/) {
        print;
    }
}
```


### 计算单词总数
```perl
while (<>) {
    foreach (split) {
        $total++;
        next if /\W/;
        $valid++;
        $count{$_}++;
    }
}
print "$total\n";
print "$valid\n";
foreach $word(sort keys %count) {
    print "$word was seen $cont{$word} time."
}
```



+ last标签
+ next标签
+ redo标签
+ 如果我们要控制内层循环，就不需要用到标签
+ 如果我们要控制多重循环最外层的循环，就需要用到标签
OUT: for ($i=0; $i<5; $i++) {
    for ($j=0; $j<4; $j++) {
        print "$i, $j\n";
        if ($i==2 && $j==2) {
            last OUT;
        }
        
    }
}



### 条件语句修饰词
$n = -99;
if ($n<0) {
    print "$n is a negative number.\n";
}



+ if $n < 0; 它是词句修饰词
```perl
$n = -99;
print "$n is a negative number. \n" if $n < 0;
```



```perl
sub error {
    my($msg) = shift @_;
    print "Error: " . $msg . "\n";
}

sub valid {
    my($input) = shift @_;
    if ($input =~ /^[0-9]+$/) {
        return 1;
    } else {
        return 0;
    }
    
}
    
print "输入一个数：";
chomp($input = <STDIN>);
unless(&valid($input)) {
    &error("Invalid input");
}


&error("Invalid input") unless &valid($input);
```




# 循环修语句饰词
```perl
$x = 0;
while ($x != 5) {
    print $x++, "\n";
}


$x = 0;
print $x++, "\n" while $x != 5;


$x = 1;
until ($x == 5) {
    print $x++, "\n";
}
$x = 1;
print $x++, "\n" until $x == 5;


@alpha = (a..z, "\n");
foreach (@alpha) {
    print;
}
print foreach @alpha;
```





