### for基本格式
```bash
for [变量] in [取值列表]
do
done
```
##### 或者使用分号; 分分割语句
`for [变量] in [取值列表]; do [各种操作]; done`



### 取值列表为空格或回车符分割的字符串
```bash
for i in 'apple' 'meat' 'sleep' 'woman'
do
    echo "I like $i"
done
```



### 迭代, 花括号 { }
+ 数字迭代，比如 {1..100}
+ ASCII字符迭代，比如 {a..A}
```bash
#!/bin/bash
# 计算丛1加到100的和
sum=0
for i in {1..10}
do
    let sum+=$i
done
echo $sum
```

+ 打印1到100以内的所有奇数
+ 花括号的迭代还可以指定指定增量，格式如下：
+ {start..end..sep}
`for i in {1..100..2}; do echo $i; done`



### 使用 seq 需要配合命令替换使用
`seq 命令的格式为: seq 首数 [增量] 末数`
+ ping -c3 ${PREFIX}${i} >& /dev/null
+ 他们的意思就是把 ping -c3 ${PREFIX}${i} 执行完输出的东西都放入/dev/null里
+ 不管出错了,还是正常ping通了,只要是输出到屏幕的信息都放入/dev/null里
```bash
#!/bin/bash
# 用脚本来ping一下局域网内的主机
PREFIX=192.168.0.
for i in `seq 100 120`
do
    echo -n "${PREFIX}$i "
    ping -c3 ${PREFIX}${i} >& /dev/null
    if [ "$?" -eq 0 ]; then
        echo "OK"
    else
        echo "Failed"
    fi
done
```


### C语言风格的循环
```bash
sum=0
for (( i=1;i<=100;i++ ))
do 
    let sum+=$i
done
echo $sum
```


### bash输入输出重定向
+ 描述符的重定向还有下面的几种用法：
+ 你可以将stderr单独定向到一个文件，将stdout重定向到另一个文件：
`cmd 2>stderr.txt 1>stdout.txt`

+ 也可以利用下面的方法，将stderr转换成stdout，使得stderr和stdout都被重新定向到同一个文件中
`cmd >output.txt 2>&1`
+ 或者采用这个方法（这个经常用到，我个人比较喜欢用这个，少写几个字符(*^__^*)
+ 两个表达式效果一样哒~
`cmd &> output.txt`
`cmd >& output.txt`



