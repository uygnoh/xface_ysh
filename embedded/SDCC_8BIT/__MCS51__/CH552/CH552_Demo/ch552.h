#ifndef __CH552_H__
#define __CH552_H__

#define BIT_00          0x01
#define BIT_01          0x02
#define BIT_02          0x04
#define BIT_03          0x08
#define BIT_04          0x10
#define BIT_05          0x20
#define BIT_06          0x40
#define BIT_07          0x80

/* GPIO */
__sfr __at (0x92) P1_MOD_OC     ;       /* */
__sfr __at (0x93) P1_DIR_PU     ;       /* */
__sfr __at (0x96) P3_MOD_OC     ;       /* */
__sfr __at (0x97) P3_DIR_PU     ;       /* */
__sfr __at (0xC6) PIN_FUNC      ;       /* */


/* PWM */
__sfr __at (0x9B) PWM_DATA2     ;
__sfr __at (0x9C) PWM_DATA1     ;
__sfr __at (0x9D) PWM_CTRL      ;
__sfr __at (0x9E) PWM_CK_SE     ;

/* ADC */
__sfr __at (0x80) ADC_CTRL      ;
__sfr __at (0x9A) ADC_CFG       ;
__sfr __at (0x9F) ADC_DATA      ;
/* ADC_CTRL 位定义 */
__sbit __at (0x80) ADC_CHAN0    ;
__sbit __at (0x81) ADC_CHAN1    ;
/* No (0x82) */
__sbit __at (0x83) CMP_CHAN     ;
__sbit __at (0x84) ADC_START    ;
__sbit __at (0x85) ADC_IF       ;
__sbit __at (0x86) CMP_IF       ;
__sbit __at (0x87) CMP0         ;


#endif
