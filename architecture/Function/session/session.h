#ifndef _SESSION_H_
#define _SESSION_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
#define SESSIONAPI(function) session_private##function

////////////////////////////////////////////////////////////////////////////////
typedef void *SESSIONHANDLE;
typedef void *FIL;

typedef enum {
        SST_NONE,
        // SYSTEM
        SST_SYS,
        // MODULES
        SST_MODULE1,
        SST_MODULE2,
        SST_MODULE3,
        // END
        SST_TYPES,
} session_type_t;

typedef struct session_file {
        char *filename;
        int type;
        int sub_type;
} session_file_t;

typedef enum
{
        SSTATE_NULL = 0,
        SSTATE_INITED,
        SSTATE_RUNNING,
        SSTATE_RUNNING_IDLE,
        SSTATE_RUNNING_PAUSE,
        SSTATE_STOP,
} SESSIONSTATE;

struct SESSION {
        const char name[128];
        const long types;

        SESSIONHANDLE(*SessionInit)(struct SESSION *session);
        SESSIONSTATE state;
        SESSIONHANDLE handle;
        SESSIONSTATE(*SessionRun)(struct SESSION *session);
        int(*SessionCommand)(struct SESSION *session, int cmd, void *params);
        void(*SessionDeInit)(struct SESSION *session);
};

typedef enum {
        SSCMD_NONE = 0,
        SSCMD_STREAM_START,
        SSCMD_STREAM_PAUSE,
        SSCMD_STREAM_RESUME,
        SSCMD_STREAM_STOP,
        SSCMD_STREAM_BUFCHANGED,
        // session special command
        SSCMD_STREAM_USER = 0x10,
} SESSIONCMDID;

#define SSCMD_USER(x)	((x) + SSCMD_STREAM_USER)
enum {
        SSCMD_STREAM_USER0 = SSCMD_USER(0),
        SSCMD_STREAM_USER1
};

////////////////////////////////////////////////////////////////////////////////
extern struct SESSION *SessionGet(session_type_t type);
extern struct SESSION *SessionNext(struct SESSION *session);
extern void SessionInitAll(const struct SESSION *gSessions_all[]);
extern void SessionDeInitAll(void);
extern void SessionBufferInit(struct SESSION *session);
extern char *SessionBufferPush(struct SESSION *session, char *buf);
extern char *SessionBufferPop(struct SESSION *session);
extern void SessionBufferDeInit(struct SESSION *session);
extern SESSIONSTATE SessionRun(struct SESSION *session);
extern int SessionCommand(struct SESSION *session, int cmd, void *params);

#endif //_SESSION_H_
