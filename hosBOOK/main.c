#include "hos.h"


// SYS
extern struct __hos ghos_sys;
// MODULES
extern struct __hos ghos_module1;


static const struct __hos *ghos[] = {
        &ghos_sys,
        &ghos_module1,
        NULL
};

static const
HOS_FILE_STRUCT_T STREAMS_FILEs[] =
{
    {"test.txt\0", HOS_MODULE01},
};

////////////////////////////////////////////////////////////////////////////////
int main()
{
    int index, res;
    struct __hos *hos;
    HOS_FILE_STRUCT_T *file, filestream;
    HOS_STATE_ENUM_T state;

    /* init */
    hos_init_all(ghos);

    /* stream shift */
    index = -1;
    while(1)
    {
        /* file shift */
        index++;
        if (index >= sizeof(STREAMS_FILEs) / sizeof(STREAMS_FILEs[0]))
                index = 0;
        file = (HOS_FILE_STRUCT_T *)&STREAMS_FILEs[index];
        printf("\n\nSwitch to new stream %d\n", index);
        printf("filename: %s\n", file->filename);
        filestream.type = file->type;
        filestream.sub_type = file->sub_type;
        filestream.filename = file->filename;

        /* module checking */
        hos = hos_get(file->type);
        if (hos == NULL) {
            printf("Can't find decoder module for stream %d, type = %d\n", index, (int)file->type);
            continue;
        }

        /* stream open */
        res = hos_command(hos, HOS_CMD_STREAM_START, &filestream);
        if(res) {
            printf("Module command 'SSCMD_STREAM_START' error %d for stream %d, type = %d\n",
                res, index, (int)file->type);
            continue;
        }

        /* stream running */
        do {
            state = hos_run(hos);
        } while (0);//(state == SSTATE_RUNNING || state == SSTATE_RUNNING_IDLE);

        /* stream close */
        res = hos_command(hos, HOS_CMD_STREAM_STOP, NULL);
        if(res) {
            printf("Module command 'SSCMD_STREAM_STOP' error %d for stream %d, type = %d\n",
                res, index, (int)file->type);
            continue;
        }

        printf("\n\n");
        usleep(1 * 1000 * 1000);
        break;
    }

    /* deinit */
    hos_deinit_all();

    return 0;
}
