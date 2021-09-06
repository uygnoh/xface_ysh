### bash的case语句用法规则
```bash
case ${VAR} in
    pattern1)
        commands1
        ;;
    pattern2)
        commands2
        ;;
esac
```


## 注意的是, case比较的是pattern，既然是通配符，那么：
+ 切记通配符本身不能用引号括起来。
+ 而对于变量VAR是否使用双引号括起来都可以。
+ 另外要记住通配符(pattern)和规则表达式(regular expression)的区别



### 例子1, 一般用法, 匹配
```bash
#!/bin/bash

VAR="AABB"
case "${VAR}" in
    AABB)
        echo "match"
        ;;
    *)
        echo "unmatch"
        ;;
esac
```


### 例子2, 一般用法, 不匹配
```bash
#!/bin/bash

VAR="AABB"
case "${VAR}" in
    AB)
        echo "match"
        ;;
    *)
        echo "unmatch"
        ;;
esac
```

### 例子3, 通配符
```bash
#!/bin/bash

VAR="AABB"
case "${VAR}" in
    *AB*)
        echo "match"
        ;;
    *)
        echo "unmatch"
        ;;
esac

输出：match
AABB匹配通配符'*AB*'，其中：
'*' 代表任何多个(或者0个)普通字符。
'?' 代码任意一个普通字符。

```


### 例子4, 使用双引号
```bash
#!/bin/bash

VAR="AABB"
case "${VAR}" in
    "*AB*")
        echo "MATCH" 
        ;;
    *)
        echo "UNMATCH" 
        ;;
esac

输出：UNMATCH
我们说过，case语句匹配的是通配符，如果加上双引号后就不是按通配符处理，而是按文本处理。
使用双引号后通配符就不再生效 ，只是作为普通字符对待。
```

```bash
#!/bin/bash

VAR="AABB"
case "${VAR}" in
    "AABB")
        echo "MATCH" 
        ;;
    *)
        echo "UNMATCH" 
        ;;
esac

输出：MATCH
```
