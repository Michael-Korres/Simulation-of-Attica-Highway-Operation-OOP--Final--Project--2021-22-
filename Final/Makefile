#Compiler
CC = g++

#Object files
OBJS = Attica.o random.o Segment.o List.o Vehicle.o Queue.o Toll.o Entrance.o main.o

#Attica.o Entrance.o List.o Queue.o Segment.o Toll.o 

#Executable
EXEC:	$(OBJS)
	$(CC) -g3 -o p $(OBJS)

#run
run:
	./p 200 5 20 0.9

#Clean
clean:
	rm -f $(OBJS)  p