/*
 * option_display.c
 *
 *  Created on: 10 mars 2020
 *      Author: cuisinier
 */
#include "serial.h"
#include <vt100.h>
#include "option_display.h"
#include "time.h"
#include "menu.h"
#include "stdlib.h"
// définition de variables

//variable nb de vie et nb_invader restants
uint8_t nb_invader = 3;
uint8_t nb_vie = 3;

//variable permettant le déplacement du GAME OVER
uint8_t mc;

uint8_t dead1 = 3; // variable contenant le reste d'invader
uint8_t dead2 = 3; // variable contenant le reste de vie
uint8_t fire_compteur = 0; // variable permettant de temporiser les tirs des invaders
uint8_t pmix = 0; // position du missile invader en x
uint8_t pmiy = 0; // position du missile invader en y

// structure contenant les position x y de l'invader
struct Point{
		uint8_t x, y;
	};
//initialisation de nos invader
char ti_1[1] = "V";
char ti_2[1] = "V";
char ti_3[1] = "V";

//fonction vie permettant l'affichage des vies restantes ainsi que la mise en GAME OVER
void vie(uint8_t nb_invader, uint8_t nb_vie){

	vt100_move(0,2); // position 0 / 2
	serial_puts("--------------------------------------------------------------------------------");
	vt100_move(0,0);
	serial_puts("vie : ");
	vt100_move(7,0);

	// si nombre de vie est a 3
	if (nb_vie == 3){
		serial_puts("3"); // on affiche 3
	}
	else if (nb_vie == 2){
		serial_puts("2");
	}
	else {
		serial_puts("1");
	}

	vt100_move(10,0);
	serial_puts("Invader restants : ");
	vt100_move(29,0);

	// si le nombre d'invader restant est de 3
	if (nb_invader == 3){
		serial_puts("3"); // on affiche 3
	}
	else if (nb_invader == 2){
		serial_puts("2");
	}
	else {
		serial_puts("1");
	}


}


// fonction affichage joueur de paramètres position en x du player / position en x du missile invader / position en y du missile invader
uint8_t player(uint8_t xp, uint8_t xmi, uint8_t ymi){
	vt100_move(xp, 24); // seul la position en x varie le joueur est fixé en bas de l'écraan en y
	serial_puts("¡_|_¡"); // affichage du vaisseau joueur

	// si la position du missile correspond à celle du joueur alors on perd une vie
	if ((xmi == xp || xmi+1 == xp+1 || xmi+2 == xp+2 || xmi+3 == xp+3 || xmi+4 == xp+4) && ymi == 24){
		dead2--;
		// animation clignotante
		vt100_move(xp, 24); // seul la position en x varie le joueur est fixé en y
		serial_puts("¡_|_¡");
		time(300000);
		vt100_move(xp, 24);
		serial_puts("     ");
		time(300000);
		vt100_move(xp, 24);
		serial_puts("¡_|_¡");
		time(300000);
		vt100_move(xp, 24);
		serial_puts("     ");
		time(300000);
		//si dead2 = 0 alors nous n'avons plus de vie on perd
		if (dead2 == 0){
			dead2 =3;
			game_over();
		}
		return dead2;
	}
	else {
		return dead2;
	}

}


