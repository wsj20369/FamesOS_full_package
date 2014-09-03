1、最好将这个FamesOS目录放到c:盘根目录下

2、批处理文件:

	clean.bat:	删除src目录下的所有临时文件(*.obj, *.lib等)
	makeall.bat:	编译生成demo.exe
	makeit.bat:	编译生成demo.exe, 并用notepad显示编译的过程
	sendapp.bat:	将demo.exe发到另一台机器(tftp->192.168.0.68)

3、目录:
	
	debug		用于调试，也是demo.exe可以执行的一个完整的环境
	demo		示例目录
	help		参考资料
	res		可能用到的一些资源文件
	si		SourceInsight工程文件
	src		FamesOS源码
	x		应用程序源码
	tmp		临时文件
	tools		工具程序, 如tc2等
	utility		工具

4、编译:

	1) 将tc目录拷贝至c:的根目录
	2) 将c:\tc加入到系统路径
	3) 先执行clean.bat, 再执行makeit.bat


