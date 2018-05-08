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