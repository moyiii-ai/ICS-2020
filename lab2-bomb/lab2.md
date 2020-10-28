# ICSⅠ Lab2 报告

计算机科学与技术

19307130296

孙若诗

## 运行截图

![avatar](results.png)  

## 密码答案

列举多组表示多种答案均可行。

对于Phase_1、Phase_5，格式必须和下列答案一致。对于Phase_2、3、4、6，secret等，由于使用%d读入整数，可以自动忽略多余空格，但回车仍旧是不可接受的。

1. **Phase_1: string comparison**
Border relations with Canada have never been better.

2. **Phase_2: loops**
1 2 4 8 16 32

3. **Phase_3: conditionals/switches**
0 207 / 1 311 / 2 207 / 3 256 / 4 389 / 5 206 / 6 682 / 7 327

4. **Phase_4: recursive calls and the stack discipline**
0 0 / 1 0 / 3 0 / 7 0
进入Secret_Phase需要在后面空一格加 DrEvil。

5. **Phase_5: pointers**
IONEFG/yo^uvw等任何ASCII码后四位依次为9、F、E、5、6、7的六位字符串。

6. **Phase_6: linked lists/pointers/structs**
4 3 2 1 6 5

7. **Secret_phase**
22

## 解题过程

* **Pre**

&emsp;&emsp;对照bomb.c观察main函数。基本模式为调用read_line，将返回值%rax赋给%rdi，调用phase_i，重复6次。

&emsp;&emsp;阅读read_line，可以推测它的功能是读入一行字符串，返回值为字符串首地址。

&emsp;&emsp;explode_bomb为引爆炸弹，lab目标为跳过此函数。

* **Phase_1: string comparison**

&emsp;&emsp;阅读Phase_1函数，发现400ee4处将0x402400赋给%esi。下一行即调用string_not_equal，其返回值为0则可跳过explode_bomb。

&emsp;&emsp;阅读string_not_equal，发现它的功能和名字一样，就是先比较%rdi和%rsi长度是否相等，再按位比较。若两个字符串相等则返回0。

&emsp;&emsp;因此我们想拆除炸弹，就是要输入一个和%esi相同的字符串，显然可以用gdb输出0x402400地址所存储的内容，具体操作如下。
![avatar](phase_1.png)

* **Phase_2: loops**

![avatar](phase_2.png)

* **Phase_3: conditionals/switches**

* **Phase_4: recursive calls and the stack discipline**

* **Phase_5: pointers**

![avatar](phase_5.png)

* **Phase_6: linked lists/pointers/structs**

![avatar](list.png)

* **Secret_phase**

![avatar](intosecret.png)
![avatar](position.png)
![avatar](cell1.png)
![avatar](cell2.png)
![avatar](cell3.png)

## 实验总结

1. 认识到了gdb工具的方便强大。
