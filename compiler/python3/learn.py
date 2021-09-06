#!/usr/bin/python3

import random
import sys
import os

print("Hello World")
name = "Derek"
print(name)



###########################################################
###             python3 算术运算
###########################################################
print("5 +  2 = ", 5 +  2)
print("5 -  2 = ", 5 -  2)
print("5 *  2 = ", 5 *  2)
print("5 /  2 = ", 5 /  2)
print("5 %  2 = ", 5 %  2)
print("5 ** 2 = ", 5 ** 2)
print("5 // 2 = ", 5 // 2)



###########################################################
###             python3 格式输出
###########################################################
quote = "\"Always remember you are unique"
multi_line_quote = ''' just
like everyone else '''
print("%s %s %s" % ('I like the quite', quote, multi_line_quote))
print("\n" * 5)
print("I don't like ", end="")
print("newlines")



###########################################################
###             python3 列表
###########################################################
grocery_list = ['Juice', 'Tomatoes', 'Potatoes', 'Bananas']
print('First Item:', grocery_list[0])
print(grocery_list[1:3])
other_events = ['Wash Car', 'Pick Up Kids', 'Cash Check']
to_do_list = [other_events, grocery_list]
print(to_do_list)
print((to_do_list[1][1]))



###########################################################
###             python3 元组
###########################################################
# 元组中的元素值是不允许修改的，但我们可以对元组进行连接组合
# 元组中的元素值是不允许删除的，但我们可以使用del语句来删除整个元组
tup1 = ('Google', 'Runoob', 1997, 2000)
tup2 = (1, 2, 3, 4, 5, 6, 7)
print("tup1[0]: ", tup1[0])
print("tup2[1:5]: ", tup2[1:5])



###########################################################
###             python3 字典
###########################################################
super_villains = {  'Key00'   : 'value11',
                    'Fiddler' : 'Issac Bowin',
                    'Captin ' : 'Leonard Snart',
                    'Weather' : 'Mark Markdon',
                    'Mirror ' : 'Sam Scudder',
                    'Pide P ' : 'Thomas Peterson'
}
print(super_villains)
print(super_villains['Key00'])
print(super_villains['Pide P '])



###########################################################
###             python3 条件判断
###########################################################

age = 21
if age > 16:
    print('You are old enough to drive')
else:
    print('You are not old enough to drive')

  
if age >= 21:
    print('You are old enough to drive a tactor traile')
elif age >= 16:
    print('You are old enough to drive a car')
else:
    print("You are not old enough to drive")


if ((age >= 1) and (age <= 18)):
    print("You get a birthday")
elif ((age == 21) or (age >= 65)):
    print("You get a birthday")
elif not(age == 30):
    print("You don't get a birthday")
else:
    print("You get a birthday party yeah")
    
    

###########################################################    
###             python3 循环
###########################################################
for x in range(0, 10):
    print(x, ' ', end="")
print()


grocery_list = ['Juice', 'Tomatoes', 'Potstoes', 'bananas']
for y in grocery_list :
    print(y)

 
for x in [2,4,6,8,10]:
    print(x)    

    
num_list = [[1,2,3], [10,20,30], [100, 200, 300]] 
for x in range(0, 3):
    for y in range(0, 3):
        print(num_list[x][y])    
    
    
random_num = random.randrange(0, 100) 
while (random_num != 15):
    print(random_num)
    random_num = random.randrange(0, 100)
    
    
i = 0
while (i <= 20):
    if (i % 2 == 0):
        print(i)
    elif (i == 9):
        break
    else:
        i = i+1
        continue
    i += 1 
   
   

###########################################################    
###             python3 函数
###########################################################
def addNumber(fNum, lNum):
    sumNum = fNum + lNum
    return sumNum
print("sumNumber : ", addNumber(1, 2))
  
# python3中lambda函数



###########################################################
###             python3 模块 
###########################################################
pandas #科学计算， pip3 install pandas



