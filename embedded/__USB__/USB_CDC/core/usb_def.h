#ifndef _USBD_DEF_H
#define _USBD_DEF_H


// __packed  用来内存对齐使用的( 此结构体共有8字节 )
struct usb_setup_packet {
        __packed union {
                uint8_t bmRequestType;
                struct {
                        uint8_t Recipeent : 5;
                        uint8_t Type : 2;
                        uint8_t Dir : 1;
                } bmRequestType_b;
        };
        
        uint8_t bRequest;
        __packed union {
                uint16_t wValue;
                struct {
                        uint8_t wValueL;
                        uint8_t wValueH;
                };
        };
        
        __packed union {
                uint16_t wIndex;
                struct {
                        uint8_t wIndexL;
                        uint8_t wIndexH;
                };
        };
        uint16_t wLength;
        
} __packed;

#endif
