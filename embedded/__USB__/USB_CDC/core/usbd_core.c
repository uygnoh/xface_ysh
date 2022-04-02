uint8_t *desc;
uint8_t *mos_desc;      //WINDOWS XP 描述符
uint8_t *bos_desc;      //BOS        描述符
static bool usbd_get_decriptor(uint16_t type_index, uint8_t **data, uint32_t *len)
{
        bool found = false;
        uint8_t *p;
        uint32_t current_index;
        uint8_t type = (type_index >> 8) & 0xff;
        uint8_t index = (type_index & 0xff;
        
        if (type == 3 && index == 0xee) {       // 微软描述符
                if (mos_desc) {
                        *data = mos_desc;
                        *len = 100;
                        return (true);
                } else {
                        return (false);
                }
        } else if (type == 15) {                // bos描述符
                if (bos_desc) {
                        *data = bos_desc;
                        *len = 100;
                        return (true);
                } else {
                        return (false);
                }
        } else if (type == 4 || type == 5 || type >= 7) {
                return false;
        }
        
        p = desc;
        
        // 寻找设备描述符信息
        while (p[0]) {
                if (p[1] == type && curent_index == index) {
                        found = true;
                        break;
                }
                p += p[0];
                current_index++;
        }
        if (found) {
                *data = p;
                if (type == 2) {
                        *len = p[2] | (p[3] << 3);
                } else {
                        *len = p[0];
                }
        }
        return found;
}


// 0
// _____________________________________________________________________________
static bool usbd_std_device_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        bool ret = true;
        
        switch (setup->bRequest) {
        case 0x06:
                ret = usbd_get_descriptor(setup->wValue, data, len);
                break;
        default:
                break;
        }
        return (ret);
}
// 1
static bool usbd_std_interface_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        bool ret = true;
        return (ret);
}
// 2
static bool usbd_std_endpoint_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        bool ret = true;

        return (ret);     
}



//  standard 标准设备请求 3 大接收者
// _____________________________________________________________________________
static int usbd_standard_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        int ret = 0;
                switch (setup->bmRequestType_b.Recipient) {
        case 0:
                if (usbd_std_device_request_handler(setup, data, len) == false) {
                        ret = -1;
                }
                break;
        case 1:
                if (usbd_std_interface_request_handler(setup, data, len) == false) {
                        ret = -1;
                }
                break;
        case 2:
                if (usbd_std_endpoint_request_handler(setup, data, len) == false) {
                        ret = -1;
                }
                break;
        default:
                ret = -1;
                break;
        }
        return (ret);
}

// class
static int usbd_class_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        int ret = 0;
        
        if (setup->bmRequestType_b.Recipient != 1) {
                return -1;
        }
        retrun ret;
}

// vendor
static int usbd_vendor_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        int ret = 0;
        retrun ret;
}



// 总的设备请求， 根据Type分为三大类（standard, class, vendor）
// _____________________________________________________________________________
static int usbd_setup_request_handler(struct usb_setup_packet *setup, 
                                      uint8_t **data, uint32_t *len)
{
        int ret = 0;
                switch (setup->bmRequestType_b.Type) {
        case 0:
                if (usbd_standard_request_handler(setup, data, len) < 0) {
                        ret = -1;
                }
                break;
        case 1:
                if (usbd_class_request_handler(setup, data, len) < 0) {
                        ret = -1;
                }
                break;
        case 2:
                if (usbd_vendor_request_handler(setup, data, len) < 0) {
                        ret = -1;
                }
                break;
        default:
                ret = -1;
                break;
        }
        return (ret);
}
