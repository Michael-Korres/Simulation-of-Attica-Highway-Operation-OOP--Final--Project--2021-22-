#Compiler
CC = g++

#Object files
OBJS = random.o Segment.o List.o Vehicle.o Queue.o Toll.o Entrance.o test_entrance.o

#Attica.o Entrance.o List.o Queue.o Segment.o Toll.o 

#Executable
EXEC:	$(OBJS)
	$(CC) -g3 -o p $(OBJS)

#run
run:
	./p 5 10 1 2 2

#Clean
clean:
	rm -f $(OBJS)  p