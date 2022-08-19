

void setup() {
        Serial.begin(9600);
}

void loop() {
        if (Serial.available() > 0) {           // 判断串口监视器是否有值输入？
                char ch = Serial.read();        // 读取一个字符，将会清除缓冲区
                if (ch >= '0' && ch <= '9') {   // 判断
                        int  n  = (ch - '0');   // 将字符转换成数字
                        Serial.println(n);
                } else {
                        Serial.println("Please enter 0-9");
                }
        }
}
