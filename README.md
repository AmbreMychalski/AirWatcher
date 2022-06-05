# AirWatcher

AirWatcher is a software application that allows a government agency to monitor the air quality of a large territory.

## Creation of executable file

Use Makefile command `make` to create the AirWatcher executable file, `make debug` for debug builds, and `make clean` to delete all files in `/dist` and `/build` directories (executable and objects files).

## Usage

Launch the app with `./dist/airwatcher` in your terminal.

```
-----------------------------------------------------------------------------------------------
                                   AirWatcher
-----------------------------------------------------------------------------------------------
-----------------------------------Choix du Menu-----------------------------------------------
1. Citoyen       2. Entreprise       3. Gouvernement       |4. Quitter l'application
```

Then, choose your category or leave the app by writing the corresponding number.

### Private indivual user (1)

Log in with your id (they are listed in `./datasets/users.csv` file).
```
1) Voir mes points
2) Voir mes capteurs
3) Sélectionner un capteur
4) Voir mes mesures
5) Voir mon statut
6) Me déconnecter
```
Then you can see your AirCoins(1), view the list of your sensors (2), select one of your sensors to get more information (3), view the list of your measurements (4), your status (5) - if you are reliable or not -, or log out (6).

### Air cleaners provider (2)

Log in with your id (they are listed in `./datasets/providers.csv` file).
```
1) Voir la liste d'Air Cleaner(s)
2) Me déconnecter
```
Not many features are available for now. You can either view the list of your air cleaners (1), or log out (2).

### Government agency (3)

```
1) Calculer l'indice ATMO Moyen en un point donné sur une période donnée
2) Calculer le pourcentage de similarité d'un capteur avec ceux qui l'entoure
3) Afficher les capteurs
4) Afficher les mesures d'un capteur
5) Afficher les Air Cleaner(s)
6) Afficher un Air Cleaner
7) Me déconnecter
```
You can get the average of the ATMO index in a circular area around a given point and during a given period (1), get the list of all sensors ordered by their similarity to a given reference sensor, calculated over a given period (2), view the list of sensors with their information (3), view the list of measurements (4), view the list of air cleaners (5), view information about one specific air cleaner (6), or log out (7).

## Tests

To run the tests, you have to change your current working directory to `./tests`, and then use the `make` command (it may be a bit long). Finally, execute `./dist/test`, and hopefully, if there is no issue, you will get this message:

```
All tests passed (132 assertions in 7 test cases)
```

We used the framework [Catch2](https://github.com/catchorg/Catch2)  to make testing easier.