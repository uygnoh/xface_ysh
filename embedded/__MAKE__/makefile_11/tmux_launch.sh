#!/bin/sh

SESSION=STM32

tmux new-session -d -s $SESSION                 ### 创建一个新的会话

tmux new-window -t $SESSION:1 -n 'user'         ### 创建第1个新的窗口“user”
tmux new-window -t $SESSION:2 -n 'bsp'          ### 创建第2个新的窗口“bsp”
tmux new-window -t $SESSION:3 -n 'stm32_doc'    ### 创建第3个新的窗口“STM32_DOC”    
tmux new-window -t $SESSION:4 -n 'stm32f10x'    ### 创建第3个新的窗口“STM32_DOC”    

tmux select-window -t $SESSION:1 
tmux send-keys 'cd user' C-m
tmux select-window -t $SESSION:2
tmux send-keys 'cd bsp' C-m
tmux select-window -t $SESSION:3
tmux send-keys 'cd STM32_DOC' C-m
tmux select-window -t $SESSION:4
tmux send-keys 'cd include' C-m

tmux select-window -t $SESSION:1
tmux send-keys 'vim main.c ' C-m
tmux attach-session -t $SESSION                 ### 连接会话   
