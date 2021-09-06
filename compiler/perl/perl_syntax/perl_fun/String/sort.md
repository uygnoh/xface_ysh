# sort

语法：sort(@array)
说明：将数组中的元素由小到大排序，
     如果要由大到小排序的话，要加上reverse这个函数。
示例：1
```
@abc=("d","b","c","a"); 
@abc=sort(@abc); 
这时@abc=("a","b","c","d");
```
示例：2
```
@abc=(reverse sort@abc); 
这时@abc=("d","c","b","a"); 
这个语法也可以写成@abc=(reverse sort(@abc));
```
示例：3
```
@number=(5,2,10); 
@number=sort(@number); 
上面示例用sort函数来排序数值的时，会出差错，因此要用下面到下面这一句。 
@number=(sort{$a<=>$b}@number);
这时@number=(2,5,10);
```
