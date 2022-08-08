
extern int main_user(void);
int main(void)
{

        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_USART2_UART_Init();


        // ThreadX 初始化
        main_user();
        
        
        while (1) {

        }
}

