##### 系统可用的shell
+ cat /etc/shells

##### 登陆的shell
+ login shell; 登陆shell使用 ysh@localhost:~$ su - alice
+ {/etc/profile, /etc/bashrc, ~/.profile, ~/.bashrc} ;登陆的shell,这4个文件都执行

##### 非登陆的shell
+ nologin shell; 非登陆shell使用 ysh@localhost:~$ su alice
+ {/etc/bashrc, ~/.bashrc} ;非登陆的shell,它只执行这2个文件

##### bash shell下的配置文件位置
+ /etc/profile    系统级配置文件*
+ /etc/bashrc     系统级配置文件*
+ ~/.profile      用户级配置文件
+ ~/.bashrc       用户级配置文件
+ ~/.bash_logout  离开shell写入~
+ ~/.bash_history 离开shell写入~

##### linux文件备份 
+ cp /var/log/messages{, .bak}

##### base64
+ Base64是网络上最常见的用于传输8Bit字节码的编码方式之一
+ Base64就是一种基于64个可打印字符来表示二进制数据的方法

##### 输入输出重定向 <ls -l  /dev/std*>
+ <, <<;输入重定向(覆盖,append) or >, >>;输出重定向(覆盖,append)
+ cat </etc/passwd >a.password ;把/ect/passwd文件重定向到a.password
+ 1>file_name_ok  ;重定向正确输出到文件file_name_ok中
+ 2>file_name_err ;重定向错误输出到文件file_name_ok中
+ &>file_name     ;正确输出和错误输出重定向到file_name中
+ &>/dev/null     ;正确输出和错误输出重定向到/dev/null中
+ 2>&1            ;将标准错误输出重定向到标准输出
+ nohup java -jar app.jar >log 2>&1 &
`每次都写”>log 2>&1”太麻烦，能简写吗？ 简写方式:   &>log`

##### bash< && || 运算符>
+ command1 && command2
`只有在 && 左边的命令返回真（命令返回值 $? == 0），&& 右边的命令才会被执行`
+ command1 || command2
`只有在 || 左边的命令返回假（命令返回值 $? == 1），|| 右边的命令才会被执行`
+ ping -c3 www.baidu.com &>/dev/null && echo "is up" || echo "is down"

##### alias
+ 列出文件大小
    `alias lt='ls --human-readable --size -1 -S --classify'`
+ 增加一个复制进度条
    `alias cpv='rsync -ah --info=progress2'`
+ 手动去除这些行尾的空格是一件头大的事情，但对于sed来说不过是举手之劳
 `sed 's/[ \t]*$//g' your_code.c`

##### bash命令行提示符修改
+ 如果将以下内容放入 root 的家目录中的 .bashrc 文件中
+ 你将看到一个黑色背景上的红色的 root 提示符
+ 清楚地表明你（或其他任何人）应该谨慎行事
`export PS1="\[$(tput bold)$(tput setab 0)$(tput setaf 1)\]\u@\h:\w # \[$(tput sgr0)\]"`

##### 命令行参数的风格
+ dd if=sysdisk.img of=/dev/sdb
+ find src -name ’*.c’ -type f -exec dos2unix --keepdate {} \;
+ gcc -O0 -Wall -g -masm=intel -Wa,-ahl -c shudu.c
+ ls --classify --all --size --human-readable --width=80 /home/jiang 
+ ls -Fashw80 /home/jiang
+ ls -F -a -s -h -w 80 /home/jiang
+ ls -F -w80 /home/jiang -has




```note 

#################################################
#                                               #
# F11			;Screen Full                    #
#                                               #
# Super+L		;Lock Screen                    #
# Super+H		;Hide window                    #
# Super+Up		;Maximize window                #
# Super+Left	;View split on left             #
# Super+right	;View split on right            #
#                                               #
# Alt+F2		;Show the run command prompt    #
# Alt+F4		;Close window                   # 
#                                               #
# Ctrl+Shitf++	;Increase font size             #
# Ctrl+-		;Decrease font size             #
# Ctrl+7		;turn terminal                  #
# Ctrl+H		;Display hidden files           #
# Ctrl+C		;Keyboard interrupt             #
# Ctrl+D		;echo <<-EOF                    #
# Ctrl+Z        ;Stop the process[background]   #   
# Ctrl+/        ;Send SIGQUIT 3 [foreground]    #
# Ctrl+S        ;Interrupt console output       #
# Ctrl+Q        ;Recovery console output        #
# Ctrl+L        ;clear                          #
#                                               #
#################################################

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"                                                                        "
" 窗口切换 vim <===>Buffer              tmux<===>Shift+arrow              "
" 窗格切换 vim <===>Ctrl+arrow          tmux<===>Alt+arrow                "
" 分屏操作 vim <===>:split, :vsplit     tmux<===> PREFIX+h, PREFIX+v      "
"                                                                        "
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 
" 参考文件位置: /home/ysh/Documents/FREEYSH/readme.md
" Vim 中的 Buffer 是文件在内存中的缓存数据，一个 Buffer 总是也只能是对应一个文件
" :ls   :buffer number  :buffer next    :buffer previous   <buffer == b> 
"
" tmux Ctrl+b激活控制台；此时以下按键生效, PREFIX = Ctrl+a自定义方式
" tmux 使用C/S模型构建, 包括的单元模块有 server, session, window, panel
" tmux new-session -s <session_name> 创建一个新的会话
" 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
source ~/Documents/FREEYSH/profiles/aVIMRC/vimrc  
  



" vim ~/.bashrc
" export ysh=/home/ysh/Documents/FREEYSH
" cd; . .bashrc
"
```

#################################################
#                                               #
# F11			;Screen Full                    #
#                                               #
# Super+L		;Lock Screen                    #
# Super+H		;Hide window                    #
# Super+Up		;Maximize window                #
# Super+Left	;View split on left             #
# Super+right	;View split on right            #
#                                               #
# Alt+F2		;Show the run command prompt    #
# Alt+F4		;Close window                   # 
#                                               #
# Ctrl+Shitf++	;Increase font size             #
# Ctrl+-		;Decrease font size             #
# Ctrl+7		;turn terminal                  #
# Ctrl+H		;Display hidden files           #
# Ctrl+C		;Keyboard interrupt             #
# Ctrl+D		;echo <<-EOF                    #
# Ctrl+Z        ;Stop the process[background]   #   
# Ctrl+/        ;Send SIGQUIT 3 [foreground]    #
# Ctrl+S        ;Interrupt console output       #
# Ctrl+Q        ;Recovery console output        #
# Ctrl+L        ;clear                          #
#                                               #
#################################################

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"                                                                        "
" 窗口切换 vim <===>Buffer              tmux<===>Shift+arrow              "
" 窗格切换 vim <===>Ctrl+arrow          tmux<===>Alt+arrow                "
" 分屏操作 vim <===>:split, :vsplit     tmux<===> PREFIX+h, PREFIX+v      "
"                                                                        "
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


