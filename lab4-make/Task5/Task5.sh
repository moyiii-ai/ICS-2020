# 在这里写你想写的代码
g++ -shared -fPIC mycode.cpp -o mycode.so
export LD_PRELOAD=$PWD/mycode.so

# 也可以修改密码
Task5_Passwd=weak_password

# 不要改动下面的代码
echo $Task5_Passwd
echo $Task5_Passwd | $PWD/login