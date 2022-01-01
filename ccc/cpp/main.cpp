#include <iostream>
using namespace std;

const double PI = 3.14;

//class代表设计一个类，类后面紧跟着就是类名称
class Circle {
        //访问权限（公共权限）
        public:
                //属性（设置圆的半径）
                int R;
                
                //行为（它是一个函数）
                double calculateZC() {
                        return 2 * PI * R;
                }
        
};

int main(void) {
        //通过圆类创建具体的圆（对象）
        Circle c1;
        //给圆对象的属性进行具体的赋值操作
        c1.R = 10;
        cout << "圆的周长为： " << c1.calculateZC() << endl;
        return 0;
}



