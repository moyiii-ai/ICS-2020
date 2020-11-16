
main : 
	cd A && make mainA
	cd C && make mainC
	g++ main.cpp -lA -LA -lB -LB -lC -LC -o main

#下面的不用改
.PHONY : clean
cleanObject = main A/A.o A/libA.a C/C.o C/libC.a
clean :
	@rm ${cleanObject}  -f