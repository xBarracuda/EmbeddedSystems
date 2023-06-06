OBJS    = main.o Buggy.o gyroDriver.o UltraSchallDriver.o
SOURCE    = main.cpp Buggy.cpp gyroDriver.cpp UltraSchallDriver.cpp
HEADER    = Buggy.h gyroDriver.h UltraSchallDriver.h
OUT    = main
CC     = g++
FLAGS     = -g -c -Wall
LFLAGS     = 

all: $(OBJS)
    $(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
    $(CC) $(FLAGS) main.cpp 

Buggy.o: Buggy.cpp
    $(CC) $(FLAGS) Buggy.cpp 

gyroDriver.o: gyroDriver.cpp
    $(CC) $(FLAGS) gyroDriver.cpp 

UltraSchallDriver.o: UltraSchallDriver.cpp
    $(CC) $(FLAGS) UltraSchallDriver.cpp 


clean:
    rm -f $(OBJS) $(OUT)