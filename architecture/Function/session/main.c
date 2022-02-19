#include "session.h"

////////////////////////////////////////////////////////////////////////////////
// SYS
extern struct SESSION gSession_sys;
// MODULES
extern struct SESSION gSession_module1;
extern struct SESSION gSession_module2;
extern struct SESSION gSession_module3;

////////////////////////////////////////////////////////////////////////////////
static const struct SESSION *gSessions[] =
{
        &gSession_sys,
        &gSession_module1,
        &gSession_module2,
        &gSession_module3,
        NULL
};

static const
session_file_t STREAMS_FILEs[] =
{
        {"test.txt\0", SST_MODULE1, SST_MODULE2},
};

////////////////////////////////////////////////////////////////////////////////
int main()
{
        int index, res;
        struct SESSION *session;
        session_file_t *file, filestream;
        SESSIONSTATE state;

        /* init */
        SessionInitAll(gSessions);

        /* stream shift */
        index = -1;
        while (1) {
                /* file shift */
                index++;
                if (index >= sizeof(STREAMS_FILEs) / sizeof(STREAMS_FILEs[0]))
                        index = 0;
                file = (session_file_t *)&STREAMS_FILEs[index];
                printf("\n\nSwitch to new stream %d\n", index);
                printf("filename: %s\n", file->filename);
                filestream.type = file->type;
                filestream.sub_type = file->sub_type;
                filestream.filename = file->filename;

                /* module checking */
                session = SessionGet(file->type);
                if (session == NULL) {
                        printf("Can't find decoder module for stream %d, \
                                type = %d\n", index, (int)file->type);
                        continue;
                }

                /* stream open */
                res = SessionCommand(session, SSCMD_STREAM_START, &filestream);
                if(res) {
                        printf("Module command 'SSCMD_STREAM_START'     \
                                error %d for stream %d, type = %d\n",   \
                                        res, index, (int)file->type);
                        continue;
                }

                /* stream running */
                do {
                        state = SessionRun(session);
                } while (0);//(state == SSTATE_RUNNING || state == SSTATE_RUNNING_IDLE);

                /* stream close */
                res = SessionCommand(session, SSCMD_STREAM_STOP, NULL);
                if (res) {
                        printf("Module command 'SSCMD_STREAM_STOP' error %d \
                                for stream %d, type = %d\n",                \
                                        res, index, (int)file->type);
                        continue;
                }

                printf("\n\n");
                usleep(1 * 1000 * 1000);
                break;
        }

        /* deinit */
        SessionDeInitAll();

        return 0;
}
