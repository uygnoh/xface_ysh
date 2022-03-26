
#define LED00_TIME              1000
unsigned int  led00_count;
unsigned char led00_flag;

#define LED11_TIME              5000
unsigned int  led11_count;
unsigned char led11_flag;


int main(void)
{
        led00_count = LED00_TIME;
        while (1) {
                // LED00
                //_____________________________________________
                if (led00_counter) {
                        led00_counter--;
                        if (!led00_counter) {
                                led00_flag = 1;
                        }
                }
                if (led00_flag) {
                        led00_flag = 0;
                        led00_count = LED00_TIME;
                        LED00 = ~LED00;
                }
                
                // LED11
                //_____________________________________________
                if (led11_counter) {
                        led11_counter--;
                        if (!led11_counter) {
                                led11_flag = 1;
                        }
                }
                if (led11_flag) {
                        led11_flag = 0;
                        led11_count = LED00_TIME;
                        LED11 = ~LED11;
                }
        }
}
