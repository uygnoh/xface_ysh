1. 解锁__FLASH__
2. 擦除指定的页（查看工程空间分布，以防擦除程序本身）
3. 写入数据
4. 读出数据校验
int main(void)
{
        uint32_t *ptr;
        FLASH_Unlock();                                 //解锁__FLASH__
        FLASH_ErasePage(0x08000000 + 2*1024*10);        //擦除第10页（每页2K）
        FLASH_ProgramWord(0x08000000 + 2*1024*10, 0x01234567);
        FLASH_Lock();                                   //上锁__FLASH__
        printf("数据已经写入完成！");
        ptr = (uint32_t *)(2*1024*10);
        printf("ptr = 0x%x", ptr);
}
