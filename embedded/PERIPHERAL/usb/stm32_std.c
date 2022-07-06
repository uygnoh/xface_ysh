https://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32-standard-peripheral-library-expansion/stsw-stm32046.html



Common	usb_core.c/h	        //该文件包含硬件抽象层和USB通信操作
Common	usb_conf_template.h	//该文件包含主机、设备和OTG模式的核心配置参数：
                                //发送FIFO大小，接收FIFO大小，核心模式和选定功能等。
                                //*用户需要根据自己的需求，使用这个文件对USB OTG low level driver进行合理的配置。
                                //这个文件应该被复制到应用程序文件夹并根据应用程序的需要进行修改。
Common	usb_bsp_template.c	//该文件包含了USB使用的低级核心配置（中断、GPIO等）。用户需要使用这个文件配置USB使用
                                //的硬件资源。这个文件应该被复制到应用程序文件夹并根据应用程序的需要进行修改。
Host	usb_hcd.c/h	        //该文件包含USB_HOST_Library访问核心时使用的Host接口层
Host	usb_hcd_int.c/h	        //该文件包含Host模式所使用的中断子程序
Device	usb_dcd.c/h	        //该文件包含USB_HOST_DEvice用于访问核心时使用的的Device接口层。
Device	usb_dcd_int.c/h	        //该文件包含Device模式的中断子程序
OTG	usb_otg.c/h	        //该文件包含SRP和HNP协议的实现以及有关于OTG模式的中断



// USB OTG low level driver 配置
//_____________________________________________________________
USB OTG low level driver 配置是通过一个名为usb_conf.h的配置文件进行
配置的。在实际的移植过程中，可以复制源码中的usb_conf_template.h然后更名
为usb_conf.h，然后编辑修改即可。具体可配置的项目见下表：
USB_OTG_FS_CORE                 //使能内核的全速模式
USB_OTG_HS_CORE                 //使能内核的高速模式
RX_FIFO_FS_SIZE                 //设置全速模式下接收的FIFO的大小
RX_FIFO_HS_SIZE                 //设置高速模式下接收的FIFO的大小
TXn_FIFO_FS_SIZE                //设置全速模式下指定设备端点的发送FIFO的大小，n 为设备的端点号使用的索引值
TXn_FIFO_HS_SIZE                //设置高速模式下指定设备端点的发送FIFO的大小，n 为设备的端点号使用的索引值
TXH_NP_FS_FIFOSIZ               //设置全速模式下，作为USB Host时，非周期性发送的FIFO的大小
TXH_NP_HS_FIFOSIZ               //设置高速模式下，作为USB Host时，非周期性发送的FIFO的大小
TXH_P_FS_FIFOSIZ                //设置全速模式下，作为USB Host时，周期性发送的FIFO的大小
TXH_P_HS_FIFOSIZ                //设置高速模式下，作为USB Host时，周期性发送的FIFO的大小
USB_OTG_ULPI_PHY_ENABLED        //为高速模式使能ULPI接口的PHY。通常为外接的PHY芯片
USB_OTG_EMBEDDED_PHY_ENABLED    //为高速模式芯片内嵌的FS PHY。一般STM32系列芯片内嵌了一个PHY芯片。
                                //芯片不同其PHY的对于全速和高速的支持情况也不同
USB_OTG_HS_LOW_PWR_MGMT_SUPPORT //使能高速模式下的低功耗管理功能
USB_OTG_FS_LOW_PWR_MGMT_SUPPORT //使能全速模式下的低功耗管理功能
USB_OTG_HS_INTERNAL_DMA_ENABLED //使能高速模式下的DMA特性
USB_OTG_HS_DEDICATED_EP1_ENABLED//使能高速模式下，作为USB Device时，专用的端点1的特性

typedef struct USB_OTG_handle {
        USB_OTG_CORE_CFGS       cfg;
        USB_OTG_CORE_REGS       regs;
        
        #ifdef USE_DEVICE_MODE
        DCD_DEV                 dev;
        #endif
        
        #ifdef USE_HOST_MODE
        HCD_DEV                 host;
        #endif
        
        #ifdef USE_OTG_MODE
        OTG_DEV                 otg;
        #endif
} USB_OTG_CORE_HANDLE, *PUSB_OTG_CORE_HANDLE;


//同时在使用DMA时，需要注意：
//目前，DMA仅在高速模式下使用。
//在使用DMA时，必须要保证所有需要处理DMA 收发Buf的结构体必须是四字节对齐的。
//所以，USB_OTG_handle(其封装了所有内部Buffer和变量)必须要四字节对齐。具体可使用如下代码
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLE
        #if defined (__ICCARM__)        //IAR Compiler
        #pragma data_alignment=4
        #endif
#endif
//_ALIGN_BEGIN和__ALIGN_END为特殊的编译器宏值，具体见usb_conf_template.h的定义。
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_Core __ALIGN_END



//USB OTG low level driver中的Host层
//_____________________________________________________________
该部分主要是指usb_hcd.c/h和usb_hcd_int.c/h两个文件。在初始化主机驱动
程序（HCD）之后，低级驱动程序为数据和URB状态监视保存多个结构和缓冲区。 
主机通道结构保存在主机驱动程序中，并通过主机号索引从上层访问。USB Host 的定义结构
typedef struct _HCD {
        uint8_t         Rx_Buffer[MAX_DATA_LENGTH];     //
        __IO uint32_t   ConnSts;                        //连接状态
        __IO uint32_t   PortEnabled;
        __IO uint32_t   ErrCnt[USB_OTG_MAX_TX_FIFOS];
        __IO uint32_t   XferCnt[USB_OTG_MAX_TX_FIFOS];
        __IO HC_STATUS   HC_Status[USB_OTG_MAX_TX_FIFOS];
        __IO URB_STATE   URB_State[USB_OTG_MAX_TX_FIFOS];
        USB_OTG_HC       hc[USB_OTG_MAX_TX_FIFOS];
        uint16_t        channel[UsB_OTG_MAX_TX_FIFOS];
} HCD_DEV, *USB_OTG_USBH_PDEV;



https://blog.csdn.net/ZCShouCSDN/article/details/78936456?utm_source=blogxgwz12








