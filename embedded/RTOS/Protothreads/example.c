#include <pt.h>                 // ProtoThreads必须包含的头文件


static int counter1;            // 线程1计数器
static int counter2;            // 线程2计数器
static int state1 = 0;          // 线程1状态标志
static int state2 = 0;          // 线程2状态标志
static struct pt        pt1;
static struct pt        pt2; 


// 线程1， 控制灯1
// ____________________________________________________________
static int protothread1(struct pt *pt) 
{  
        PT_BEGIN(pt);                   // 线程开始
        while(1) {                      // 每个线程都不会死
                // 如果时间满了1秒，则继续执行，否则记录运行点，退出线程1
                PT_WAIT_UNTIL(pt, counter1 == 1); 
                digitalWrite(12, state1);
                state1   = !state1;     // 灯状态反转
                counter1 = 0;           // 计数器置零
        } 
        PT_END(pt);                     // 线程结束
}



// 线程2， 控制灯2
// ____________________________________________________________
static int protothread2(struct pt *pt) 
{ 
        PT_BEGIN(pt);                   // 线程开始
        while (1) {                     // 每个线程都不会死
                // 如果时间满了5秒，则继续执行，否则记录运行点，退出线程2
                PT_WAIT_UNTIL(pt, counter2 == 5); 
                counter2 = 0;           // 计数清零
                digitalWrite(13, state2);
                state2 =! state2;       // 灯状态反转
        } 
        PT_END(pt);                     // 线程结束
} 



// 线程初始化
// ____________________________________________________________
void setup()
{ 
        pinMode(12, OUTPUT);
        pinMode(13, OUTPUT);
        PT_INIT(&pt1);          // 线程1初始化
        PT_INIT(&pt2);          // 线程2初始化
}



// 这就是进行线程调度的地方
// ____________________________________________________________
void loop () 
{ 
        protothread1(&pt1);     // 执行线程1
        protothread2(&pt2);     // 执行线程2
        delay(1000);            // 时间片，每片1秒，可根据具体应用设置大小
        counter1++; 
        counter2++; 
}



/*******************************************************************************
        => protothread 分析
*******************************************************************************/
#include <pt.h>//ProtoThreads必须包含的头文件

static int counter1,counter2,state1=0,state2=0; //counter为定时计数器，state为每个灯的状态

static int protothread1(struct pt *pt)          //线程1，控制灯1
{  
        char PT_YIELD_FLAG = 1; 
        switch((pt)->lc) {                      //用switch来选择运行点
        case 0:                                 //此乃初始运行点，线程正常退出或刚开始都从这开始运行
                while (1) {                     //每个线程都不会死
                        do {        
                                (pt)->lc = 12;  //记录运行点
        case 12:
                                if (!(counter1 == 1)) {
                                        //return 0
                                        return PT_WAITING;
                                }                                                
                        } while (0)
                        digitalWrite(12, state1);
                        state1   = !state1;     //灯状态反转
                        counter1 =  0;          //计数器置零
                        } 
        }
        PT_YIELD_FLAG = 0; 
        pt->lc=0; 
        return PT_ENDED; // return 1
} 


static int protothread2(struct pt *pt) //线程2，控制灯2
{ 
        char PT_YIELD_FLAG = 1; 
        switch((pt)->lc) {                      //用switch来选择运行点
        case 0:                                 //线程开始
                while(1)  {                     //每个线程都不会死
                        do {        
                                (pt)->lc=39;    //记录运行点
        case 39:
                                if (!(counter2 == 5)) {
                                        //return 0
                                        return PT_WAITING;
                                                                }                                                
                                } while(0)
                                counter2=0;  //计数清零
                                digitalWrite(13, state2);
                                state2 = !state2; //灯状态反转
                                }
        }
        PT_YIELD_FLAG = 0; 
        pt->lc=0; 
        return PT_ENDED; // return 1
        }
} 


static struct pt pt1, pt2; 
void setup()
{ 
        pinMode(12,OUTPUT);
        pinMode(13,OUTPUT);
        pt1->lc=0;  //线程1初始化
        pt2->lc=0;  //线程2初始化
}

void loop () //这就是进行线程调度的地方
{ 
        protothread1(&pt1);  //执行线程1
        protothread2(&pt2);  //执行线程2
        delay(1000);  //时间片，每片1秒，可根据具体应用设置大小
        counter1++; 
        counter2++; 
} 