//fonction invader pour l'affichage des invaders en fonction des la structure et des tableaux initialisés plus haut
uint8_t invader(uint8_t xi,uint8_t yi,uint8_t xm,uint8_t ym,uint8_t pp){

	// definition des coordonnées
	struct Point c1={5,4}; //v1={x,y}
	struct Point c2={35,4};
	struct Point c3={65,4};

	// attribution des pointeur vers les structure de coordonnées
	struct Point *c12=&c1;
	struct Point *c22=&c2;
	struct Point *c32=&c3;

	// destruction des vaisseaux si coordonnées missile = coordonnées vaisseaux
	if (c12->x+xi == xm && c12->y+yi == ym){

		ti_1[0] = ' '; // remplacement de la forme du vaisseau par du vide
		dead1--; // on enlève le vaisseau au vaisseaux restants
		return dead1; // on retourne la valeur de vaisseaux restants
	}
	else if (c22->x+xi == xm && c22->y+yi == ym){

		ti_2[0] = ' ';
		dead1--;
		return dead1;
	}
	else if (c32->x+xi == xm && c32->y+yi == ym){

		ti_3[0] = ' ';
		dead1--;
		return dead1;
	}
	// si tout les invaders sont détruit alors vous avez gagné !
	else if (ti_1[0] == ' ' && ti_2[0] == ' ' && ti_3[0] == ' '){
		// réinitialisation des variables du plateau de jeu
		ti_1[0] = 'V';
		ti_2[0] = 'V';
		ti_3[0] = 'V';

		dead1 = 3;

		xi = 0;
		yi = 0;
		win();
	}
	// affichage vaisseaux
	vt100_move(c12->x+xi,c12->y+yi);
	serial_puts(ti_1);

	vt100_move(c22->x+xi,c22->y+yi);
	serial_puts(ti_2);

	vt100_move(c32->x+xi,c32->y+yi);
	serial_puts(ti_3);

	// parties du programme permettant de générer des tirs à intévale régulier mais par n'importe quel vaisseaux
	int invader_choose_fire = rand()%(3-0) + 0; // choix du vaisseaux de manière aléatoire
	fire_compteur++; // compteur pour générer le tir
	// si le compteur à atteint la valeur souhaité alors on peut activé le tir
	if (fire_compteur == 100){
		// selon le vaisseaux choisi on tir
		if (invader_choose_fire == 1){
			pmiy = c12-> y+yi; // position en y du départ du missile
									// tant que la position en y n'est pas de 3 on incrémente sa postion
			while (pmiy != 24) {
				pmix = c12->x+xi;
				pmiy += 1;
				vt100_clear_screen();
				// on garde l'affichage des vaisseaux joueur/invader pendant le tir
				player(pp, pmix, pmiy);
				vt100_move(c12->x+xi,c12->y+yi);
				serial_puts(ti_1);

				vt100_move(c22->x+xi,c22->y+yi);
				serial_puts(ti_2);

				vt100_move(c32->x+xi,c32->y+yi);
				serial_puts(ti_3);
				//bloc de commande du tir
				vt100_move(pmix, pmiy);
				serial_putchar('|');
										//invader(pix,piy,pmx,pmy);

				time(200000);
				fire_compteur = 0;

			}
		}
		if (invader_choose_fire == 2){
			pmiy = c22-> y+yi; // position en y du départ du missile
												// tant que la position en y n'est pas de 3 on incrémente sa postion
			while (pmiy != 24) {
				pmix = c22->x+xi;
				pmiy += 1;
				vt100_clear_screen();
				// on garde l'affichage des vaisseaux joueur/invader pendant le tir
				player(pp, pmix, pmiy);
				vt100_move(c12->x+xi,c12->y+yi);
				serial_puts(ti_1);

				vt100_move(c22->x+xi,c22->y+yi);
				serial_puts(ti_2);

				vt100_move(c32->x+xi,c32->y+yi);
				serial_puts(ti_3);
				//bloc de commande du tir
				vt100_move(pmix, pmiy);
				serial_putchar('|');
													//invader(pix,piy,pmx,pmy);

				time(200000);
				fire_compteur = 0;

				}
		}
		if (invader_choose_fire == 3){
			pmiy = c32-> y+yi; // position en y du départ du missile
															// tant que la position en y n'est pas de 3 on incrémente sa postion
			while (pmiy != 24) {
				pmix = c32->x+xi;
				pmiy += 1;
				vt100_clear_screen();
				// on garde l'affichage des vaisseaux joueur/invader pendant le tir
				player(pp, pmix, pmiy);
				vt100_move(c12->x+xi,c12->y+yi);
				serial_puts(ti_1);

				vt100_move(c22->x+xi,c22->y+yi);
				serial_puts(ti_2);

				vt100_move(c32->x+xi,c32->y+yi);
				serial_puts(ti_3);
				//bloc de commande du tir
				vt100_move(pmix, pmiy);
				serial_putchar('|');


				time(200000);
				fire_compteur = 0; // on remet le compteur à 0 une fois le tir effectuer
				}
		}
	}
	return dead1; // retour du nombre de vaisseaux restant à la fonction principale jeu()

}


// fonction game_over pour une issue de partie
void game_over(){
	vt100_clear_screen();
	vt100_move(40, 12);
	serial_puts("GAME OVER !"); // affichage du premier GAME OVER au milieu de l'écran
	time(3000000);
	vt100_clear_screen();
	time(3000000);
	vt100_move(40, 12);
	serial_puts("GAME OVER !");
	time(3000000);
	vt100_clear_screen();
	// mouvement vers le bas du GAME_Over
	for(mc=12;mc<23;mc++){
		vt100_move(40,mc);
		serial_puts("GAME OVER !");
		time(300000);
		vt100_clear_screen();
	}
	//variable nb de vie et nb_invader restants
	nb_invader = 3;
	nb_vie = 3;

	//variable permettant le déplacement du GAME OVER


	dead1 = 3; // variable contenant le reste d'invader
	dead2 = 3; // variable contenant le reste de vie
	fire_compteur = 0; // variable permettant de temporiser les tirs des invaders
	pmix = 0; // position du missile invader en x
	pmiy = 0; // position du missile invader en y



	menu(); // sortit du jeu vers le menu
}

void win(){
	vt100_clear_screen();
	vt100_move(40, 12);
	serial_puts("YOU WIN !");// affichage du premier WINau milieu de l'écran
	time(3000000);
	vt100_clear_screen();
	time(3000000);
	vt100_move(40, 12);
	serial_puts("YOU WIN !");
	time(3000000);
	vt100_clear_screen();
	// mouvement vers le haut du WIN
	for(mc=12;mc>1;mc--){
		vt100_move(40,mc);
		serial_puts("YOU WIN !");
		time(300000);
		vt100_clear_screen();

	}
	//variable nb de vie et nb_invader restants
	nb_invader = 3;
	nb_vie = 3;
		//variable permettant le déplacement du GAME OVER

	dead1 = 3; // variable contenant le reste d'invader
	dead2 = 3; // variable contenant le reste de vie
	fire_compteur = 0; // variable permettant de temporiser les tirs des invaders
	pmix = 0; // position du missile invader en x
	pmiy = 0; // position du missile invader en y

	menu(); // sortit du jeu vers le menu
}


