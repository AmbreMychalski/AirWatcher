# Definition des variables necessaires au Makefile

# Compilateur
CC = g++

# Flags de compilation
CFLAGS = -g -ansi -pedantic -Wall -std=c++11

# Repertoire des fichiers sources
SRC = ../src

# Repertoire des fichiers assemblés
OBJ = ../build

# Recuperation de tous les fichiers .cpp
# du dossier des sources grâce à la fonction wildcard
SRCS := $(wildcard $(SRC)/*.cpp)
SRCS := $(filter-out $(SRC)/main.cpp, $(SRCS))
SRCS := $(filter-out $(SRC)/mainTest.cpp, $(SRCS))

# Creation des .o à partir des .cpp en utilisant un pattern de substitution
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

# Repertoire et Nom pour l'exécutable
DISTDIR = dist
EXENAME := $(patsubst %.cpp, %, $(wildcard *.cpp))

# Regroupement du Repertoire et du Nom de l'exécutable
# dans une seule variable pour plus de commodité
DIST := $(DISTDIR)/test

#all: CFLAGS = -g -ansi -pedantic -Wall -std=c++11 -D MAP
all: initobj initdist
all: $(DIST)

# Commande d'édition des liens
$(DIST): $(OBJS) $(EXENAME).o
	$(CC) $(CFLAGS) $(OBJS) $(EXENAME).o -o $@

$(EXENAME).o : $(EXENAME).cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Commande d'assemblage (réalise également le traitement par le préprocesseur et la compilation)
$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Commande de nettoyage (destruction de l'exécutable et des fichiers assemblés)
clean:
	$(RM) -r $(DIST) $(OBJ)/*


initobj :
	if [ ! -d "$(OBJ)" ]; then\
		echo "Creating objects directory";\
		mkdir $(OBJ);\
	fi

initdist :
	if [ ! -d "$(DISTDIR)" ]; then\
		echo "Creating dist directory";\
		mkdir $(DISTDIR);\
	fi