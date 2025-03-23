
bin := bin/prog
cflages := -Wall -Wextra -I/home/gman/work/sproj/c/powerAlarm/headers/
cc := gcc

all : $(bin)

$(bin) : obj/main.o obj/strTonum.o
	$(cc)  $^ -o $@
obj/main.o  : src/main.c
	$(cc) $(cflages) -c $< -o $@
obj/strTonum.o : src/strTonum.c
	$(cc) $(cflages) -c $< -o $@


folders :
	mkdir bin obj

play :
	./$(bin)
clean :
	rm bin/* -rf
	rm obj/* -rf
