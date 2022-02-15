#include <stdio.h>

int function(void) {
        static int i, state = 0;
		printf("%d\n", __LINE__);
        switch (state) {
        case 0: goto LABLE0;
        case 1: goto LABLE1;
        }
        
        LABLE0:
        for (i = 0; i < 10; i++) {
                state = 1;
                return (i);
                LABLE1:;
        }
}

int main(void) 
{
	function();
	return 0;
}
