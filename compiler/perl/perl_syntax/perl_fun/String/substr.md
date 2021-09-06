# substr
语法：substr($string,offset,length)    #offset代表起始字符的位置,
    length代表引用的字符串长度，如果省略length则代表从起始值到字符串的最后一个字符长度。   
    而offset如果是负值的话，就会从字符串右边开始指定字符。
    
示例：
```
$s=substr("perl5",2,2);  #这时$s="rl";
$s=substr("perl5",2);    #这时$s="rl5";
$s=substr("perl5",-2,2); #这时$s="er"; 
```




