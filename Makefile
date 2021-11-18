FLAGS = -Wall
SRC = $(FILE).c
OBJ = $(FILE).o
BIN = $(FILE)

$(BIN) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(BIN)
	rm $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(FLAGS) -c $(SRC)
clean :
	rm $(OBJ)
