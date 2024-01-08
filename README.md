# Etude-de-graphes-issus-du-Web
Dans ce projet, on s’intéressera à différents graphes du Web. On va étudier en particulier des 
graphes issus de la basede données des grands graphes de Stanford qui modélisent différents 
réseaux sociaux. Typiquement,ces graphes sont représentés sous forme de fichier texte, dans
lequel sont donnés leurs arêtes et sommets.Ce projet C++ vise à effectuer une analyse de 
différents graphes en termes de sommets, arêtes, degré maximal, composantes connexes, cycles
 avec 3 sommets et dégénérescence. Le programme prend en charge les fichiers graphiques aux 
formats txt et csv.

## Table des matières

- [Installation](#installation)
- [Utilisation](#utilisation)


## Installation
git clone https://github.com/John-the-ripp/Etude-de-graphes-issus-du-Web
cd Projet.cpp
et compiler le code
g++ -o Projet Projet.cpp
pour le code python
pip install pandas
pip install matplotlib.pyplot


## Utilisation
dans la ligne 212 du code "ofstream outputCSV("...output2.csv");" remplacer le chemin existant avec le chemin où vous souhaiter stocker votre résultat
Executer : 
./Projet
et puis vous allez remarquer la création l'output qui contient les informations à savoir 
Nom du graphe; Nombre de sommets; Nombre d'arêtes; Degré maximal; Nombre de composantes connexes; Nombre de cycles avec 3 sommets; dégénérescence
pour visiualiser la fréquence des différents degrés il faut d'abord executer ./Projet et aprés exécuter graph_generated.py 
