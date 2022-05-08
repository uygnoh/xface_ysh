
typedef int (*usbd_request_handler)(struct usb_setup_packet *setup, uint8_t **data, uint32_t *len);
