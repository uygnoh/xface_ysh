#  grep
```perl
# 打印1到100中所有的奇数
my @odd_numbers;
foreach(1..100) {
    push @odd_numbers, $_ if $_ % 2;
}
print "@odd_numbers\n";
```

```perl
print "\n\n";
my @odd = grep $_ % 2, 1..100;
print "@odd\n";

print "\n\n";
my @odd = grep {$_ % 2} 1..100;
print "@odd\n";
```





