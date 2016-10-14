#compile
CC = gcc 
CFLAGS= -ggdb -Wall 
LIBS = -L/usr/lib -lm

#Folders
SRC_DIR = .
SRC_DIR_O = ../../obj/Gameplay

#files
SRCS = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR_O)/%.o, $(SRCS)) 
HEADS = $(addprefix -I, $(shell find  ../ -mindepth 1  -type d -name '*'))

#.PHONY
.PHONY: all clean

all: $(OBJS)

$(SRC_DIR_O)/%.o: $(SRC_DIR)/%.c 

	@printf "\t $< ==> $@\n"
	
	@$(CC) -c $(CFLAGS) $(LIBS) $< $(HEADS) -o $(SRC_DIR_O)/$@ 
	
clean:
	@echo 'Deleting Gameplay temp files'
	@-rm $(SRC_DIR_O)/*.o
