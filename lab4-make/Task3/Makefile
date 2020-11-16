
main : 
	cd A && make mainA
	cd C && make mainC
	ln -s /home/fudanicpc/Desktop/lab4-make/Task3/C/libC.so /usr/lib
	sudo ldconfig
	ln -s /home/fudanicpc/Desktop/lab4-make/Task3/A/libA.so /usr/lib
	sudo ldconfig
	ln -s /home/fudanicpc/Desktop/lab4-make/Task3/libB.so /usr/lib
	sudo ldconfig
	g++ main.cpp -lA -LA -lB -L. -lC -LC -o main

#下面的不用改
.PHONY : clean
cleanObject = main libA.so libC.so
clean :
	@rm ${cleanObject}  -f