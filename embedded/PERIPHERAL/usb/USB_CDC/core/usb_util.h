#ifndef MIN
#define MIN(a, b)       (((a) < (b)) ? (a) : (b))
#endif

#define BCD(x)          ((((x) / 10) << 4) | ((x) % 10))

#define BIT(n)          (1UL << (n))


#define ARRAY_SIZE(array)       \
                        ((int)((sizeof(array) / sizeof((array)[0]))))
                        
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif
