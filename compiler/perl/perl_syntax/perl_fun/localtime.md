# perl 时间函数
+ 时间起点: 1970-01-01 00:00:00 ;它以标准时间为基准
+ 标准时间: gmtime()            ;这个函数的值: 表示比时间起点过去了多少秒
+ 北京时间: locatime()          ;这个函数的值: 表示比时间起点过去了多少秒

`北京时间 = 标准时间 + 8小时`

```note
print localtime;
print "\n";
print gmtime;
print "\n";

my $now = localtime;
print $now;
print "\n";
my $now = gmtime;
print $now;
print "\n";
print scalar localtime;

```

```perl
my($sec, $min, $hour, $day, $mon, $year, $wday, $yday, $isdst) = localtime;
print (($year+1900), "年", ($mon+1), "月$day日$hour:$min:$sec\n");
```










# localtime
语法：localtime(time)
说明：可返回九个有关时间的元素，在写CGI应用程序的时候常会用到系统的时间，
所以在此会详细介绍这个函 数的用法。
示例：
`($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst)=localtime(time);`
其中： 
```note
$sec    代表秒数[0,59] 
$min    代表分数[0,59] 
$hour   代表小时数[0,23] 
$mday   代表是在这个月的第几天[1,31] 
$mon    代表月数[0,11],要将$mon加1之后，才能符合实际情况。
$year   从1990年算起的年数 
$wday   从星期六算起，代表是在这周中的第几天[0-6] 
$yday   从一月一日算起，代表是在这年中的第几天[0,365] 
$isdst  只是一个flag 知道这些变量之后，就可以在CGI应用程序中拿来应用了。
```

```
此外，也可以用下面这一行指令在UNIX系统下取得系统的时间。
为了避免错误发生，最好用绝对路径的方法来取得系统时间，
如果绝对路径不清楚的话可以用"which data"这个指令来得知。
最后要提字符的话，就不能正确执行系统的程序了。 
$data='/usr/bin/data'; 而在perl5版本中，也可以用下面这一行指令来取得系统时间。 
$data=localtime(time); 
```














