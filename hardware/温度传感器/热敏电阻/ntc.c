温度      电阻（单位K）         加上30K           1024*x          ADC数值
0         324.1              354.1            331878.4        937.245
1         307.68             337.68           315064.3        933.026
2         292.34             322.34           299356.2        928.697


#define uint8_t unsigned char
#define uin16_t unsigned int

#define RESVAL          30      //上拉电阻值
#define LEN             41      //温度宽度  

//0~40度温度对应电阻表
double RES[] = {
        324.1,  307.68, 292.34, 277.99, 264.53,
        251.89, 240,    228.78, 218.2,  208.19,
        198.71, 189.72, 181.19, 173.07, 165.35,
        157.98, 150.96, 144.26, 137.85, 131.72,
        125.86, 120.24, 114,86, 109.7,  104.75,
        100,    95.642, 91.506, 87.577, 83.845,
        80.299, 76.926, 73.718, 70.665, 67.759,
        64.991, 62.355, 59.842, 57.446, 55.161,
        52.98
};


//根据电阻计算长度为len的ADC数据
//计算公式： ADC = (1024*x) / (x+y)
//说明：x为NTC对应的阻值， y为上拉电阻
void calc_adc_res(int len, int y)
{
        int i = 0;
        for (i = 0; i < len; i++) {
                //计算出的数据将原数据覆盖掉
                RES[i] = (int)(RES[i]*1024)/(RES[i]+y);
        }
}


//打印长度len的数据
//mode = 1 打印整形
//mode = 2 打印浮点型
void print_data(int len, int mode)
{
        int i;
        for (i = 0; i< len; i++) {
                if (mode == 1) {
                        printf("%.3f\t", RES[i];
                } else if (mode == 2) {
                        printf("%.3f\t", RES[i];
                }
                
                //10个数据进行换行
                if (i % 10 == 0) {
                        printf("\n");
                }
        }
}

//算法校验（返回1正确， 返回0错误）
uint8_t check(int len)
{
        int i;
        for (i = 0; i < len; i++) {
                //如果误差超过1， 表示出现错误
                if ((RES[i] - ADC[i]) > 1) {
                        return 0;
                }
        }
        return 1;
}

//在RES[0]到RES[len-1]中根据ADC计算温度
//错误代码，超上下限返回（201）
float calc_adc_temperture(int adc, int len)
{
        float tmp = 0;
        int i;
        
        //计算数据有效性
        if ((adc > RES[0]) || (adc < RES[len-1])) {
                printf("上限： %.2f  下限： %.2f  \n", RES[0], RES[len-1]);
                return (-201);
        }
        
        //计算初始化值
        for (i = 0; i < len; i++) {
                if (adc < RES[i]) {
                        tmp++;
                } else {
                        break;
                }
        }
        
        //计算偏移量
        if (i >= 1) {
                tmp = tmp - (RES[i-1] - adc) / (RES[i-1] - RES[i-2]);
        }
        return (tmp-1);
}


int main(void)
{
        float tmp = 0;
        int i = 0;
        
        //计算长度为LEN, 上拉电阻为30K的__ADC值
        calc_adc_res(LEN, RESVAL);
        printf("上拉电阻__%dk__时候的ADC宽度为：%.2f\n", RESVAL, RES[0] - RES[LEN-1]);
        printf("___________________________________________________________\n");
        //打印计算后的ADC值
        print_data(LEN, 1);
        
        //数据检验
        if (check(LEN) == 1) {
                printf("!校验成功\n");
        } else {
                printf("!Error\n");
        }
        
        //for (i = 993; i > 861; i--)     //10K
        for (i = 937; i > 653; i--) {   //30K
                tmp = calc_adc_temperture(i, LEN);
                printf("ADC:%d = %.2f\n", i, tmp);
        }
        printf("\n");
        return (0);
}
