# read

+ read 函数用于从缓冲区的文件句柄读取信息。
+ 这个函数用于从文件读取二进制数据。
+ read FILEHANDLE, SCALAR, LENGTH, OFFSET
+ read FILEHANDLE, SCALAR, LENGTH
参数说明:
    FILEHANDLE  文件句柄，用于存放一个文件唯一标识符。
    SCALAR      存贮结果，如果没有指定OFFSET，数据将放在SCALAR的开头。
                否则数据放在SCALAR中的OFFSET字节之后。
    LENGTH      读取的内容长度。
    OFFSET      偏移量。
如果读取成功返回读取的字节数，如果在文件结尾返回 0，如果发生错误返回 undef。 


语法：read(filehandle,$string,length) 其中length是代表读入字符串的长度(bytes)。
说明：用read这个函数把filehandle中的数据依指定的字符串长度读入之后指派给$string这个变量。
在cgi程序分割解码过程中，如果FORM的传送方式是设定为POST的话，就会将传送的数据设定为标准输入，
所以会将数据内容指定给STDIN这个标准输入的filehandle，
而CGI环境变量$env{'content_length'}就是代 表使用者送出数据内容的长度，
因此我们要用read这个函数来取得使用者送出的数据内容。
示例：read(stdin,$buffer,$env{'content_length'}); 
就会将stdin这个标准输入filehandle中的数据依指定的字符串长度读入，再指派给$buffer这个变量。

