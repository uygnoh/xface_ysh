#!/usr/bin/python3

#*******************************************************************************
#               => python 使用面向对象方法
#*******************************************************************************
# BankAccount       银行卡
# account_number    银行卡号码
# account_name      银行卡名称
# balance           余额
# input             存钱
# output            取钱

class BankAccount:
    # Constructor(构造器)
    def __init__(self, account_number, account_name, balance):
        self.account_number = account_number
        self.account.name   = account_name
        self.balance        = balance
        
    def input(self, amount)
        self.balance = self.balance + amount
        
    def output(self, amount)
        self.balance = self.balance - amount
        
    # 使用String方法，修改输出样式    
    def __str__(self)
        return "({}, {})".format(self.account_name, self.balance)
        # 也可以使用下面字符串拼接方法
        # return "(" + str(self.account_name) + ", " + str(self.balance) + ")"
        
obj1 = BankAccount("12345", "Tom", 100)
obj2 = BankAccount("12345", "Jerry", 100)    

obj1.output(20)
obj2.input(10)

print(obj1.balance)
print(obj2.balance)  

print(obj1)



#*******************************************************************************
#               => Lambda Expression
#*******************************************************************************
# Lambda表达式，中使用一行写成的代码
fn = lambda x: x*x
print( fn(5) )

fn = lambda x, y: x+y
print( fn(5, 4) )

