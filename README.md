License
--------
The MIT License (MIT)

Copyright (c) <2013> <Jake Horsfield>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.



## 项目说明

### 编译环境

win10 gcc



### 功能

1.增加鼠标对蛇的控制，可以通过鼠标来改变蛇的运动方向，使蛇的方向朝向鼠标位置。通过改变旋转中心设置旋转角，使得蛇在改变位置后节点会向运动方向旋转，保持蛇身节点上的横线与运动方向垂直。

2.总共8个水果，两个水果由黑，棕随机产生，6个水果由红，蓝，绿随机产生。原程序没有对水果产生位置的判定，可能造成蛇身与水果重合以及水果与水果的重合，本程序增加对食物投放点的判断，如果与蛇身或其他水果重合，则重新投放。

3.蛇头由sprite绘制，图案为自己所画的带眼睛的圆形，蛇身节点由CircleShape和RectangleShape绘制，表现为圆叠加黑色矩形，矩形在圆中间。

4.可以使用b键更改背景颜色，顺序为白，黑，褐

5.可以使用g键改grid颜色以及是否显示：顺序为关，白，黑，褐；grid使用sprite绘制。

6.最后分数为总长度，包括蛇身和蛇头



### 性能优化

​    使用循环链表处理snake节点，每次移动删除最后一个尾节点并在蛇头位置增加一个新的节点，减少运算。

​    原程序在边界处判定存在问题，导致刚好位于在边界运动的节点一直被判定，因而坐标不断改变，浪费性能，且会出现节点消失的现象，本程序仅保留一次相等判定，减少性能浪费。