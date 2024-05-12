
CXX = g++ -std=c++11
EXEC = .\bin\LaunchThisScript
CXXFLAGS = -Wall -Wextra -Werror

# Path for .c , .h and .o Files 
SRC_PATH = ./src/
OBJ_PATH = ./obj/


# Files to compile
OBJ1 := hidefile.o \
        main.o

OBJ := $(patsubst %,$(OBJ_PATH)%,$(OBJ1))


all : $(EXEC)

$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	$(CXX) -o $@ -c $^

$(EXEC) : $(OBJ)
	@echo [INFO] build exe
	$(CXX) $(CXXFLAGS) -o $@ $^



#efface tous les .o sous windows ou linux
clean :	
	@echo [Cleaning] delete object-files
ifeq ($(OS),Windows_NT)
	del .\obj\*.o
else
	rm -rf $(OBJ_PATH)*.o
endif
	
# clean + efface le .exe
mrproper : clean
	@echo [Cleaning] delete exe
ifeq ($(OS),Windows_NT)	
	del $(EXEC).exe
else
	rm -f $(EXEC)
endif


#zip :


#<cible> : <dependances>
#    <commande>

#variable
#NOM = VALEUR
# pour utiliser la variable  $(NOM)

# CC / CXX
# CFLAGS / CXXFLAGS
# LDFLAGS
# SRC
# OBJ
# EXE

# variable spéciales
# $@ nom de la cible
# $< nom de la 1ier dependance
# $^ liste dependances
# $? liste dependances plus recentes que la cible
# $* nom fichier, sans son extension

# % tous les objets