// https://github.com/raspberrypi/pico-sdk/tree/master/src/rp2_common/hardware_gpio/include/hardware/gpio.h
static inline bool gpio_get(uint gpio) {
        return !!((1ul << gpio) & sio_hw->gpio_in);
}

static inline void gpio_set_mask(uint32_t mask) {
        sio_hw->gpio_set = mask;
}

static inline void gpio_clr_mask(uint32_t mask) {
        sio_hw->gpio_clr = mask;
}

static inline void gpio_put(uint gpio, bool value) {
        uint32_t mask = 1ul << gpio;
        if (value) {
                gpio_set_mask(mask);
        } else {
                gpio_clr_mask(mask);
        }
}
