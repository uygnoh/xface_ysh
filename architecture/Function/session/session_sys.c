
#include "session.h"

////////////////////////////////////////////////////////////////////////////////
// SYS
////////////////////////////////////////////////////////////////////////////////

typedef struct {
        struct SESSION *session;
} session_unit_t;

static
SESSIONSTATE SESSIONAPI(SessionRun)(struct SESSION *session)
{
        session_unit_t *punit = NULL;
        if (session != NULL)
                punit = (session_unit_t*)session->handle;
        if (punit == NULL)
                return SSTATE_NULL;

        if (session->state != SSTATE_RUNNING
                && session->state != SSTATE_RUNNING_IDLE)
                return session->state;

        return session->state;
}

static
int SESSIONAPI(SessionCommand)(struct SESSION *session, int cmd, void *params)
{
        int ret = 0;
        session_unit_t *punit = NULL;

        if (session != NULL)
                punit = (session_unit_t *)session->handle;
        if (punit == NULL)
                return -1;

        switch (cmd) {
        case SSCMD_STREAM_START:
                printf("Session '%s' command 'SSCMD_STREAM_START'\n", session->name);
                if (session->state == SSTATE_INITED)
                session->state = SSTATE_RUNNING;
                break;
        case SSCMD_STREAM_PAUSE:
                printf("Session '%s' command  'SSCMD_STREAM_PAUSE'\n", session->name);
                if (session->state == SSTATE_RUNNING
                        || session->state == SSTATE_RUNNING_IDLE)
                        session->state = SSTATE_RUNNING_PAUSE;
                break;
        case SSCMD_STREAM_RESUME:
                printf("Session '%s' command  'SSCMD_STREAM_RESUME'\n", session->name);
                if (session->state == SSTATE_RUNNING_PAUSE)
                        session->state = SSTATE_RUNNING;
                break;
        case SSCMD_STREAM_STOP:
                printf("Session '%s' command  'SSCMD_STREAM_STOP'\n", session->name);
                if (session->state >= SSTATE_RUNNING)
                        session->state = SSTATE_STOP;
                break;
        case SSCMD_STREAM_BUFCHANGED:
                break;
        default:
                printf("Session '%s' command %d unknown !\n", session->name, cmd);
                ret = -1;
        }

        return ret;
}

static
void SESSIONAPI(SessionDeInit)(struct SESSION *session)
{
        session_unit_t *punit = NULL;

        if (session != NULL)
                punit = (session_unit_t*)session->handle;
        else
                return;

        printf("SessionDeInit : %s ..\n", session->name);

        if (punit != NULL) {
                free(punit);
        }

        session->handle = NULL;
}

static
SESSIONHANDLE SESSIONAPI(SessionInit)(struct SESSION *session)
{
        session_unit_t *punit = (session_unit_t*)malloc(sizeof(session_unit_t) + 64);

        if (punit == NULL)
                return NULL;

        printf("SessionInit : %s ..\n", session->name);

        memset(punit, 0, sizeof(session_unit_t));

        punit->session = session;
        session->SessionRun = &SESSIONAPI(SessionRun);
        session->SessionCommand = &SESSIONAPI(SessionCommand);
        session->SessionDeInit = &SESSIONAPI(SessionDeInit);
        session->state = SSTATE_INITED;

        /* session */
        session->state = SSTATE_RUNNING;
        session->handle = (SESSIONHANDLE)punit;

        return session->handle;
}

struct SESSION gSession_sys =
{
        "sys", (1 << SST_SYS), &SESSIONAPI(SessionInit),
};
