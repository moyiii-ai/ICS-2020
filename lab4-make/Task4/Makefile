main:
	@#在这里添加编译的代码
	#g++ main.cpp some.cpp -o main
	gcc -c some.cpp -o some.o -fPIC
	gcc -c main.cpp -o main.o -fPIC

.PHONY : clean
clean :
	@rm *.o -f
	@rm main -f
