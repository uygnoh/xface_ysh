# perl 文件名通配
新的写法
```perl
my @files = glob "*.txt *.jpg";

foreach (@files) {
    print $_ . "\n";
}
```
旧的写法
```perl
my @files = <*.txt *.jpg">;

foreach $_ (@files) {
    print $_ . "\n";
}
```



# perl 删除文件
```note
1. 删除文件: unlink "1.txt", "2.txt";
2. 删除所有文件: unlink glob "*.txt";
```
my $successful = unlink "1.txt", "2.txt";
print "I deleted $successful files just now\n";

使用循环一个一个地删除文件并且检查是否有删除失败的
```perl
foreach my $files (glob "*.txt") {
    unlink $file or warn "Failed on $files: $!\n";
}
```




# perl 重命明文件
rename "1.txt", "new_txt";
remame "1.txt", "new_folder/new_txt";




# perl 修改文件时间标记
```perl
my $now = localtime;
my $yesterday = $now - 24*60*60;
utime $now, $yesterday, glob "*,txt";

把最后访问的时间改为$now; 把最后修改的时间改为$yesterday; 后面是要匹配的文件名;

```


















