# STM32F4xx 库函数版本 STM32F4xx Std Lib Version
## 该c文件基于STM32F407ZG芯片编写 Based on STM32F407ZG MCU
## 请勿用于牟利 Please do not use for profit

欢迎大家交流学习心得，如果有用请尽管拿去用，欢迎提交Pull Request<br>
Welcome to communicate<br>
Please feel free to use<br>
Pull request if you want<br>
## 版本说明 Versions Introduction
### v1.7版本 Version 1.7
增加了计算高电平时间函数并决定是否在串口显示(需要用到正点原子的串口通讯函数文件)，删除了不能正常工作的Simplified_ADCx_Init()函数<br>
Add a function to calculate the high level time and decide whether show the data on usart or not("alientek"files of "Usart.c","Usart.h" needed),delete the function Simplified_ADCx_Init() which cannot work properly.<br> 
### v1.6版本 Version 1.6
增加了输入捕获有关的函数，未完全完成，大概会在下个版本补充完整并且更新对应的chm手册<br>
Add some functions about input capture(not completly finished).I will probably complete it in next version and update the CHM reference manual.<br>
### v1.5版本 Version 1.5
增加了帮助手册(中文和英文均有)STM32F4MyHelpManual.chm (v1.0)<br>
Add Help Manuals(including Chinese version and English Version)STM32F4MyHelpManual.chm (v1.0)<br>
### v1.4版本 Version 1.4
增加了一个调试常见问题描述及解决方法的文件，祝大家能顺利解决自己遇到的bug<br>
Add a file which records some problems I met with and the solutions I find.Hope all of you can solve bugs successfully.<br>
### v1.3版本 Version 1.3
添加了一些注释，简化了一些函数的参数，调用更方便<br>
In version 1.3 I added some comments and simplified some parameters of functions so that it is more convenient to call<br>