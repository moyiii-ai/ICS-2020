# Lab5 - Shell lab

## 实验目的

Shell Lab 的主要目的是为了让我们熟悉**进程控制**和**信号**。

通过完成lab，加深对CSAPP中异常控制流这一章节的知识的理解。

## 实验总览

按照[shlab.pdf](./shlab.pdf)的指示，编写一个简易的shell，并且通过`test01`~`test16`的测试。shell的简易框架已在[tsh.c](./tsh.c)中为你搭建好，你需要的只是补充相关代码。如果对shell的相关概念暂时不是非常清楚，请参考[shlab.pdf](./shlab.pdf)中*General Overview of Unix Shells*一节。具体需要实现的shell的功能也请参见[shlab.pdf](./shlab.pdf)中*The `tsh` Secification*一节。

考虑到本次lab布置时间临近期末且与pj时间时间重合，为了减轻负担，本次lab**并没有**为选修荣誉课程的同学布置特殊的内容。

请注意，本次实验为单人实验，请忽略[shlab.pdf](./shlab.pdf)中*Logistics*节的提示。

## 实验准备

1. **仔细查看shlab.pdf（实验所需指导）**，理解实验内容。

2. shlab-handout.tar压缩包内是实验所需的材料，其中tsh.c是我们需要补充代码的文件。

3. 在开始动手编写shell以前，请确保自己已经仔细阅读完教材第8章《异常控制流》的内容.

## 实验内容

对 tsh.c 中没有填写的函数进行填写，使得该 shell 能处理前后台运行程序，能够处理 `SIGINT`, `SIGTSTP `等信号。需要实现的函数和参考长度如下：

`eval()`: 该函数的主要功能是对用户输入的指令和参数进行解析并运行计算。如果用户输入内建命令（`quit`, `bg`, `fg`, `jobs`），那么立即执行；否则fork 一个新的子进程并且将该任务在子进程的上下文中运行。如果该任务是前台任务，那么需要等到它运行结束才返回。(70行)

`builtin_cmd()`: 该函数主要用来判断输入指令是否是内建指令，如果是则立即执行，不是则返回。（25行）

`do_bgfg()`: 主要执行 bg 和 fg 指令功能。(50行)

`waitfg()`: 实现等待前台程序运行结束。(20行)

`sigchld_handler()`: 响应`SIGCHLD`。(80行)

`sigint_handler()`: 响应`SIGINT`(ctrl+c)信号。(15行)

`sigtstp_handler()`: 响应`SIGTSTP`(ctrl+z)信号。(15行)

注：在编写代码的过程中不同函数的代码长度可能与参考长度有较大的出入。特别是后三个函数，TA实现长度均不到参考长度的一半。

----

实现完上述函数后，你需要保证你的代码能够通过所有的test测试（即，对于`test01`~`test16`，你`make testXX`输出的结果应与`make rtestXX`在除pid部分以外一致）。

## 实验提示

1. 可以从分析样例trace01.txt(`test01`的输入)开始，看看具体需要运行哪些指令和操作，依次根据16个样例理解整个lab，最后完成编程。

2. 每次修改tsh.c文件后，需要重新make编译，然后运行./tsh检查是否可以正确运行。

3. 在未实现shell对内建指令`quit`的支持前，可以通过`Ctrl + \`退出shell（建议思考为什么可以这样做，有助于对整个代码逻辑的初步理解，不需要附在报告中）

4. 可以通过运行./tshref这个已经实现的shell，将它的输出结果与自己实现的shell的运行结果进行比较。

5. 测试样例时，可以使用`make testXX `和`make rtestXX`来测试自己的程序输出是否与参考答案输出一致。(注意有一些样例`make test`和`make rtest`输出的PID会有所不同，无须担心）。以下为一个例子：

   ```bash
   febblay@DESKTOP-GL2F042:/mnt/c/Users/admin/Desktop/ICS lab5/shlab-handout$ make test04
   ./sdriver.pl -t trace04.txt -s ./tsh -a "-p"
   #
   # trace04.txt - Run a background job.
   #
   tsh> ./myspin 1 &
   [1] (220) ./myspin 1 &
   febblay@DESKTOP-GL2F042:/mnt/c/Users/admin/Desktop/ICS lab5/shlab-handout$ make rtest04
   ./sdriver.pl -t trace04.txt -s ./tshref -a "-p"
   #
   # trace04.txt - Run a background job.
   #
   tsh> ./myspin 1 &
   [1] (226) ./myspin 1 &
   ```

6. 请特别注意CSAPP上8.5.2节中的**进程组概念**和一系列函数，这可能会在很大程度上为你实现shell提供便利。

7. 更多提示请参见[shlab.pdf](./shlab.pdf)。

8. 若参考网上的资料，请注明。请不要参考同学作业！

## 实验提交

提交材料：

1. 实验报告(学号.pdf，请在实验报告中写上学号和姓名)

2. tsh.c文件(只需要这一个代码文件即可)

实验报告应**详细解释每个函数完成的工作**，不需要附带运行的截图。

请将提交材料放在以学号命名的文件夹中，打包成**学号.tar**进行提交。

Due: 2020.12.30 23:59 （共3周）

---

本次lab的负责人: 沈溯，肖琪霖。

