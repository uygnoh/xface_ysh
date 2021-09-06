
### perl test.pl f.txt
```note
f.txt
fred flintstone:2168:310 Cobbleastone Way:555-1212:555-2121:3
barney rubble  :3521:425 sobeltsssfei Day:666-5645:666-6525:2
```

```perl
while (<>) {
    chomp;
    my @items = split /:/;
    my ($card_num, $count) = ($items[1], $items[5]);
    print "$card_num\t$count\n";
}

while (<>) {
    chomp;
    my ($name, $card_num, $addr, $home, $work, $count) = split /:/;
    print "$card_num\t$count\n";
}

while (<>) {
    chomp;
    my ($card_num, $count) = (split /:/)[1, 5];
    print "$card_num\t$count\n";
}


while (<>) {
    chomp;
    my card_num = (split /:/)[1];
    my count_num = (split /:/)[5];
    print "$card_num\t$count\n";
}
```


```perl
my($dev, $ino, $mode, $nlink, $uid, $gid, \
   $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks) = stat("1.txt");
print "$mtime\n";


my($mtime) = (stat("1.txt"))[9];
print "$mtime\n";
```


my @names = qw{zero one two three four five six seven eight nine};
my($first, $last) = (sort @names)[0, -1];
print "$first, $last\n"

my @numbers = (@names)[9, 0, 2, 1, 0];
print "@numbers\n";

my @numbers = @names[9, 0, 2, 1, 0];
print "@numbers\n";


print "@names\]n";
@names[2, 6] = ("2", "6");
print "@names\n";



