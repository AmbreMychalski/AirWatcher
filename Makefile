# Flags utilisés dans chaque commande
CPPFLAGS = -ansi -pedantic -Wall -std=c++11 -g

# Edition de liens de main
airwatcher: %.o
	@echo "Edition de liens du main"
	g++ -o airwatcher %.o

# Compilation de tous les fichiers cpp
%.o : %.cpp %.h
	@echo "Compilation de $<"
	g++ -c $< $(CPPFLAGS)

make clean:
	@echo "Suppresion des fichiers compilés"
	touch a.o
	rm *.o
	make

# Vérification au fur et à mesure de
# la gestion de la mémoire avec valgrind
checkMemory :

	@echo "Suppresion des fichiers compilés"
	touch a.o
	rm *.o
	
	make CPPFLAGS='$(CPPFLAGS) -DMAP'

	valgrind ./sejours --track-origins=yes

