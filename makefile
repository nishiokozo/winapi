OBJS   = main.o

TARGETS = main

#CFLAGS   =  -Wall -Werror -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format -Wno-unused-value -Wno-unused-label -Wno-multichar
CFLAGS   =  -g -Wall -Werror -Wno-unused-but-set-variable -Wno-unused-variable -Wno-sign-compare -Wno-unused-label      -Wno-uninitialized
LDFLAGS  = 
LDLIBS   =    -mwindows -mconsole# -lopengl32 -lglut32 -lglew32 -lglu32


g: makefile $(OBJS) 
	g++ -o main.exe $(OBJS) -mwindows -mconsole
# -lopengl32 -lglut32 -lglew32 -lglu32

ll: makefile ll.cpp
	g++  -o ll.exe ll.cpp $(CFLAGS)
	
main.o:main.cpp 
	g++	-c -o main.o main.cpp $(CFLAGS)

clean:
	rm main.exe -f
	rm ll.exe -f
	rm *.o -f
	
