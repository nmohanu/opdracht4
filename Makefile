OBJS	= main.o input.o turn.o board.o
OUT		= gomoku
CC		= g++
FLAGS	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

input.o: input.cpp
	$(CC) $(FLAGS) input.cpp 

turn.o: turn.cpp
	$(CC) $(FLAGS) turn.cpp 

board.o: board.cpp
	$(CC) $(FLAGS) board.cpp 

clean:
	rm -f $(OBJS) $(OUT)
