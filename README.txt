=================================ZELFUS================================


===== Présentation du jeu : =====
Zelfus en un RPG proposant un système de combat au tour par tour.
Vous devrez menez à bien toute sortes de quêtes afin d’en finir avec ce jeu.


==== Installation : =====
Le jeux utilise les librairies :
- SDL2
- SDL2_image
- SDL2_TTF
- SDL2_mixer
Installations des librairies :
Sous linux :
ubuntu : dans un terminal : « sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install lbsdl2-ttf-dev »

archLinux : dans un terminal : « sudo pacman -s sdl2
sudo pacman -s sdl2-mixer
sudo pacman -s sdl2-ttf
sudo pacman -s sdl2-image

Sous Windows et mac OS :
sdl2 : https://www.libsdl.org/download-2.0.php
sld2-image : https://www.libsdl.org/projects/SDL_image/
sdl2-ttf : https://www.libsdl.org/projects/SDL_ttf/
sdl2-mixer : https://www.libsdl.org/projects/SDL_mixer/




==== Compilation : =====
Un makefile est fourni à la racine du jeu. 
Tapez « make » pour compiler le jeu en version graphique.
make test : pour compiler les tests de regression 
make txt : pour compîler le jeu en version console
make all : pour tout compiler




==== Execution : ====
make exec : lancement du jeu en version graphique
make exec_txt : lancement du jeu en version console
make exec_test : lancement de tout les tests de regressions du programme



==== Règles du jeu ====

Menu :
Au lancement du jeu vous arrivez dans le menu. Pour vous déplacer dans celui-ci
utilisez les fléches haut et bas et la touche entrée pour sélectionner.
Vous pouvez trouver la page relative à la configuration des touches dans le dernier
bouton en bas à droite du menu.

Phase RPG :
Vous incarnez un héros qui se réveil dans un donjon, vous semblez avoir perdu la
mémoire. Vous devrez alors résoudre moultes quêtes afin de comprendre qui vous
êtes et comment sortir de cet endroit.
Votre but dans cette version du jeu est donc de résoudre les quêtes proposées par
les pnj.
Les quêtes vous demanderons de ramasser un certain nombre d’objets et de tuer un
certain nombre de monstres.
Afin de résoudre ces quêtes vous devez tout d’abord allez les accepter. Pour ce
faire il suffit de se mettre à côté d’un pnj et de parler à ce dernier (Touche « T » de
votre clavier pour lancer l’action). Vous pouvez consulter maintenant les objectifs de
votre quête dans votre journal de quête (touche « J » de votre clavier pour lancer
l’action). Une fois que vous avez déterminé combien d’objets doivent être trouvés et
de monstre tués, vous devez vous lancer à la recherche de ces dernier. Quand vous
trouver un objet par terre, vous pouvez le ramasser (touche « P » de votre clavier
pour lancer l’action). Afin de lancer un combat il vous suffit de marcher sur les
monstres (Voir les explications Phase Fight). Quand vous avez remplit l’intégralité
des objectifs de votre quêtes (Toujours disponible dans votre journal de quête), vous
devez allez rendre votre quête auprès du pnj vous l’ayant donné. Pour ceci rien de
plus simple, il suffit de retourner lui parler, comme pour prendre une quête. A ce
moment là vous recevez les récompenses qui était indiquées dans votre journal de
quête.

Phase Fight :

Le combat est un combat tour par tour. Le but est de tuer tout les monstres avant qu’il
ne vous tue.
Vous avez un nombre de points de déplacement (un pas = un point de
déplacement), un nombre de point d’action (Un point par sort lancé) et des points de vie.
Vous pouvez donc vous déplacer d’autant de case que de points d’actions dont vous
disposez. Quand un ennemi est à porté vous pouvez lancer un sort afin d’affliger des
dégâts à ce dernier (touche 1,2,3 du numpad de votre clavier pour lancer le sort en
conséquence). Le jeu déterminera quel cible est la plus proche et lancera le sort sur
celle-ci.
Quand vous ne pouvez plus bouger et/ou lancer de sort vous devez passer votre
tour afin de laisser les monstres jouer (Touche « Entrée » de votre clavier).
A la fin du combat deux issues sont possible soit vous avez perdu, soit gagner.
Quand vous gagner les monstre tué sont comptabilisé dans les objectifs de votre
quête. Quand vous mourrez aucun monstre n’est comptabilisé dans vos objectifs,
vous devrez alors relancer un nouveau combat et tenter de tuer d’autres monstres.




==== Fonctionnalités ====
- Menu
- Initialisation à partir de fichier .init
- Sauvegarde du jeu
- Caméra “vue du dessus” en 2D
- Utilisation de SDL2 pour les fonctionnalité d”affichage principal
- 2 phases de jeu : phase exploration et phase de combat
- Système de combat tour par tour
- Système de gestion de quête
- Intelligence artificelle des Monstres en combat
- Système gestion d’expériences
- Intégration d’une bibliothèque musicale (musique d’ambiance, effets sonnores)
- Déplacement du personnages et toutes interactions réalisés au clavier
- extension propriétaire .map / .init / .save


==== Architecture ====

Racine :

- bin : fichier binaire
- data : contient image, son, sauvegarde et initialisation
- doc : Documentation, powerPoint présentation, diagramme des modules, Gantt
- obj : Contient les fichier .o
- src : contient l'intégrlité du code du jeu
- makefie : makefile du projet 


