#!/bin/bash

### 安装vim-plug插件
mkdir ~/.vim/autoload
cp ~/Documents/GIT_HUB/utilities/textedit/vim/vim_plug/vim_plugin/plug.vim ~/.vim/autoload/

### vim安装配色主题 ->molokai
mkdir ~/.vim/colors/
cp ~/Documents/GIT_HUB/utilities/textedit/vim/vim_plug/molokai/molokai.vim ~/.vim/colros/

### vim配置文件安装
cp ~/Documents/GIT_HUB/profiles/vim/vimrc ~/.vimrc
