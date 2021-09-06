# pack
语法：pack("指定的格式",list)
说明：pack这个函数会将一个list变成所指定的二进制数据格式。
在CGI程序分割解码过程中，会用到pack这 个函数,所以笔者在此简单介绍这个函数的用法。
示例：$string=pack("c",65); 
这时$string="a";将65这个ascii码转换成一个unsigned字符，
其中c就是指定要转换成unsigned字符的意思。




