
# shift
语法：shift(@array)
说明：将数组@array的第一个元素删除，并将删除的元素返回。
示例：
@array=("one","two"); 
@rm=shift(@array);  
#这时@array=("two");而$rm="one";



# unshift
语法：unshift(@array,$string) 
说明：在数组@array的第一个元素前附加新的元素$string到数组@array中。 
示例： 
@array=("one","two"); 
unshift(@array,"three"); 
#这时@array=("three","one","two")
