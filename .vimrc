"ee: http://vimdoc.sourceforge.net/htmldoc/options.html for details
"设定自动缩进
set cindent
"设定 gvim 运行在增强模式下,不使用vi的键盘模式
set nocompatible
"设置支持多语言,解决乱码
set encoding=utf-8
set fileencodings=utf-8,gbk,default,latin1
"设置字体，配色方案
if has("gui_running")
set guifont=Courier\ New\ 14
" on windows,use "set guifont=Courier:14 "
"设置配色方案
" colorscheme oceandeep
endif

"基本编辑器设置
set number          "显示行号
set expandtab       "编辑时将所有 Tab 替换为空格
set shiftwidth=4    "自动缩进的时候，缩进尺寸为2个空格
set tabstop=4       "设置 softtabstop 为 2. 输入 tab 后就跳了2格
"对于不同类型的文件，进行自定义设置
"au FileType html,python,vim,javascript,css setl shiftwidth=2
"au FileType html,python,vim,javascript,css setl tabstop=2
au FileType java,php setl shiftwidth=4
au FileType java,php setl tabstop=4

set textwidth=180    "设置每行的最大字符数，超过的话，将换行
set hlsearch        "搜索时高亮显示 
set incsearch       "输入搜索内容时就显示搜索结果
set fileformat=unix "文本格式
set nobackup        "覆盖文件时不备份

set ruler           "打开状态栏标尺
set laststatus=2    "显示状态栏 (默认值为 1, 无法显示状态栏)
set cmdheight=1     "设定命令行的行数为 1

set showtabline=2   "显示tab标签
set tabline+=%f     "tab标签
" Enable Code Folding 代码折叠
" set foldenable
" set foldmethod=syntax
set mouse=a         "任何情况都可以使用鼠标）

"去掉错误声音
set vb t_vb=
"工作目录随文件变
autocmd BufEnter * cd %:p:h
"设置状态栏
set statusline=%F%m%r,%Y,%{&fileformat}\ \ \ ASCII=\%b,HEX=\%B\ \ \ %l,%c%V\%p%%\ \ \ [\ %L\ lines\ in\ all\ ]
"不显示工具条
set guioptions-=T
set backspace=indent,eol,start "不设定的话在插入状态无法用退格键和 Delete
"filetype on        "设置文件类型的检测
filetype plugin on "为特定的文件类型允许插件文件的载入

"按住ctrl键，移动方向键时，以峰驼的方式
nnoremap <silent><C-Left>  :<C-u>calsearch('\<\<Bar>\U\@<=\u\<Bar>\u\ze\%(\U\&\>\@!\)\<Bar>\%^','bW')<CR>
nnoremap <silent><C-Right> :<C-u>calsearch('\<\<Bar>\U\@<=\u\<Bar>\u\ze\%(\U\&\>\@!\)\<Bar>\%$','W')<CR>
inoremap <silent><C-Left>  <C-o>:calsearch('\<\<Bar>\U\@<=\u\<Bar>\u\ze\%(\U\&\>\@!\)\<Bar>\%^','bW')<CR>
inoremap <silent><C-Right> <C-o>:calsearch('\<\<Bar>\U\@<=\u\<Bar>\u\ze\%(\U\&\>\@!\)\<Bar>\%$','W')<CR> 

"php语法检查
"setlocal makeprg=\/usr/bin/php\ -l\ -n\ -d\ html_errors=off\ %
"setlocal errorformat=%m\ in\ %f\ on\ line\ %l
"autocmd BufWritePost *.php,*.phps :make
"map :w:noh:make

"Disable phpsyntax based indenting for .php files
au BufRead,BufNewFile *.php             set indentexpr= | set smartindent
au BufRead,BufNewFile *.phps            set filetype=php

"NERDTree
map <F9> :NERDTreeToggle<CR>
let NERDTreeIgnore=['\.svn$','\.bak$']

"在通常模式（n）和插入模式（i），按ctrl+p插入注释
inoremap <buffer> <C-P> ^[:call PhpDocSingle()<CR>
nnoremap <buffer> <C-P> :call PhpDocSingle()<CR>
"选择多行，在可视模式（v）下，对选中的多行插入注释
"vnoremap <buffer> <C-P> :call PhpDocRange()<CR>


setlocal dictionary-=/usr/share/vim/vimfiles/funclist.txt dictionary+=/usr/share/vim/vimfiles/funclist.txt
" Use the dictionary completion
setlocal complete-=k complete+=k

func! InsertTabWrapper()
    let col = col('.') - 1
    if !col || getline('.')[col - 1] !~ '\k'
        return "\<tab>"
    else
        return "\<c-p>"
    endif
endfunction

" Remap the tab key to select action with InsertTabWrapper
inoremap <buffer> <tab> <c-r>=InsertTabWrapper()<cr>
