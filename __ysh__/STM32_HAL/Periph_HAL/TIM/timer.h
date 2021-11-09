/*******************************************************************************
        => STM32F4x__定时器__结构体
*******************************************************************************/
typedef struct {
        uint32_t Prescaler;             //定时器预分频设置
        uint32_t ConuterMode;           //定时器计数方式
        uint32_t Period;                //定时器周期
        uint32_t ClockDivision;         //时钟分频
        uint32_t RepetitionCounter;     //重复计数器
        uint32_t AutoReloadPreload;     //ARPE：自动重装载预装载允许位
} TIM_Base_InitTypeDef;
//_________________________________________________________________________
Prescaler       //它设定（TIMx_PSC寄存器）的值，可设置范围（0~65535）
                //基本实现1至65536分频（实际分频系数 = TIMx_PSC+1）
CounterMode     //定时器计数方式，基本定时器只能向上计数
Period          //它设定（TIMx_ARR寄存器）的值，可设置范围（0~65535）
                //假设： 定时器预分频器后的时钟频率为（1MHz），我们设置
                //Period的值 = 999； 1MHz / (999+1) = 1KHz； 即为1ms的定时周期。
ClockDivision   //时钟分频，设置定时器时钟CK_INT频率与数字滤波器采样时钟频率分频比，
                //基本定时器没有这个功能。
RepetitionCounter//重复计数器，利用它可以轻松控制输出PWM的个数。
//_________________________________________________________________________


//定时器句柄结构体
//_________________________________________________________
typedef struct {
        TIM_TypeDef                     *Instance;      //定时器基地址
        TIM_Base_InitTypeDef            Init;           //定时器基本结构体
        HAL_TIM_ActiveChannel           Channel;        //通道选择
        DMA_HandleTypeDef               *hdma[7];       //DMA句柄结构体指针
        HAL_LockTypeDef                 Lock;           //对象资源锁
        __IO HAL_TIM_StateTypedef       State;          //定时器工作状态
} TIM_HandleTypeDef;


//定时器时钟配置结构体
//_________________________________________________________
typedef struct {
        uint32_t ClockSource;           //时钟源
        uint32_t ClockPolarity;         //时钟极性
        uint32_t ClockPrescaler;        //时钟预分频
        uint32_t ClockFilter;           //时钟滤波器
} TIM_ClockConfigTypeDef;
ClockPolarity   //时钟极性选择，ETR不反相（高电平或或者上升沿有效）
                //ETR反相，TIx上升没，TIx下降沿，TIx双边沿有效
ClockPrescaler  //时钟分频器（1， 2， 4， 8）分频
ClockFilter     //时钟滤波器（只用于ETR信号）， 0~0xF


//输入捕获结构体
//_________________________________________________________
typedef struct {
        uint32_t ICPolarity;    //输入捕获极性（上升沿， 下降沿，双边沿）
        uint32_t ICSelection;   //输入捕获选择（TIx, TRC）信号选择
        uint32_t ICPrescaler;   //输入捕获分频（1， 2， 4， 8）分频
        uint32_t ICFilter;      //输入捕获滤波（0~0xF）
} TIM_IC_InitTypeDef;


//输出比较结构体
//_________________________________________________________
typedef struct {
        uint32_t OCMode;        //输出比较模式
        uint32_t Pulse;         //捕获比较寄存器值（TIMx_CCxR）
        uint32_t OCPolarity;    //输出比较通道极性
        uint32_t OCNPolarity;   //输出比较互补通道极性
        uint32_t OCFastMode;    //输出比较快速模式
        uint32_t OCIdleState;   //空闲状态下，通道的输出
        uint32_t OCNIdleState;  //空闲状态下，互补通道的输出
} TIM_OC_InitTypeDef;



