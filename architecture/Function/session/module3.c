#include "session.h"

// put all global variables to this struct
typedef struct
{
    struct SESSION *session;
    session_type_t mytype;
    char *load_buf;
    FIL file;
} session_unit_t;

static
SESSIONSTATE SESSIONAPI(SessionRun)(struct SESSION *session)
{
    int bstop = 0;
    SESSIONSTATE state;
    session_unit_t *punit = NULL;

    if (session != NULL)
        punit = (session_unit_t*)session->handle;
    if (punit == NULL)
        return SSTATE_NULL;

    if(session->state != SSTATE_RUNNING
        && session->state != SSTATE_RUNNING_IDLE)
        return session->state;

    return session->state;
}

static
int SESSIONAPI(SSCMD_STREAM_BUFCHANGED)(struct SESSION *session, char *buf)
{
    session_unit_t *punit = NULL;

    if (session != NULL)
        punit = (session_unit_t*)session->handle;
    if (punit == NULL)
        return -1;

    //char *buf = SessionBufferPop(session);
    if (buf == NULL)
        return -1;

    printf("module3 get: %s\n", buf);

    //if (buf != NULL)
    //	free(buf);

    return 0;
}

static
int SESSIONAPI(SSCMD_STREAM_START)(struct SESSION *session, session_file_t *file)
{
    session_unit_t *punit = NULL;

    if (session != NULL)
        punit = (session_unit_t*)session->handle;
    if (punit == NULL || session->state < SSTATE_INITED)
        return -1;

    if (file->filename)
        printf("module1 start, filename: %s\n", file->filename);

    session->state = SSTATE_RUNNING;

    return 0;
}

static
int SESSIONAPI(SSCMD_STREAM_STOP)(struct SESSION *session)
{
    session_unit_t *punit = NULL;

    if (session != NULL)
        punit = (session_unit_t*)session->handle;
    if (punit == NULL || session->state < SSTATE_RUNNING)
        return -1;

    // set state
    session->state = SSTATE_STOP;

    //if (punit->load_buf)
    //	free(punit->load_buf);
    punit->load_buf = NULL;

    // reset state
    session->state = SSTATE_INITED;

    return 0;
}


static
int SESSIONAPI(SessionCommand)(struct SESSION *session, int cmd, void *params)
{
    int ret = 0;
    session_unit_t *punit = NULL;

    if (session != NULL)
        punit = (session_unit_t*)session->handle;
    if (session == NULL || punit == NULL)
        return -1;

    switch (cmd)
    {
    case SSCMD_STREAM_START:
    {
        printf("Session '%s' command 'SSCMD_STREAM_START'\n", session->name);
        return SESSIONAPI(SSCMD_STREAM_START)(session, (session_file_t *)params);
    }break;
    case SSCMD_STREAM_PAUSE:
    {
        printf("Session '%s' command  'SSCMD_STREAM_PAUSE'\n", session->name);
        if (session->state == SSTATE_RUNNING
            || session->state == SSTATE_RUNNING_IDLE)
            session->state = SSTATE_RUNNING_PAUSE;
    }break;
    case SSCMD_STREAM_RESUME:
    {
        printf("Session '%s' command  'SSCMD_STREAM_RESUME'\n", session->name);
        if (session->state == SSTATE_RUNNING_PAUSE)
            session->state = SSTATE_RUNNING;
    }break;
    case SSCMD_STREAM_STOP:
    {
        printf("Session '%s' command  'SSCMD_STREAM_STOP'\n", session->name);
        return SESSIONAPI(SSCMD_STREAM_STOP)(session);
    }break;
    case SSCMD_STREAM_BUFCHANGED:
    {
        return SESSIONAPI(SSCMD_STREAM_BUFCHANGED)(session, (char *)params);
    }break;
    default:
    {
        printf("Session '%s' command %d unknown !\n", session->name, cmd);
        ret = -1;
    };
    };

    return ret;
}

static
void SESSIONAPI(SessionDeInit)(struct SESSION *session)
{
    session_unit_t *punit = NULL;

    if (session != NULL)
        punit = (session_unit_t*)session->handle;
    if (punit != NULL) {
        free(punit);
    }

    printf("SessionDeInit : %s ..\n", session->name);

    session->handle = NULL;
}

static
SESSIONHANDLE SESSIONAPI(SessionInit)(struct SESSION *session)
{
    int res;
    session_unit_t *punit = (session_unit_t *)malloc(sizeof(session_unit_t) + 64);

    if (punit == NULL)
        return NULL;

    printf("SessionInit : %s ..\n", session->name);
    memset(punit, 0, sizeof(session_unit_t));

    punit->session = session;
    session->SessionRun = &SESSIONAPI(SessionRun);
    session->SessionCommand = &SESSIONAPI(SessionCommand);
    session->SessionDeInit = &SESSIONAPI(SessionDeInit);
    session->state = SSTATE_INITED;

    session->state = SSTATE_RUNNING;
    session->handle = (SESSIONHANDLE)punit;

    return session->handle;
}

struct SESSION gSession_module3 =
{
    "module3", (1 << SST_MODULE3), &SESSIONAPI(SessionInit),
};
