### while循环用于重复地执行一个命令列表
```bash
while [ condition ]
    command1
    command2
    commandN
done
```


### while无限循环例程
```bash
#!/bin/bash
while :
do
    clear
    echo "================================"
    echo "1. Display date and time."
    echo "2. Display system information."
    echo "3. Display what users are doing."
    echo "4. Exit"
    echo "================================"
    read -p "Enter your choice[1--4]: " choice
    echo $choice
    
    case $choice in
        1)
            echo "Today is:      $(date +%Y-%m-%d)"
            echo "Currrent time: $(date +%H:%M:%S)"
            read -p "Press [Enter] key to continue..." readEnterKey
            ;;
        2)
            uname -a
            read -p "Press [Enter] key to continue..." readEnterKey
            ;;
        3)
            w
            read -p "Press [Enter] key to continue..." readEnterKey
            ;;
        4)
            echo "Bye!"
            exit 0
            ;;
        *)
            echo "Error: Invalid option!"
            read -p "Press [Enter] key to continue..." readEnterKey
            ;;
    esac
    
done
    
```    
    
    
    
    
    
    
