### 为顶层目录创建  autogen.sh文件 {vim autogen.sh}
### ================================================
#!/bin/bash
### ./configure CFLAGS="-Wall -g"
aclocal
autoconf
automake --add-missing
### CC=arm-linux-gcc CFLAGS="-Wall -g" ./configure --host=arm-linux
./configure
