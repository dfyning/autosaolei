# autosaolei
自动扫雷小程序

从小就喜欢玩扫雷， 写一个自动扫雷程序探索一下胜率的问题。

一共四个文件，main.cpp, saolei.cpp, autosaolei.cpp, saolei.h

saolei.cpp 文件内是扫雷游戏生成地雷，生成相应数字表的内容，这些都在类minta中实现。
方法leclick()模拟鼠标左键点击。
方法reclick()模拟鼠标右键点击。
方法findwarn()模拟鼠标左右键一同点击。



autosaolei.cpp 内主要是类autosaolei的实现，具体为通过restart()方法刷新状态，通过working(minta)方法接收一次游戏，
该函数返回值为该次扫雷游戏是否胜利（点开所有非雷格子）。
通过以下具体函数实现
方法working()为主工作循环。
方法randclick()为无法判断后的随机点击。
方法trywarn()为简单逻辑判断，左右键一同点击每个周围有未点开格子的已知格子。若点开的格子上标的雷数与周边已预警和未点开格子一样多。
则点开周边所有未点开格子。当仅适用这一种判断方法时可以以一定概率通过低级，较低概率通过中级，不能通过高级。
方法smartjudge()为复杂逻辑判断，可以判断形如121 或212 等可通过逻辑判断出具体地雷位置的情况。
  具体通过"断言"机制，每当trywarn()方法无法点开新的格子，就通过getasserts()方法生成"断言"。每个周围有未点开格子的格子生成一个"断言"。
  每个"断言"携带该格子数字减去周围已预警雷数及周围未点开格子位置信息。通过两两断言间相互判断确定无雷或有雷的格子。
  (断言机制本身覆盖了trywarn方法的功能，但是出于效率考虑，仍保留trywarn()方法)
具体每千局简单模式胜率在   80% 至 85% 之间
          中等模式胜率在  40% 至 42% 之间
          高级模式胜率在  0.6% 至 1.5% 之间
          
还可以通过对不同区域未知格子的地雷概率进行计算，在随机点击时尽可能点击地雷概率小的位置来提高胜率。
