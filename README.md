<<<<<<< HEAD
#Multithreading
##配置
###openmp
-	brew安装好openmp之后，再使用brew安装新版LLVM
- 	使用clang++ 编译
- 	为了与系统自带的LLVM区分，我们使用下列符号链接

>	sudo ln -s /usr/local/opt/llvm/bin/clang /usr/local/bin/clang-omp
>	sudo ln -s /usr/local/opt/llvm/bin/clang++ /usr/local/bin/clang-omp++

-	为了方便编译，进入XXX.fish里面进行编译指令的特指。

>	vim ~/.config/fish/functions/XXX.fish

-	 配置方法如下图：
	![](/Users/chen/study/并行分布式计算/g++mp配置.png)
=======
# multithread_programing
## project1 ##
### 具体介绍 ###
> #### *生产者消费者模型* ####
>##### 生产者消费者模型是一个并行程序中非常基础又经典的一个问题。
	在多线程开发当中，如果生产者处理速度很快，而消费者处理速度很慢，那么生产者就必须等待消费者处理完，才能继续生产数据。同样的道理，如果消费者的处理能力大于生产者，那么消费者就必须等待生产者。为了解决这个问题于是引入了生产者和消费者模式。
>	
>1. 在这个问题中特别要注意一些共享变量的互斥问题以及生产者消费者俩者的同步问题。
>2. 为了解决这俩个问题，我们有俩种方法：互斥锁+条件变量，以及互斥锁+信号量
>3. 本次实验使用互斥锁+条件变量的方法，使用pthread编程模型，在EHPC上面运行。详细情况见project1
>>>>>>> a56d48f13d4870019db0ca1b4e11ec04b98b0cd4
