#! /bin/bash
string="runoob is a great site"
echo `expr index "$string" io`  # 输出 4

array=(29 100 13 8 91 44)
echo ${array[@]}
echo ${#array[*]}
echo ${#array[0]}

#read -p "input a val:" a    #获取键盘输入的 a 变量数字
#read -p "input b val:" b    #获取键盘输入的 b 变量数字
#r=$[a+b]                    #计算a+b的结果 赋值给r  不能有空格
#echo "result = ${r}"        #输出显示结果 r

echo "Shell 传递参数实例！";
echo "执行的文件名：$0";
echo "第一个参数为：$1";
echo "第二个参数为：$2";
echo "第三个参数为：$3";
echo "参数个数为：$#"
echo "进程PID为：$$"
echo "传递的参数作为一个字符串显示：$*";

echo "-- \$* 演示 ---"
for i in "$*"; do
    echo $i
done

echo "-- \$@ 演示 ---"
for i in "$@"; do
    echo $i
done