//定时器从模式配置结构体
//_________________________________________________________
typedef struct {
        uint32_t SlaveMode;             //从模式选择
        uint32_t InputTrigger;          //输入触发TRGI
        uint32_t TriggerPolarity;       //触发极性
        uint32_t TriggerPrescaler;      //触发预分频
        uint32_t TriggerFilter;         //触发滤波
} TIM_SlaveConfigTypeDef;


//定时器主模式配置结构体
//_________________________________________________________
typedef struct {
        uint32_t MasterOutputTrigger;   //触发输出选择
        uint32_t MasterSlaveMode;       //主、从模式选择
} TIM_MasterConfigTypeDef;


//单脉冲初始化结构体
//_________________________________________________________
typedef struct {
        uint32_t OCMode;        //输出比较模式
        uint32_t Pulse;         //捕获比较寄存器值（TIMx_CCxR）
        uint32_t OCPolarity;    //输出比较通道极性
        uint32_t OCNPolarity;   //输出比较互补通道极性
        uint32_t OCFastMode;    //输出比较快速模式
        uint32_t OCIdleState;   //空闲状态下，通道的输出
        uint32_t OCNIdleState;  //空闲状态下，互补通道的输出
        uint32_t ICPolartity;   //输入捕获极性
        uint32_t ICSelection;   //输入捕获选择
        uint32_t ICFilter;      //输入捕获滤波
} TIM_OnePulse_InitTypeDef;


//编码器初始化结构体
//_________________________________________________________
typedef struct {
        uint32_t EncoderMode;   //编码器模式（3种可选）
        uint32_t IC1Polarity;   //输入捕获 1 极性选择
        uint32_t IC1Selection;  //输入捕获 1 信号源选择
        uint32_t IC1Prescaler;  //输入捕获 1 预分频
        uint32_t IC1Filter;     //输入捕获 1 滤波
        uint32_t IC2Polarity;   //输入捕获 2 极性选择
        uint32_t IC2Selection;  //输入捕获 2 信号源选择
        uint32_t IC2Prescaler;  //输入捕获 2 预分频
        uint32_t IC2Filter;     //输入捕获 2 滤波
} TIM_Encoder_InitTypeDef;


//霍尔传感器初始化结构体
//_________________________________________________________
typedef struct {
        uint32_t IC1Polarity;           //输入捕获 1 极性
        uint32_t IC1Prescaler;          //输入捕获 1 预分频
        uint32_t IC1Filter;             //输入捕获 1 滤波器
        uint32_t Commutation_Delay;     //发生捕获后输出脉冲的延时时间
} TIM_HallSensor_InitTypeDef;


//清除输入配置结构体
//_________________________________________________________
typedef struct {
        uint32_t ClearInputState;       //在外部事件时清除OCxREF信号
        uint32_t ClearInputSource;      //清除输入源选择
        uint32_t ClearInputPolarity;    //清除输入极性
        uint32_t ClearInputPrescaler;   //清除输入预分频
        uint32_t ClearInputFilter;      //清除输入滤波器
} TIM_ClearInputConfigTypeDef;


//刹车和死区配置结构体
//_________________________________________________________
typedef struct {
        uint32_t OffStateRunMode;       //运行模式下的关闭状态
        uint32_t OffStateIDLEMode;      //空闲模式下的关闭状态
        uint32_t LockLevel;             //定时器锁等级
        uint32_t DeadTime;              //死区时间（0~0xFF）
        uint32_t BreakState;            //刹车状态（使能或禁用）
        uint32_t BreakPolarity;         //刹车极性
        uint32_t AutomaticOutput;       //自动输出选择（使能或禁用）
} TIM_BreakDeadTimeConfigTypeDef;



/*******************************************************************************
        => STM32F4x__定时器__
*******************************************************************************/
//测量2个上升沿之间的时间
typedef struct {
        uint8_t ucFinishFlag;
        uint8_t ucStartFlag;
        int32_t sCtr;
        int32_t sLastCtr;
        int32_t sPeriod;
} struct_capture;
