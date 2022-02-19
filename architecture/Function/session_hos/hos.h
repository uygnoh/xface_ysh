#ifndef _HOS_H_
#define _HOS_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define HOSAPI(function)        hos_private##function

typedef void *HOSHANDLE;
typedef void *FIL;

// 用枚举定义系统中（各个模块名称）
typedef enum {
        HOS_NONE,
        //System
        HOS_SYS,
        //Modules
        HOS_MODULE01,
        HOS_MODULE02,
        HOS_MODULE03,
        //End
        HOS_TYPE,
} HOS_TYPE_ENUM_T;

//用结构体定义（各个模块参数）
typedef struct {
        char *filename;
        int type;
        int sub_type;
} HOS_FILE_STRUCT_T;

//用枚举定义（模块状态）
typedef enum {
        HOS_STATE_NULL = 0,
        HOS_STATE_INITED,
        HOS_STATE_RUNNING,
        HOS_STATE_RUNNING_IDLE,
        HOS_STATE_RUNNING_PAUSE,
        HOS_STATE_STOP,
} HOS_STATE_ENUM_T;

//系统结构体(__HOS__)
struct __hos {
        //全局变量
        const char name[128];
        const long types;
        
        //接口函数
        HOSHANDLE(*hos_init)(struct __hos *hos);
        HOS_STATE_ENUM_T state;
        HOSHANDLE handle;
        HOS_STATE_ENUM_T (*hos_run)(struct __hos *hos);
        int(*hos_command)(struct __hos *hos, int cmd, void *params);
        void(*hos_deinit)(struct __hos *hos);
};

//通用接口中的（命令类型）
typedef enum {
        HOS_CMD_NONE = 0,
        HOS_CMD_STREAM_START,
        HOS_CMD_STREAM_PAUSE,
        HOS_CMD_STREAM_RESUME,
        HOS_CMD_STREAM_STOP,
        HOS_CMD_STREAM_BUFCHANGED,
        //hos special command
        HOS_CMD_STREAM_USER = 0x10,
} HOS_CMD_ID_ENUM_T;

#define HOS_CMD_USER(x)         ((x) + HOS_CMD_STREAM_USER)

enum {
       HOS_CMD_STREAM_USER0 =  HOS_CMD_USER(0),
       HOS_CMD_STREAM_USER1
};


extern struct __hos *hos_get(HOS_TYPE_ENUM_T type);
extern struct __hos *hos_next(struct __hos *hos);
extern void hos_init_all(const struct __hos *ghos_all[]);
extern void hos_deinit_all(void);
extern void hos_buffer_init(struct __hos *hos);
extern char *hos_buffer_push(struct __hos *hos, char *buf);
extern char *hos_buffer_pop(struct __hos *hos);
extern void hos_buffer_deInit(struct __hos *hos);
extern HOS_STATE_ENUM_T hos_run(struct __hos *hos);
extern int hos_command(struct __hos *hos, int cmd, void *params);
#endif
