# keys
语法：keys(%array)
说明：取出关联数组%ARRAY中全部的key。
示例：
%NAME=(1,"mike",2,"michael"); 
@readkey=keys(%NAMES); 
% 这时@readkey=(1,2); 


# values
语法：values(%array)
说明：取出关联数组%ARRAY中全部的value。
示例：
%NAMES=(1,"mike",2,"michael"); 
@readval=values(%NAMES); 
% 这时@readval=("mike","michael"); 
