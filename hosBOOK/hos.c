#include "hos.h"

char *hos_buffer_push(struct __hos *hos, char *buf)
{
        if (hos == NULL) {
                return (NULL);
        }
        if (buf != NULL) {
                hos_command(hos, HOS_CMD_STREAM_BUFCHANGED, buf);
        }
        return (buf);
}

char *hos_buffer_pop(struct __hos *hos)
{
        char *buf = NULL;
        if (hos == NULL) {
                return (NULL);
        }
        //get buffer from list
        return buf;
}


static const struct __hos  *ghos_null[] = {NULL, NULL, };
static const struct __hos **ghos_all = (const struct __hos **)ghos_null;


void hos_init_all(const struct __hos *ghos[])
{
        int index;
        struct __hos *hos;
        HOSHANDLE handle;
        
        //set
        ghos_all = (const struct __hos **)ghos;
        
        //init
        index = 0;
        while (ghos_all[index] != NULL) {
                hos = (struct __hos *)ghos_all[index];
                handle = hos->hos_init(hos);
                if (handle == NULL) {
                        printf("\tFailed!");
                }
                index++;
        }
}

void hos_deinit_all(void)
{
        int index;
        struct __hos *hos;
        index = 0;
        
        while (ghos_all[index] != NULL) {
                hos = (struct __hos *)ghos_all[index];
                hos->hos_deinit(hos);
                index++;
        }
}

struct __hos *hos_get(HOS_TYPE_ENUM_T type)
{
        int index;
        struct __hos *hos;
        if (type >= HOS_TYPE) {
                return (NULL);
        }
        index = 0;
        hos = NULL;
        while (ghos_all[index] != NULL) {
                hos = (struct __hos *)ghos_all[index];
                if (hos->types & (1 <<((int)type))) {
                        break;
                }
                index++;
                hos = NULL;
        }
        return (hos);
}

struct __hos *hos_next(struct __hos *hos)
{
        int index;
        if (hos == NULL) {
                return ((struct __hos *)ghos_all[0]);
        }
        index = 0;
        while (ghos_all[index] != NULL) {
                if (ghos_all[index] == hos) {
                        break;
                }
                index++;
        }
        if (ghos_all[index] == hos) {
                return ((struct __hos *)ghos_all[index+1]);
        }
        return (NULL);
}

HOS_STATE_ENUM_T hos_run(struct __hos *hos)
{
        int index;
        if (hos == NULL) {
                return (-1);
        }
        index = 0;
        while (ghos_all[index] != NULL) {
                if (hos == ghos_all[index]) {
                        break;
                }
                index++;
        }
        if (ghos_all[index == NULL) {
                return (-1);
        }
        return (hos->hos_run(hos));
}

int hos_command(struct __hos *hos, int cmd, void *params)
{
        int index;
        if (hos == NULL) {
                return (-1);
        }
        index = 0;
        while (ghos_all[index] != NULL) {
                if (hos == ghos_all[index]) {
                        break;
                }
                index++;
        }
        if (ghos_all[index] == NULL) {
                return (-1);
        }
        return (hos->hos_command(hos, cmd, params));
}
