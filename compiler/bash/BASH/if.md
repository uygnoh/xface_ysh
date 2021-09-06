### bash的if语句语法
```bash
if [ conditional-expression1 ]; then
    statement...
elif [ conditional-expression2 ]; then
    statement...
else
    statement...
fi
```


### bash if 例程
```bash
#!/bin/bash

if [ $1 = 1 -o  $1 = "read" ]; then
    echo "do_read"
elif [ $1 = 2 -o $1 = "write" ]; then
    echo "do_write"
else
    echo "do_other"
fi

% ./test.sh 1
do_read

% ./test.sh 2
do_write
```
