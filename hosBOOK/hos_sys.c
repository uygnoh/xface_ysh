#include "hos.h"

typedef struct {
        struct __hos *hos;
} HOS_UNIT_STRUCT_T;

static
HOS_STATE_ENUM_T HOSAPI(hos_run)(struct __hos *hos)
{
        HOS_UNIT_STRUCT_T *punit = NULL;
        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }	
        if (punit == NULL) {
                return (HOS_STATE_NULL);
        }

        if (hos->state != HOS_STATE_RUNNING && 
            hos->state != HOS_STATE_RUNNING_IDLE) {
                return (hos->state);
        }

        return (hos->state);
}

static
int HOSAPI(hos_command)(struct __hos *hos, int cmd, void *params)
{
        int retval = 0;
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        }	
        if (punit == NULL) {
                return (-1);
        }


	switch (cmd) {
	case HOS_CMD_STREAM_START:
                printf("HOS '%s' command 'HOS_CMD_STREAM_START'\n", hos->name);
                if (hos->state == HOS_STATE_INITED) {
                        hos->state = HOS_STATE_RUNNING;
                }
                break;
	case HOS_CMD_STREAM_PAUSE:
                printf("HOS '%s' command  'HOS_CMD_STREAM__PAUSE'\n", hos->name);
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
                if (hos->state >= HOS_STATE_RUNNING) {
                        hos->state = HOS_STATE_STOP;
		}
                break;
	case HOS_CMD_STREAM_BUFCHANGED:
                break;
	default:
                printf("HOS '%s' command %d unknown !\n", hos->name, cmd);
                retval = -1;
	}

	return (retval);
}

static
void HOSAPI(hos_deinit)(struct __host *hos)
{
        HOS_UNIT_STRUCT_T *punit = NULL;

        if (hos != NULL) {
                punit = (HOS_UNIT_STRUCT_T *)hos->handle;
        } else {
                return;
        }

        printf("HOS_deinit : %s ..\n", hos->name);

	if (punit != NULL) {
                free(punit);
	}

        hos->handle = NULL;
}

static
HOSHANDLE HOSAPI(hos_init)(struct __hos *hos)
{
        HOS_UNIT_STRUCT_T *punit = (HOS_UNIT_STRUCT_T*)malloc(sizeof(HOS_UNIT_STRUCT_T) + 64);

        if (punit == NULL) {
                return (NULL);
        }
        
        printf("HOS_INIT : %s ..\n", hos->name);

	memset(punit, 0, sizeof(HOS_UNIT_STRUCT_T));

	punit->hos = hos;
	hos->hos_run     = &HOSAPI(hos_run);
	hos->hos_command = &HOSAPI(hos_command);
	hos->hos_deinit  = &HOSAPI(hos_deint);
	hos->state       = HOS_STATE_INITED;

	/* hos */
	hos->state = HOS_STATE_RUNNING;
	hos->handle = (HOSHANDLE)punit;

	return (hos->handle);
}

struct __hos ghos_sys =
{
	"sys", (1 << HOS_SYS), &HOSAPI(hos_init),
};
