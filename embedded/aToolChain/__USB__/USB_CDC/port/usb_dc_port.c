#include "usb_dc.h"
struct usbd_ep_state {
        uint16_t ep_mps;        //最大包长度
        uint8_t  ep_addr;       //地址
        uint8_t  ep_type;       //类型
};
struct usb_dc_config_priv {
        struct usbd_ep_state  in_ep[8]; //IN端点
        struct usbd_ep_state out_ep[8]; //OUT端点
} usb_dc_cfg;


// 设置USB设备地址，默认都是（0）地址
//_____________________________________________________________
int usbd_set_address(const uint8_t addr)
{
        //填写设备地址到USB寄存器
        //是立即设置（或者是延时设置）
        if (addr == 0) {
        }
        dev_addr = addr;
}

// 打开端点，设置端点属性
//_____________________________________________________________
int usbd_ep_open(const struct usbd_endpoint_cfg *ep_cfg)
{
        if (ep_cfg->addr & 0x80) {      //IN方向
                //FIFO配置
                //设置端点的传输Type
                usb_dc_cfg.in_ep[ep_cfg->ep_addr & 0x7f].ep_addr = ep_cfg->ep_addr;
                usb_dc_cfg.in_ep[ep_cfg->ep_addr & 0x7f].ep_addr = ep_cfg->ep_addr;
                usb_dc_cfg.in_ep[ep_cfg->ep_addr & 0x7f].ep_addr = ep_cfg->ep_addr;
                //设置端点地址
                //设置端点mps
                //IN端点接收使能关闭
        } else {                        //OUT方向
                //FIFO配置
                //设置端点的传输Type
                usb_dc_cfg.out_ep[ep_cfg->ep_addr & 0x7f].ep_addr = ep_cfg->ep_addr;
                usb_dc_cfg.out_ep[ep_cfg->ep_addr & 0x7f].ep_addr = ep_cfg->ep_addr;
                usb_dc_cfg.out_ep[ep_cfg->ep_addr & 0x7f].ep_addr = ep_cfg->ep_addr;
                //OUT端点接收使能开启
        }
}

// 关闭端点
//_____________________________________________________________
int usbd_ep_close(const uint8_t ep)
{
        //关闭端点收发使能
}

// 将端点设置为（stall）状
//_____________________________________________________________
int usbd_ep_set_stall(const uint8_t ep)
{
        //根据方向设置到寄存器中的stall标志位
}

// 
//_____________________________________________________________
int usbd_ep_clear_stall(const uint8_t ep)
{
        //根据方向设置到寄存器中的stall标志位，清除
        //如果要收数据（开启OUT端点使能）
}

// 
//_____________________________________________________________
int usbd_ep_is_stall(const uint8_t ep, uint8_t *stalled)
{
        //读stall寄存器然后设置到stalled里面
        *stalled = get_stall_state();
}

// write, 先填充再发送
//_____________________________________________________________
int usbd_ep_write(const uint8_t ep, const uint8_t *data, uint32_t data_len, uint32_t *ret_bytes)
{
        if (ep & 0x80 != 0x80) {
                return -1;
        }
        if (!data & data_len) {
                return -1;
        }
        if (!data_len) {
                //使能发送(EPEN, valid, ready, ack)，长度为（0）
                return 0;
        }
        
        // 如果有数据
        if (data_len > usb_dc_cfg.in_ep[ep & 0x7f].ep_mps) {
                data_len = usb_dc_cfg.in_ep[ep & 0x7f].ep_mps;
        }
        
        1 //填充到FIFO
        2 //使能发送(EPEN, valid, ready, ack)，长度为（data_len）
        
        if (ret_bytes) {
                *ret_bytes = data_len;
        }
        return 0;
}

// read，先使能，再接收数据
// 第一次使能一定是在usbd_ep_open()这个函数中处理
//_____________________________________________________________
int usbd_ep_read(const uint8_t ep, const uint8_t *data, uint32_t max_data_len, uint32_t *read_bytes)
{
        uint32_t read_count;
        if (ep & 0x80 == 0x80) {
                return -1;
        }
        if (!data & max_data_len) {
                return -1;
        }
        if (!max_data_len) {
                //使能接收(EPEN, valid, ready, ack)，长度为（ep_mps）
                return 0;
        }
        
        
        if (max_data_len > usb_dc_cfg.out_ep[ep & 0x7f].ep_mps) {
                max_data_len = usb_dc_cfg.out_ep[ep & 0x7f].ep_mps;
        }
        
        read_count = get_read_count;
        read_count = MIN(read_count, max_data_len);
        
        1 //从FIFO中读取数据到data中
        2 //使能接收(EPEN, valid, ready, ack)，长度（max_data_len）
        
        if (read_bytes) {
                *read_bytes = read_count;
        }
        return 0;
}



/*******************************************************************************
        => 硬件需要实现的函数
*******************************************************************************/
// 
//_____________________________________________________________
int usb_dc_init()
{
        //打开USB时钟
        //配置USB引脚
        //清除USB寄存器，清除中断
        //配置一些基本的属性（lpm, fifo ...）
        //开启USB中断（reset, ep中断，端点0（setup in（tx） out（rx））, 非0中断）
        //开总中断
}

// 
//_____________________________________________________________
int usb_dc_deinit()
{
}


// 
//_____________________________________________________________
void usbd_irq_callback(uint8_t event, void *args)
{
}

// 
//_____________________________________________________________
void USB_IRQ(void)
{
        if (val & isr_reset) {
                usbd_irq_callback(USB_EVENT_RESET, NULL);
        }
        if (val & isr_suspend) {
                usbd_irq_callback(USB_EVENT_SUSPEND, NULL);
        }
        if (val & isr_resume) {
                usbd_irq_callback(USB_EVENT_RESUME, NULL);
        }
        if (val & ep_tx) {
                if (ep == 0) {
                        usbd_irq_callback(USB_EVENT_EP0_IN_NOTIFY, NULL);
                } else {
                        usbd_irq_callback(USB_EVENT_EP_IN_NOTIFY, (void *)ep | 0x80);
                }
        }
        if (val & ep_rx) {
                if (ep == 0) {
                        usbd_irq_callback(USB_EVENT_EP0_OUT_NOTIFY, NULL);
                } else {
                        usbd_irq_callback(USB_EVENT_EP_OUT_NOTIFY, (void *)ep | 0x7f);
                }
        }
        if (val & ep0_setup) {
                usbd_irq_callback(USB_EVENT_SETUP_NOTIFY, NULL);
        }
}
