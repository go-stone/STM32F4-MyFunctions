### 1.keil连接了stlink，在设置中可以看到连接成功，但是无法下载程序是什么原因？
#### Keil linked to stlink successfully,but it can't download programs to MCU,what's wrong?<br>
答：若提示Error: Flash Download failed  -  Could not load file '..\OBJ\Template.axf'，则将工程编译(build)一次即可。该错误原因是没有生成.axf文件<br>
Answer: If keil reminds you "Error: Flash Download failed  -  Could not load file '..\OBJ\Template.axf'",please build the project once again.<br>
### 2.keil提示Error: Flash Download failed  -  "Cortex-M4"
#### Keil Error: Flash Download failed  -  "Cortex-M4"
答：需要添加Flash。点击魔术棒，debug，右侧的settings，打开的窗口选择上方的Flash选项卡，点击Add，从中挑选正确的板子型号的Flash，然后擦除选择Erase sector即可。<br>
Answer: You need to add flash to project.Click the options-debug-settings,open "flash" tab,click "Add" and select the correct flash for your MCU,then check off "Erase sector",click OK.<br>
### 3.小笔记
#### A note
TIM与NVIC的初始化应该放在所有其他外设初始化的后面，因为如果在中断服务函数中调用了其他外设，而该外设又没有初始化时，程序就会卡在这里不动。该错误很难察觉，编译没有任何问题，但是会导致整个程序运行不正常，卡在未初始化的外设调用的代码处。<br>
You may init the TIM and NVIC at last(behind all other peripherals' inition),because if you call some other peripherals in the TIMx_IRQHandler() functions but you haven't init these peripherals,then the whole program will be stuck at the position where calls the peripherals.This error is hard to find because you can build the project successfully without being reminded of errors.<br>