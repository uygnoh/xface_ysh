# give-when 语句
```perl
use 5.010
given($x) {
    when(...) { ... }
    when(...) { ... }
    when(...) { ... }
    default { ... }
}
```

# if else
```perl
use 5.010;
my $name = $ARGV[0];
print "$name\n";

   if ($name =~ /fred/i) {say 'Name has fred in it.'}
elsif (name =~ /^Fred/)  {say 'Hame starts with Fred.'}
elsif ($name eq 'Fred')  {say 'Name is Fred.'}
else                     {say "I don't see a Fred"}


% perl test.pl fred
```



# give-when语句
```perl
use 5.010;
my $name = $ARGV[0];
given ($name) {
    when($name =~ /fred/i) {say 'Name has fred in it'}
    when($name =~ /^Fred/) {say 'Name starts with Fred'}
    when($name eq 'Fred')  {say 'Name is Fred'}
    default                {say "I don't see a Fred"}
}
```



# 全部换成智能匹配和特殊变量(~~ $_)
```perl
use 5.010;
my $name = $ARGV[0];
given ($name) {
    my $_ = $name;
    when($_ ~~ /fred/i) {say 'Name has fred in it'}
    when($_ ~~ /^Fred/) {say 'Name starts with Fred'}
    when($_ ~~ 'Fred')  {say 'Name is Fred'}
    default                {say "I don't see a Fred"}
}
```




# 智能匹配和特殊变量都可以去掉，它会自动识别它 
```perl
use 5.010;
given ($ARGV[0]) {
    when(/fred/i) {say 'Name has fred in it'}
    when(/^Fred/) {say 'Name starts with Fred'}
    when('Fred')  {say 'Name is Fred'}
    default       {say "I don't see a Fred"}
}

```


```
use 5.010;
given ($argv[2]) {
    when($_ ~~ /^-?\d+\.\d+$/) {say 'This a number!'; break}
    when($_ > 10) {say 'Number is greater than 10'}
    when($_ < 10) {say 'Number is less than 10'}
    default       {say 'Number is 10'}
}
```





