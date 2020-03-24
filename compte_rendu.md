># Compte Rendu Projet : SPACE INVADER
>Par Guillaume Cuisinier B3 


---

## Le Mode d'emploi de la mise en marche du programme :

* **Dans un terminal :** 
  * 1°étape lancer screen dans le terminal avec :

    ```unix
    $:screen
    ```
  * 2°étape initialiser la voie de communication en écriture et lancer screen :

    ```unix
    $:sudo chmod +x /dev/ttyUSB0
    $:screen /dev/ttyUSB0 115200
    ```

* **Atolic TRUESTUDIO :**

Au sein du logiciel ATOLIC TRUESTUDIO, il suffit **d'ajouter** le fichier projet, de lancer le build en utilisant **CTRL + B** et de debugger le programme en appuyant sur **F11**.

Il ne reste plus qu'a lancer l'execution du programme avec le bouton **"play"** vert.

* **Le jeu :**

Pour jouer rien de plus simple comme indiquer au démarrage du jeu il suffit de presser "**p**"

* **Les déplacements :** 

  * **q**     =    Gauche
  * **d**     =    Droite
  * **f**     =    Tirer
  * **ESC**   =    Revenir à l'écran d'accueil
  * **m**     =    Relancer le jeu

---

## Les Dificultés rencontrées :

La principale difficulté à été la décomposition du programme principal, en plusieurs fonctions au sein de différents fichiers ".h" et ".c".

Puis la coordination entre chaque fonction et la remise à zéro des variables


---

## Les Notions apprises / découvertes / peaufinées :

Lors de ce projet, j'ai principalement appris à utiliser d'avantage les notions aprises en C, à créer et utiliser les libraires et à maitriser d'avantage la coordination des variables, et des fonctions entre elles.

Il me reste encore à créer la fonction d'initialisation de toutes mes variables et de l'inclure dans le programme


--- 
## Les Points à regarder :

L'ensemple du fichier option_display.c et sont fonctionnement avec le jeu.c. J'aimerais avoir votre avis sur mon programme, les points positifs et ceux que je peux améliorer.

---

## Mon retour d'expérience sur ce projet :


A travers ce projet j'ai pu perfectionner ma rédaction en C et maitriser d'avantage l'intégralité du langage. En bref, j'ai bien aimé ce projet de part son originalité et l'utilisation du VT100 par le biais du terminal linux.
