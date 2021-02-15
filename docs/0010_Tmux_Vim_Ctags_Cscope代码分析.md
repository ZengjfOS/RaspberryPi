# Tmux Vim Ctags Cscope代码分析

在Linux命令行如何阅读代码？

## 参考文档

* http://cscope.sourceforge.net/cscope_maps.vim
* [How to let cscope use absolute path in cscope.out file?](https://stackoverrun.com/cn/q/450057)

## Tmux分屏

* cat ~/.tmux.conf
  ```
  set -g default-terminal "screen-256color"
  set -g history-limit 10000

  # Easy config reload
  bind r source-file ~/.tmux.conf \; display-message "tmux.conf reloaded"
  bind C-a source-file ~/.tmux/layout/mylayout \; display-message "tmux.conf reloaded"

  # Use Alt-arrow keys to switch panes
  unbind-key j
  bind-key j select-pane -D
  unbind-key k
  bind-key k select-pane -U
  unbind-key h
  bind-key h select-pane -L
  unbind-key l
  bind-key l select-pane -R

  unbind '"'
  bind - splitw -v -c '#{pane_current_path}' # 垂直方向新增面板，默认进入当前目录
  unbind %
  bind | splitw -h -c '#{pane_current_path}' # 水平方向新增面板，默认进入当前目录
  ```

## Vim Ctags

* sudo apt-get install vim universal-ctags
* make ARCH=arm tags
  * 要等得挺久才行
* cat ~/.vimrc
  ```
  set mouse-=a

  syntax on
  set hlsearch
  hi Search ctermbg=white
  hi Search ctermfg=black

  set tabstop=4
  set shiftwidth=4
  "set expandtab
  
  set tags+=/home/pi/zengjf/linux-rpi-5.4.y/tags
  ```

## Vim Cscope

* sudo apt-get install cscope
* make ARCH=arm cscope
* ls cscope*
* cat ~/.vimrc
  ```
  set mouse-=a
  syntax on
  set hlsearch
  hi Search ctermbg=white
  hi Search ctermfg=black
  
  set tags+=/home/pi/zengjf/linux-rpi-5.4.y/tags
  
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " cscope setting
  
  if has("cscope")
      set csprg=/usr/bin/cscope
      set csto=1
      set cst
      set nocsverb
      " add any database in current directory
      " if filereadable("cscope.out")
      "     cs add cscope.out
      " endif
      cs add /home/pi/zengjf/helloworld/cscope.out /home/pi/zengjf/helloworld
      cs add /home/pi/zengjf/linux-rpi-5.4.y/cscope.out /home/pi/zengjf/linux-rpi-5.4.y
      set csverb
  endif
  
  nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
  nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
  nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  ```
  * s: 查找C语言符号，即查找函数名、宏、枚举值等出现的地方
  * g: 查找函数、宏、枚举等定义的位置，类似ctags所提供的功能
  * d: 查找本函数调用的函数
  * c: 查找调用本函数的函数
  * t: 查找指定的字符串
  * e: 查找egrep模式，相当于egrep功能，但查找速度快多了
  * f: 查找并打开文件，类似vim的find功能
  * i: 查找包含本文件的文
