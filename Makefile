# Definition des variables necessaires au Makefile

# Compilateur
CC = g++

# Flags de compilation
CFLAGS = -g -ansi -pedantic -Wall -std=c++11

# Repertoire des fichiers sources
SRC = ./src

# Repertoire des fichiers assemblés
OBJ = ./build

# Recuperation de tous les fichiers .h et .cpp
# du dossier des sources grâce à la fonction wildcard
SRCS = $(wildcard $(SRC)/*.cpp)

# Creation des .o à partir des .cpp en utilisant un pattern de substitution
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

# Repertoire et Nom pour l'exécutable
DISTDIR = dist
EXENAME = airwatcher

# Regroupement du Repertoire et du Nom de l'exécutable
# dans une seule variable pour plus de commodité
DIST = $(DISTDIR)/$(EXENAME)

# Creation de l'exécutable en mode Production
all: initobj initdist
all: $(DIST)

# Creation de l'exécutable en mode Debug
debug: CFLAGS = -g -ansi -pedantic -Wall -std=c++11 -D MAP
debug: clean
debug: all

# Commande d'édition des liens
$(DIST): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Commande d'assemblage (réalise également le traitement par le préprocesseur et la compilation)
$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Commande de nettoyage (destruction de l'exécutable et des fichiers assemblés)
clean:
	$(RM) -r $(DISTDIR)/* $(OBJ)/*


initobj :
	mkdir -p -v $(OBJ)

initdist :
	mkdir -p -v $(DISTDIR)
