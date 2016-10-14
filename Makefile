#compiler
CC = gcc 
CFLAGS= -ggdb -Wall 
LIBS = -L/usr/lib -lm  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


#Creating objs folders if not existing : 
	
#Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

#files
EXEC = $(BIN_DIR)/main
MAIN = $(OBJ_DIR)/main.o
SDL = $(BIN_DIR)/mainSDL
SDL_O = $(OBJ_DIR)/mainSDL.o
TXT = $(BIN_DIR)/mainTXT
TXT_O = $(OBJ_DIR)/mainTXT.o

HEADS = $(addprefix -I, $(shell find  . -mindepth 1  -type d -name '*'))

#Module SRCs
QUEST_SRC = $(wildcard $(SRC_DIR)/Quest/*.c)
SPELL_SRC = $(wildcard $(SRC_DIR)/Spell/*.c)
CHAR_SRC = $(wildcard $(SRC_DIR)/Character/*.c)
STUFF_SRC = $(wildcard $(SRC_DIR)/Stuff/*.c)
MAP_SRC = $(wildcard $(SRC_DIR)/Map/*.c)
GAME_SRC = $(wildcard $(SRC_DIR)/Gameplay/*.c)
BFFR_SRC = $(wildcard $(SRC_DIR)/Buffer/*.c)
STRNG_SRC = $(wildcard $(SRC_DIR)/String/*.c)
SDL_SRC = $(wildcard $(SRC_DIR)/Display/SDL/*.c)
TXT_SRC = $(wildcard $(SRC_DIR)/Display/TXT/*.c)

#Module directory


#targets 
TRGTS = $(patsubst $(SRC_DIR)/Quest/%.c, $(OBJ_DIR)/Quest/%.o, $(QUEST_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Spell/%.c, $(OBJ_DIR)/Spell/%.o, $(SPELL_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Character/%.c, $(OBJ_DIR)/Character/%.o, $(CHAR_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Stuff/%.c, $(OBJ_DIR)/Stuff/%.o, $(STUFF_SRC)) 
TRGTS += $(patsubst $(SRC_DIR)/Map/%.c, $(OBJ_DIR)/Map/%.o, $(MAP_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Gameplay/%.c, $(OBJ_DIR)/Gameplay/%.o, $(GAME_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Buffer/%.c, $(OBJ_DIR)/Buffer/%.o, $(BFFR_SRC))
TRGTS += $(patsubst $(SRC_DIR)/String/%.c, $(OBJ_DIR)/String/%.o, $(STRNG_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Display/SDL/%.c, $(OBJ_DIR)/Display/SDL/%.o, $(SDL_SRC))
TRGTS += $(patsubst $(SRC_DIR)/Display/TXT/%.c, $(OBJ_DIR)/Display/TXT/%.o, $(TXT_SRC))

VALOPTIONS = --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all -v 

#colors
color = '\e[91;01m$(1)\x1b[0m'

.PHONY: all exec clean veryclean valgrind valgrind_options 

# makefile 
default:
	@clear
	@make --no-print-directory sdl
sdl:
	@make --no-print-directory $(SDL)

test: $(EXEC)

txt: 
	@make --no-print-directory $(TXT)

all: $(EXEC) $(SDL) $(TXT)
 

$(EXEC): $(TRGTS) $(MAIN)
	@mkdir -p $(BIN_DIR)/
	@printf $(call color,Linking main:)
	@printf "\n\t *.o ==> $@\n"	
	@$(CC)  $^ $(LIBS) -o $(EXEC) 

$(SDL): $(TRGTS) $(SDL_O)
	@mkdir -p $(BIN_DIR)/
	@printf $(call color,Linking mainSDL:)
	@printf "\n\t *.o ==> $@\n"	
	@$(CC)  $^ $(LIBS) -o $(SDL) 

$(TXT): $(TRGTS) $(TXT_O)
	@mkdir -p $(BIN_DIR)/
	@printf $(call color,Linking mainTXT:)
	@printf "\n\t *.o ==> $@\n"	
	@$(CC)  $^ $(LIBS) -o $(TXT) 

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)/

	@printf $(call color,Compiling main.c:)
	@printf "\n\t $< ==> $@\n"	

	@$(CC) -c $(CFLAGS) $(HEADS) $(LIBS) $< -o $@

$(OBJ_DIR)/mainSDL.o: $(SRC_DIR)/mainSDL.c
	@mkdir -p $(OBJ_DIR)/

	@printf $(call color,Compiling mainSDL.c:)
	@printf "\n\t $< ==> $@\n"	

	@$(CC) -c $(CFLAGS) $(HEADS) $(LIBS) $< -o $@

$(OBJ_DIR)/mainTXT.o: $(SRC_DIR)/mainTXT.c
	@mkdir -p $(OBJ_DIR)/

	@printf $(call color,Compiling mainTXT.c:)
	@printf "\n\t $< ==> $@\n"	

	@$(CC) -c $(CFLAGS) $(HEADS) $(LIBS) $< -o $@

$(OBJ_DIR)/Quest/%.o: $(SRC_DIR)/Quest/%.c
#creating folder if not existing
	@mkdir -p $(OBJ_DIR)/Quest

	@printf $(call color,Compiling Quest files:)
	@printf "\n"

	@cd $(SRC_DIR)/Quest && make -s

$(OBJ_DIR)/Spell/%.o: $(SRC_DIR)/Spell/%.c
#creating folder if not existing
	@mkdir -p $(OBJ_DIR)/Spell 

	@printf $(call color,Compiling Spell files:)
	@printf "\n"

	@cd $(SRC_DIR)/Spell && make -s

$(OBJ_DIR)/Character/%.o: $(SRC_DIR)/Character/%.c
#creating folder if not existing
	@mkdir -p $(OBJ_DIR)/Character 

	@printf $(call color,Compiling Character files:)
	@printf "\n"

	@cd $(SRC_DIR)/Character && make -s
	
$(OBJ_DIR)/Stuff/%.o: $(SRC_DIR)/Stuff/%.c
#creating folder if not existing
	@mkdir -p $(OBJ_DIR)/Stuff 

	@printf $(call color,Compiling Stuff files:)
	@printf "\n"

	@cd $(SRC_DIR)/Stuff && make -s

$(OBJ_DIR)/Map/%.o: $(SRC_DIR)/Map/%.c
#creating folder if not existing
	@mkdir -p $(OBJ_DIR)/Map


	@printf $(call color,Compiling Map files:)
	@printf "\n"

	@cd $(SRC_DIR)/Map && make -s

$(OBJ_DIR)/Gameplay/%.o: $(SRC_DIR)/Gameplay/%.c
	@mkdir -p $(OBJ_DIR)/Gameplay

	@printf $(call color,Compiling Gameplay files:)
	@printf "\n"

	@cd $(SRC_DIR)/Gameplay && make -s

$(OBJ_DIR)/Buffer/%.o: $(SRC_DIR)/Buffer/%.c
	@mkdir -p $(OBJ_DIR)/Buffer

	@printf $(call color,Compiling Buffer files:)
	@printf "\n"

	@cd $(SRC_DIR)/Buffer && make -s

$(OBJ_DIR)/String/%.o: $(SRC_DIR)/String/%.c
	@mkdir -p $(OBJ_DIR)/String

	@printf $(call color,Compiling String files:)
	@printf "\n"

	@cd $(SRC_DIR)/String && make -s

$(OBJ_DIR)/Display/SDL/%.o: $(SRC_DIR)/Display/SDL/%.c
	@mkdir -p $(OBJ_DIR)/Display/SDL

	@printf $(call color,Compiling SDL files:)
	@printf "\n"

	@cd $(SRC_DIR)/Display/SDL && make -s

$(OBJ_DIR)/Display/TXT/%.o: $(SRC_DIR)/Display/TXT/%.c
	@mkdir -p $(OBJ_DIR)/Display/TXT

	@printf $(call color,Compiling TXT files:)
	@printf "\n"

	@cd $(SRC_DIR)/Display/TXT && make -s

#miscalleanous

#execution :

exec_test: 
	@clear
	@./bin/main

exec:
	@clear
	@./$(SDL)
exec_txt:
	@clear
	@./$(TXT)
	
reload:
	@make --no-print-directory veryclean
	@make sdl
	@clear
	@./bin/mainSDL
#Delete .o
clean:

	@printf $(call color,Deleting temp files:\n)

	@cd $(SRC_DIR)/Quest && make --no-print-directory clean
	@cd $(SRC_DIR)/Spell && make --no-print-directory clean
	@cd $(SRC_DIR)/Character && make --no-print-directory clean
	@cd $(SRC_DIR)/Stuff && make --no-print-directory clean
	@cd $(SRC_DIR)/Map && make --no-print-directory clean	
	@cd $(SRC_DIR)/Gameplay && make --no-print-directory clean	
	@cd $(SRC_DIR)/Buffer && make --no-print-directory clean	
	@cd $(SRC_DIR)/String && make --no-print-directory clean	
	@cd $(SRC_DIR)/Display/SDL && make --no-print-directory clean	
	@cd $(SRC_DIR)/Display/TXT && make --no-print-directory clean	
	
	@rm -rf $(OBJ_DIR)/*.o

#Delete .o and exec
veryclean: clean 

	@printf $(call color,Temp files deleted : deleting exec files.)
	@rm -rf  $(BIN_DIR)/*
	@#@rm -rf  $(BIN_DIR)/mainSDL
	@printf "\nDone.\n"


valgrind: default
	@clear
	valgrind $(EXEC)

valgrind_options: default
	@clear
	valgrind $(VALOPTIONS) $(EXEC)


