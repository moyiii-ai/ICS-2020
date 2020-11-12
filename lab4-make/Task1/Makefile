#也许可以在这里也加点指令

main0:
	@g++ main0.cpp function0.cpp shared.cpp -o main
	
main1:
	@#添加编译命令
	
#下面的不用改
.PHONY : clean
cleanObject = main0 main1
clean :
	@rm ${cleanObject}  -f