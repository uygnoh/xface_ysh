#include "hos.h"

// put all global variables to this struct
typedef struct {
        struct __hos *hos;
        struct __hos *hos_submodule;
        HOS_TYPE_ENUM_T mytype;
        char *load_buf;
        FIL file;
} HOS_UNIT_STRUCT_T;

static
HOS_STATE_ENUM_T HOSAPI(hos_run)(struct __hos *hos)
{
        int bstop = 0;
        HOS_STATE_ENUM_T state;
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }
        if (punit == NULL) {
                return (HOS_STATE_NULL);
        }

        if ((hos->state != HOS_STATE_RUNNING) &&
            (hos->state != HOS_STATE_RUNNING_IDLE)) {
                return (hos->state);
        }


        char *buf = "[Module1 data: XXXXXXXX]";
        hos_buffer_push(punit->hos_submodule, buf);

        if (punit->hos_submodule != NULL) {
                state = punit->hos_submodule->hos_run(punit->hos_submodule);
                if (state == HOS_STATE_STOP) {
                        bstop |= 1;
                }
        }

        if ((bstop & 1) == 1) {
                printf("\t HOS %s set to HOS_STATE_STOP\n", hos->name);
                hos->state = HOS_STATE_STOP;
        }
        if (!punit->hos_submodule) {
                hos->state = HOS_STATE_STOP;
        }

        return (hos->state);
}

static
int HOSAPI(HOS_CMD_STREAM_BUFCHANGED)(struct __hos *hos, char *buf)
{
        HOS_UNIT_STRUCT_T *punit = NULL;
        
        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }
        if (punit == NULL) {
                return (-1);
        }

        // char *buf = hos_buffer_pop(os);
        if (buf == NULL) {
                return (-1);
        }


        printf("module1 get: %s\n", buf);

        //if (buf != NULL)
        //	free(buf);

        return 0;
}

static
int HOSAPI(HOS_CMD_STREAM_START)(struct __hos *hos, HOS_FILE_STRUCT_T *file)
{
        int res;
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }
        if (punit == NULL || hos->state < HOS_STATE_INITED) {
                return (-1);
        }
        
        if (file->filename) {
                printf("==== module1 start, filename: %s ====\n", file->filename);
        }
        
        HOS_FILE_STRUCT_T fl;
        
        punit->hos_submodule = hos_get(file->sub_type);
        if (punit->hos_submodule != NULL) {
                fl.type = file->sub_type;
                fl.sub_type = HOS_MODULE01;
                fl.filename = NULL;
                res = hos_command(punit->hos_submodule, HOS_CMD_STREAM_START, &fl);
                if (res) {
                        punit->hos_submodule = NULL;
                        return (res);
                }
        }

        hos->state = HOS_STATE_RUNNING;
        return (0);
}

static
int HOSAPI(HOS_CMD_STREAM_STOP)(struct __hos *hos)
{
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }
        if (punit == NULL || hos->state < HOS_STATE_RUNNING) {
                return (-1);
        }

        // set state
        hos->state = HOS_STATE_STOP;

        //if (punit->load_buf)
        //	free(punit->load_buf);
        punit->load_buf = NULL;

        if (punit->hos_submodule != NULL) {
                int res = hos_command(punit->hos_submodule, HOS_CMD_STREAM_STOP, NULL);
                if (res) {
                }
                punit->hos_submodule = NULL;
        }

        // reset state
        hos->state = HOS_STATE_INITED;

        return 0;
}


static
int HOSAPI(hos_command)(struct __hos *hos, int cmd, void *params)
{
        int ret = 0;
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }
        if (hos == NULL || punit) {
                return (-1);
        }
        
        switch (cmd) {
        case HOS_CMD_STREAM_START:
                printf("HOS '%s' command 'HOS_CMD_STREAM_START'\n", hos->name);
                return HOSAPI(HOS_CMD_STREAM_START)(hos, (HOS_FILE_STRUCT_T *)params);
                break;
        case HOS_CMD_STREAM_PAUSE:
                printf("HOS '%s' command  'HOS_CMD_STREAM_PAUSE'\n", hos->name);
                if (hos->state == HOS_STATE_RUNNING || 
                    hos->state == HOS_STATE_RUNNING_IDLE) {
                        hos->state = HOS_STATE_RUNNING_PAUSE;
                }
                break;
        case HOS_CMD_STREAM_RESUME:
                printf("HOS '%s' command  'HOS_CMD_STREAM_RESUME'\n", hos->name);
                if (hos->state == HOS_STATE_RUNNING_PAUSE) {
                        hos->state = HOS_STATE_RUNNING;
                }
                break;
        case HOS_CMD_STREAM_STOP:
                printf("HOS '%s' command  'HOS_CMD_STREAM_STOP'\n", hos->name);
                return (HOSAPI(HOS_CMD_STREAM_STOP)(hos));
                break;
        case HOS_CMD_STREAM_BUFCHANGED:
                return (HOSAPI(HOS_CMD_STREAM_BUFCHANGED)(hos, (char *)params));
                break;
        default:
                printf("HOS '%s' command %d unknown !\n", hos->name, cmd);
                ret = -1;
        }

        return ret;
}

static
void HOSAPI(hos_deinit)(struct __hos *hos)
{
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }
        if (punit != NULL) {
                free(punit);
        }

        printf("hos_init : %s ..\n", hos->name);

        hos->handle = NULL;
}

static
HOSHANDLE HOSAPI(hos_init)(struct __hos *hos)
{
        int res;
        HOS_UNIT_STRUCT_T *punit = (HOS_UNIT_STRUCT_T *)malloc(sizeof(HOS_UNIT_STRUCT_T) + 64);

        if (punit == NULL) {
                return NULL;
        }
                
        printf("OsInit : %s ..\n", hos->name);
        memset(punit, 0, sizeof(HOS_UNIT_STRUCT_T));

        punit->hos = hos;
        hos->hos_run = &HOSAPI(hos_run);
        hos->hos_command = &HOSAPI(hos_command);
        hos->hos_deinit = &HOSAPI(hos_deinit);
        hos->state = HOS_STATE_INITED;

        hos->state = HOS_STATE_RUNNING;
        hos->handle = (HOSHANDLE)punit;

        return hos->handle;
}

struct __hos ghos_module1 = {
        "module1", (1 << HOS_MODULE01), &HOSAPI(hos_init),
};
