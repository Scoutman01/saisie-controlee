CC=gcc
# -O2
CFLAGS=-Wall -ansi -pedantic -g -fsanitize=address,undefined
LDFLAGS=
EXEC=saisie
OBJ_DIR=obj/
SRC_DIR=src/
BIN_DIR=bin/
OBJ=$(OBJ_DIR)main.o \
$(OBJ_DIR)contenu_fichier.o \
$(OBJ_DIR)saisir_fichier.o \
$(OBJ_DIR)saisir_nom.o \
$(OBJ_DIR)saisir_entiers.o

install: repertoire $(EXEC)

repertoire:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(EXEC): $(OBJ)
	$(CC) -o $(BIN_DIR)$@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)

uninstall: clean
	rm -rf $(BIN_DIR)
