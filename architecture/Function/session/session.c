#include "session.h"

////////////////////////////////////////////////////////////////////////////////
char *SessionBufferPush(struct SESSION *session, char *buf)
{
        if (session == NULL)
                return NULL;

        if (buf != NULL)
                SessionCommand(session, SSCMD_STREAM_BUFCHANGED, buf);

        return buf;
}

char *SessionBufferPop(struct SESSION *session)
{
        char *buf = NULL;

        if (session == NULL)
                return NULL;

        // get buffer from list

        return buf;
}

////////////////////////////////////////////////////////////////////////////////
static const struct SESSION *gSessions_null[] = { NULL, NULL, };
static const struct SESSION **gSessions_all = (const struct SESSION **)gSessions_null;

void SessionInitAll(const struct SESSION *gSessions[])
{
        int index;
        struct SESSION *session;
        SESSIONHANDLE handle;

        /* set */
        gSessions_all = (const struct SESSION **)gSessions;

        /* init */
        index = 0;
        while (gSessions_all[index] != NULL) {
                session = (struct SESSION *)gSessions_all[index];
                handle = session->SessionInit(session);
                if (handle == NULL) {
                        printf("\tFailed !");
                }
                index++;
        }
}

void SessionDeInitAll(void)
{
        int index;
        struct SESSION *session;

        index = 0;
        while (gSessions_all[index] != NULL) {
                session = (struct SESSION *)gSessions_all[index];
                session->SessionDeInit(session);
                index++;
        }
}

struct SESSION *SessionGet(session_type_t type)
{
        int index;
        struct SESSION *session;
        if (type >= SST_TYPES)
                return NULL;

        index = 0;
        session = NULL;
        while (gSessions_all[index] != NULL) {
                session = (struct SESSION *)gSessions_all[index];
                if (session->types & (1 << ((int)type)))
                        break;
                index++;
                session = NULL;
        }

        return session;
}

struct SESSION *SessionNext(struct SESSION *session)
{
        int index;
        if (session == NULL)
                return (struct SESSION *)gSessions_all[0];

        index = 0;
        while (gSessions_all[index] != NULL) {
                if (gSessions_all[index] == session)
                        break;
                index++;
        }

        if (gSessions_all[index] == session)
                return (struct SESSION *)gSessions_all[index + 1];

        return NULL;
}

SESSIONSTATE SessionRun(struct SESSION *session)
{
        int index;
        if (session == NULL)
                return -1;

        index = 0;
        while (gSessions_all[index] != NULL) {
                if (session == gSessions_all[index])
                        break;
                index++;
        }

        if (gSessions_all[index] == NULL)
                return -1;

        return session->SessionRun(session);
}

int SessionCommand(struct SESSION *session, int cmd, void *params)
{
        int index;
        if (session == NULL)
                return -1;

        index = 0;
        while (gSessions_all[index] != NULL) {
                if (session == gSessions_all[index])
                        break;
                index++;
        }

        if (gSessions_all[index] == NULL)
                return -1;

        return session->SessionCommand(session, cmd, params);
}
