typedef enum {
        CW  = 0,        //顺时针方向
        CCW =1          //逆时针方向
} MOTOR_DIR;
typedef enum {
        STOP = 0,       //停机
        RUN  = 1        //运行
} MOTOR_STATE;

__IO int16_t    speed_duty = 15;        //速度占空比：0~100
__IO MOTOR_STATE motor_state = STOP;    //电机状态
__IO MOTOR_DIR   motor_direction = CW;  //电机方向
__IO uint8_t    time_over = 0;          //卡住超时溢出计数
