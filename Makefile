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
TESTNAME = airwatchertest

# Regroupement du Repertoire et du Nom de l'exécutable
# dans une seule variable pour plus de commodité
DIST = $(DISTDIR)/$(EXENAME)
TEST = $(DISTDIR)/$(TESTNAME)

# Creation de l'exécutable en mode Production
all: SRCS := $(filter-out %mainTest.cpp, $(SRCS))
all: initobj initdist
all: $(DIST)

#test: CFLAGS = -g -ansi -pedantic -Wall -std=c++11 -D MAP
test: SRCS := $(filter-out %main.cpp, $(SRCS))
test: initobj initdist
test: $(TEST)

# Creation de l'exécutable en mode Debug
release: CFLAGS = -g -ansi -pedantic -Wall -std=c++11 -D MAP
release: clean
release: $(DIST)

# Commande d'édition des liens
$(DIST): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	
# Commande d'édition des liens
$(TEST): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Commande d'assemblage (réalise également le traitement par le préprocesseur et la compilation)
$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Commande de nettoyage (destruction de l'exécutable et des fichiers assemblés)
clean:
	$(RM) -r $(DISTDIR)/* $(OBJ)/*

# Commande d'initialisation du projet
init : initobj initsrc

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

initsrc :
	if [ ! -d "$(SRC)" ]; then\
		echo "Creating source directory";\
		mkdir $(SRC);\
	fi
