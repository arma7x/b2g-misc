FLAGS = -Wall
SRC = *.c
OBJ = *.o
BIN = Cleaner

$(BIN) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(BIN)
	rm $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(FLAGS) -c $(SRC)
clean :
	rm $(OBJ)
