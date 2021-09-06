# push
语法：push(@array,$string)
说明：在数组@array的最后附加新的元素 ($string)到数组@array中。
示例：@array=("one","two"); push(@array,"three"); 
    #这时$@array=("one","two","three")
    
    
# pop
语法：pop(@array)
说明：将数组(@array)的最后一个元素删除，并将删除的元素返回。
示例：@array=("one","two"); $rm=pop(@array); 
    #这时@array=("one");而$rm="two";
