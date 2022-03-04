// MEMORY命令的语法是：
//_____________________________________________________________
MEMORY
{
        name (attr) : ORIGIN = origin, LENGTH = len
        ...
}
name
//一个用户定义的名字，Linker将在内部使用它，所以别把它
//和SECTIONS里用到的文件名，段名等搞重复了，它要求是独一无二的。
attr
//如同它的名字一样，这是内存段的属性描述。
        'R'     Read-only sections.
        'W'     Read/write sections.
        'X'     Sections containing executable code.
        'A'     Allocated sections.
        'I'     Initialized sections.
        'L'     Same as I.
        '!'     Invert the sense of any of the following attributes.
ORIGIN  //这是起始地址
LENGTH  //段长
//例如：
MEMORY
{
        RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
        FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
}


//SECTIONS
//_____________________________________________________________
SECTIONS
{
       ...
      secname start BLOCK(align) (NOLOAD) : AT ( ldadr )
      { contents } >region :phdr =fill
      ...
}







