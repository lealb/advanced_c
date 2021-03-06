# OpenCV3 编程入门
## 第二章，官网实例<暂略>


# 第四章 OpenCV的数据结构和基本绘图
1.Mat
OpenCV函数中输出图像的内存分配是自动完成的（如果不特别指定的话）
使用OpenCV的C++接口时不需要考虑内存释放的问题，（1.0的CV结构C接口使用IplImage）
赋值运算符和拷贝构造函数（构造函数）只复制信息头
    Mat A,C;
    A=imread("1.jpg,CV_LOAD_IMAGE_COLOR);
    Mat (B)A; // 拷贝构造函数
    C=A;  // 赋值运算
使用函数clone或copyTo()复制图像的矩阵
    Mat F=A.clone();
    Mat G;
    A.coptTo(G);
# 第五章- core
1.傅里叶变换
2.ROI
# 第六章 图像处理
重点知识：
    - 三种线性滤波： 方框滤波、均值滤波、高斯滤波
    - 两种非线性滤波： 中值滤波、双边滤波
    - 7种图像处理形态学：腐蚀、膨胀、开运算、闭运算、形态学梯度、顶帽、黑帽
    - 漫水填充
    - 图像缩放
    - 图像金字塔
    - 阈值化
    
平滑处理
    平滑处理（smoothing）也称模糊处理(bluring),是一种简单且使用频率很高的图像处理方法。
    用途很多，常见用来减少图像上的噪点或者失真。
图像滤波与滤波器
    图像滤波，指在尽量保留图像细节特征的条件下对目标图像的噪声进行抑制，是图像预处理中不可缺少的操作，其处理效果的好坏
    将直接影响到后续图像处理和分析的有效性和可靠性。
    图像滤波的目的：
        抽出对象的特征作为图像识别的特征模式
        为适应图像处理的要求，消除图像数字化时所混入的噪声
    滤波处理要求：
        不能损坏图像的轮廓及边缘等重要信息
        使图像清洗视觉效果好
    平滑滤波是低频增强的空间域滤波技术，目的主要是模糊和消除噪音。
    空间域的平滑滤波一般采用简单平均法实现，即求邻近像素点的平均亮度值。邻域的大小与平滑的效果直接相关，越大平滑的效果
    越好，但是不宜过大，会导致边缘信息损失越大，使图像变得模糊。

    滤波器，一种形象的比喻是：可以把滤波器想象成一个包含加权系数的窗口，当使用这个滤波器平滑处理图像时，
    就把这个窗口放到图像之上，透过这个窗口来看我们得到的图像。


    线性滤波器：
        经常用于剔除经输入信号中不想要的频率或者从许多频率中选择一个想要的频率
    常见线性滤波器：
        低通滤波器：允许低频率通过
        高通滤波器：允许高频率通过
        带通滤波器：允许一定范围频率通过
        带阻滤波器：阻止一定范围频率通过兵器允许其他频率通过
        全通滤波器：允许所有频率通过，仅仅改变相位关系
        陷波滤波器：阻止一个狭窄频率范围通过，是一种特殊的带阻滤波器
    滤波与模糊：
        实质上模糊是滤波的一种呈现
        以高斯滤波为例，高斯滤波是指用高斯函数作为滤波函数的滤波操作
        高斯模糊是高斯低通滤波，高通滤波为锐化
    非线性滤波：
        中值滤波基本思想是用像素点邻域灰度值的中值来代替该像素点的灰度值，
        该方法是在去除脉冲噪声、椒盐噪声的同时又能保留图像的边缘细节
        是基于排序统计理论的一种能有效抑制噪声的非线性信号处理技术，其原理是把数字图像或数字序列中一点的值用
        该点的一个邻域中各点值的中值代替，让周围的像素值接近真实值，从而消除孤立的噪声点。
        与线性的均值滤波器比较：
        优势：
            在均值滤波器中，由于噪声成分被放入平均计算中，输出收到了噪声的影响；在中值滤波器中，由于噪声成分很难
            选上，几乎不会影响到输出。在同等区域中，中值滤波的消除噪声能录更胜一筹，且也常用语保护边缘信息。
        劣势：
            中值滤波花费的时间是均值滤波的5倍以上。<需要对选取的奇数邻近点进行排序后选取中值>
        双边滤波是结合图像的空间邻近度和像素值相似度的一种折中处理，同时考虑空域信息和灰度相似性，达到保边去噪的目的，
        具有简单、非迭代、局部的特点。
    
    形态学-数学形态学
    膨胀和腐蚀实现的功能：
    消除噪声
    分割出独立的图像元素，在图像中连接相邻的元素
    寻找图像中的明显的极大值区域或者极小值区域
    求出图像的梯度

    对高亮区域进行操作，数学解释，将图像（或图像的一部分区域，称之为A）与核B进行卷积
        A*B
    开运算：先腐蚀后膨胀的过程，可用来消除小物体，在纤细点处分离物体，并且在平滑较大物体的
    边界的同时不明显改变其面积。
        dst=open(src,element)=dilate(erode(src,element))
    闭运算：先膨胀后腐蚀的过程，可用于排除小型黑洞(黑色区域)
         dst=close(src,element)=erode(dilate(src,element))
    形态学梯度：膨胀图与腐蚀图之差,对二值图像进行这一操作可以将团块(blob)的边缘突出出来。
        dst=morph-grad(src,element)=dilate(src,element)-erode(src,element)
    顶帽：原图像与开运算的结果图之差，常用语分离比邻近点亮一些的斑块（开运算的结果放大了裂缝或者局部低亮度的区域，
    原图中减去开元算后的图，得到的效果图突出了比原图轮廓周围的区域更明显的区域，操作与选择的核的大小相关）
        dst=tophat(src,element)=src-open(src,element)
    黑帽：闭运算的结果图与原图像之差，用来分离比邻近点暗一些的斑块，效果图有着非常完美的轮廓
        dst=blackhat(src,element)=close(src,element)-src
    
    漫水填充是一种用特定的颜色填充连通区域，通过设置可连通像素的上下限以及连通方式来达到不同的填充效果的方法。
    经常用来标记或分离图像的一部分，以便对其进行进一步处理或分析，也可以用来从输入图像获取掩码区域，掩码会加速处理过程，
    或只处理掩码指定的像素点，操作的结果总是某个连续的区域。



