/*
 * jeu.c
 *
 *  Created on: 4 mars 2020
 *      Author: cuisinier
 */

#include "serial.h"
#include <vt100.h>
#include "jeu.h"
#include "time.h"
#include "option_display.h"

uint8_t jeu(void){

	//char tab_invader[2]= "v";
	uint8_t i = 40;  // position de départ du joueur
	uint8_t pmx = 0; // déclaration de la variable pour la coordonée x du missile
	uint8_t pmy = 23; // déclaration de la variable pour la coordonée y du missile
	int8_t pix = 4; // déclaration de la position de départ des ennemis en x
	uint8_t piy = 2; // en y

	uint16_t ci = 0; // conteur pour temperer les déplacements des enemis
	uint8_t mode = 0; // variable pour le mode de déplacement das invaders droite gauche et inversement

	uint8_t dead_invader = 0; // variable pour le nombre d'invaders morts
	uint8_t dead_life = 0; // variable pour le nombre de vies mortes

	uint16_t clavier2 = 0; // variable contenant la valeur de la touche clavier appuyé

	vt100_clear_screen(); // on commence par préparer le plateau de jeu en effacant tout

	// tant qu'on appuye pas sur "ESC" ou "m" on joue
	while(clavier2 != 0x6D && clavier2 != 0x1B){

					clavier2 = serial_get_last_char();
					/*vt100_move(0,2);

					//début du jeu
					serial_puts("-----------------------------------------------------------");*/
		 	 	 	player(i,0,0); // joueur
					invader(pix,piy,0,0,i); // invader
					//vie(0,0);

					//mouvement vers la droite
					if (clavier2 == 0x71) {
						i -= 1;
						vt100_clear_screen();
						player(i,0,0);


					}
					//mouvement vers la gauche
					if (clavier2 == 0x64) {
						i += 1;
						vt100_clear_screen();
						player(i,0,0);
					}


					// commande de tir appuye sur "f"
					if (clavier2 == 0x66) {
						pmy = 23; // position en y du départ du missile
						// tant que la position en y n'est pas de 3 on incrémente sa postion
						while (pmy != 3) {
							pmx = i + 2;
							pmy -= 1;
							vt100_clear_screen();

							// on garde l'affichage des vaisseaux joueur/invader pendant le tir
							player(i,0,0);
							invader(pix,piy,0,0,i);

							//bloc de commande du tir
							vt100_move(pmx, pmy);
							serial_putchar('^');
							//invader(pix,piy,pmx,pmy);
							invader(pix,piy,pmx,pmy,i);
							time(200000);

							//destruction invader
						}
						vt100_clear_screen();
					}
					// sinon on garde l'affichage de tout le monde avec le déplacement des invaders
					else {
						player(i,0,0);
						ci++;
						if (ci == 50 && mode == 0){
							pix++;
							ci = 0;
							if (pix == 8){
								piy++;
								mode = 1;
							}
							vt100_clear_screen();
						}
						if (ci == 50 && mode == 1){
							pix--;
							ci = 0;
							if (pix == 4){
								piy++;
								mode = 0;
							}
							vt100_clear_screen();
						}
						/*if (pix == 65){
							piy++;
							pix--;
						}
						*/


						dead_invader = invader(pix,piy,0,0,i);
						dead_life = player(i,0,0);
						vie(dead_invader, dead_life);
					}

	}
	// si on appuie sur m on retourne au menu
	if (clavier2 == 0x6D){
		//exit = 1;
		vt100_clear_screen();


		dead_invader = 0;
		dead_life = 0;
		return 1;
		//menu();
	}
	dead_invader = 0;
	dead_life = 0;

	// si on appuie sur ESC on sort du jeu
	return 0;
}


