### 使用eval捕获错误
```perl
eval语法格式：

eval {
    ...
};
if ($@) {...}
```




```perl
sub do_something {
    #....
}

foreach my $person (qw/ Fred wilma betty barney dino pebbles /) {
    eval {
        open FILE, "<$person" or die "Cant't open file '$person': $!";
        
        my($total, $count);
        
        while (<FILE>) {
            $tatal += $_;
            $count++;
        }
        
        my $average = $total / $count;
        print "Average for file $person was $average\n";
        
        &do_something($person, $average);
    }; ###此处使用eval捕获错误，在eval之后马上用if去检查是否有错误，如果发生错误这个特殊变量($@),就有错误信息
    if ($@) {
        print "An Error occured ($@), continuing\n";
    }
}
```



### eval die配合使用， 捕获错误
```perl
sub do_work {
    my $task = shift;
    if ($task < 0) {
        die("Task [$task] should be greate than zero");
    }
    $task;
}
eval {
    my $value = do_work(-9);
    
};
if ($@) {
    print "error: $@";
}

```




# die
语法：die LIST
说明：会把LIST字符串显示出来，并退出程序。常常和$!这个代表错误信息变量一起使用。
示例：open(FILE,"$filename")||die "不能打开文件$!\n; 
    如果打开文件失败的话，就会显示出错误的信息，之后再退出程序。



