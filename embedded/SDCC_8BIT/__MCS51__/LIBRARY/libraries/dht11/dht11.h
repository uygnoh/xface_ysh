#ifndef __DHT11_H__
#define __DHT11_H__


/******************************************************************************/
/*      DHT11_硬件连接                                                         */
/******************************************************************************/
#define ON              0
#define OFF             1    
#define LED_01          P1_3
/******************************************************************************/
/*      DHT11_函数声明                                                          */
/******************************************************************************/
void dht11_init(void);
uint8_t dht11_read(void);
void dht11_data(void);


#endif
