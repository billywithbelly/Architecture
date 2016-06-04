CC = g++ -lm -std=c++11 -Wall

SRCS = ./*.cpp
OBS = ./*.o

# The following line means that do SRC first.
CMP: SRC
	$(CC) -o $@ *.o

SRC: $(SRCS)
	$(CC) -c $(SRCS)
	
.PHONY :
	clean
clean: 
	rm CMP *.o