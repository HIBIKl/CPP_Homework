header和picture头文件都是图像处理内部的代码头
horizonal是图像处理的source    picture是我自己写的用于关联的source
main函数仍未写完

0605
加入了diaognal，stc，ibr方法。将一些重复定义的函数处理了（psnr）
connect函数写出来了
信号槽基本搭好

但是仍然需要沟通一下传参
以及如何通过下拉式菜单选择不同函数

接下来就是一点点修bug了

0606
大改动？
多个header合并成为bigheader
stc代码仍在研究如何加入
测试中未出现bug
现在等待传参

0607
尝试将picture与widget合并
缺少qt库 我无法排bug

合并后的文件为widget.cpp和widget.h可以尝试使用