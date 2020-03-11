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
	uint8_t pix = 5; // déclaration de la position de départ des ennemis en x
	uint8_t piy = 3; // en y

	uint16_t ci = 0; // conteur pour temperer les déplacements des enemis

	uint16_t clavier2 = 0; // variable contenant la valeur de la touche clavier appuyé

	vt100_clear_screen();


	while(clavier2 != 0x6D && clavier2 != 0x1B){

					clavier2 = serial_get_last_char();
					vt100_move(0,2);

					//début du jeu
					serial_puts("-----------------------------------------------------------");
		 	 	 	player(i);
					invader(pix,piy,0,0);


					//position invader


					//mouvement vers la droite
					if (clavier2 == 0x71) {
						i -= 1;
						vt100_clear_screen();
						player(i);

					}
					//mouvement vers la gauche
					if (clavier2 == 0x64) {
						i += 1;
						vt100_clear_screen();
						player(i);
					}


					// commande de tir
					if (clavier2 == 0x66) {
						pmy = 23;
						while (pmy != 3) {
							pmx = i + 2;
							pmy -= 1;
							vt100_clear_screen();

							// on garde l'affichage des vaisseaux pendant le tir
							player(i);
							invader(pix,piy,0,0);

							//bloc de commande du tir
							vt100_move(pmx, pmy);
							serial_putchar('^');
							invader(pix,piy,pmx,pmy);

							time(200000);

							//destruction invader
						}
						vt100_clear_screen();
					}
					else {
						player(i);
						ci++;
						if (ci == 50){
							pix++;
							ci = 0;
							vt100_clear_screen();
						}
						if (pix == 70){
							piy++;
							pix--;
						}


						invader(pix,piy,0,0);

					}

	}

	if (clavier2 == 0x6D){
		//exit = 1;
		vt100_clear_screen();
		return 1;
		//menu();
	}

	return 0;
}


