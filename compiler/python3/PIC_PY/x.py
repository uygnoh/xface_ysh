#!/usr/bin/python3
# 读取"countries_zh.csv"文件按照ID排序
# 使用lambda表达式提取字段

countries = []
file = open("countries_zh.csv", "r")
for line in file:
    line = line.strip()
    arr  = line.split(",")
    name = arr[1]
    capt = arr[3]
    popu = arr[4]
    countries.append( (name, capt, popu) )

countries.sort(key=lambda country: country[2])

for country in countries:
    print(country)
