本文档为qt+opencv配置教程
一：opencv下载与编译：
	1.下载cmake，网址为：https://cmake.org/，下载opencv，网址为https://opencv.org/releases/，注：opencv中下载zip解压后的文件和windows版msi文件安装后得到的是一样的。
	2.编译opencv，打开cmake-gui进行configure，具体配置方法参考这篇博客：https://blog.csdn.net/qq_43855258/article/details/128634207?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167715450016800225592006%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=167715450016800225592006&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-3-128634207-null-null.142^v73^pc_search_v2,201^v4^add_ask,239^v2^insert_chatgpt&utm_term=%20architecture%20of%20input%20file%20%60CMakeFiles%5Copencv_world.dir%2Fobjects.a%28vs_version.rc.obj%29%20is%20incompatible%20with%20i386%3Ax86-64%20output&spm=1018.2226.3001.4187。
	注：缺失两文件的百度网盘链接：链接：https://pan.baidu.com/s/1dLpm23rXFY5VQpQHNGNwUQ?pwd=khhq 
提取码：khhq 
--来自百度网盘超级会员V4的分享
	3.个人编译过程中遇到的错误：1、protobuf报错，在cmake中取消勾选与protobuf相关即可解决。2、python报错，如果安装过anaconda，cmake中默认python路径可能会在anaconda文件中，这样在编译时会报错，解决方法有两种，一可以改为正确的python路径，即python安装路径，二如果用不到python，取消勾选并置空camke中的python相关。


二：qt配置opencv
	1、配置Qt\Qt5.12.9\Tools\mingw730_64\bin以及Qt\Qt5.12.9\5.12.9\mingw730_64\bin（qt版本不同，安装路径不同有区别）环境变量
	2、配置opencv环境变量，上篇链接有教程
	3、当opencv编译完成，可以使用添加外部库的方法，右键点击项目->添加库->连接到opencv编译好的install\x64\mingw\lib\libopencv_world470.dll.a，包含路径为install下的include。
	4、第三步如果不成功，直接在pro文件中添加INCLUDEPATH += E:\opencv-4.0.1-Sources\opencv-build\install\include
LIBS += E:\opencv-4.0.1-Sources\opencv-build\lib\libopencv_*.a(注意安装路径区别)
	5、第四步不成功，将E:\OpenCV\opencv-3.4.6-Build\lib内所有文件复制到C:\Qt\5.11.1\mingw53_32\lib下
			    将E:\OpenCV\opencv-3.4.6-Build\bin内所有文件复制到C:\Qt\5.11.1\mingw53_32\bin下
			    在C:\Qt\5.11.1\mingw53_32\inclule下创建一个文件名称为OpenCV，
			    并将E:\OpenCV\opencv-3.4.6-Build\install\include内所有文件复制到C:\Qt\5.11.1\mingw53_32\inclule\OpenCV下
			    在pro文件中添加NCLUDEPATH += C:\Qt\5.11.1\mingw53_32\inclule\OpenCV
			    LIBS += C:\Qt\5.11.1\mingw53_32\lib\libopencv_*.a

