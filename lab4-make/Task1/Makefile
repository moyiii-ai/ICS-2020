#也许可以在这里也加点指令

main0:
	g++ main0.cpp function0.cpp function1.cpp shared.cpp -o main0
	
main1:
ifeq ($(debug), True)
	g++ -DDEBUG main1.cpp function0.cpp function1.cpp shared.cpp -o main1
else
	g++ main1.cpp function0.cpp function1.cpp shared.cpp -o main1
endif
	
#下面的不用改
.PHONY : clean
cleanObject = main0 main1
clean :
	@rm ${cleanObject}  -f