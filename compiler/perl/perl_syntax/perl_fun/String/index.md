# index

语法：index($string,$substring,position) 
    $substring  ;是要寻找的字符；
    position    ;代表从哪一个位置开始寻找，假如省略position就从头开始找起。
说明：返回所要找寻的字符在一字符串$string中的位置，
    如果在字符串中找不到字符的话，则会返回-1这个 值。
    
示例：
$s=index("perl5","p");      #这时$s=0
$s=index("perl5","l",2);    #这时$s=3
$s=index("perl5","perl");   #这时$s=-1 
