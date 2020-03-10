/*
 * jeu.c
 *
 *  Created on: 4 mars 2020
 *      Author: cuisinier
 */

#include "serial.h"
#include <vt100.h>
#include "jeu.h"

void jeu(){

	uint8_t tab_invader[10]= "\\''0''//";
	uint8_t i = 40;
	uint8_t pmx = 0;
	uint8_t pmy = 23;
	uint8_t pix = 0;
	uint8_t piy = 0;
	float c;
	uint16_t ci = 0;
	uint8_t cib = 0;
	int exit = 0;
	uint16_t clavier2 = 0;


	while(clavier2 != 0x6D && clavier2 != 0x1B){

					clavier2 = serial_get_last_char();
		 	 	 	vt100_move(i, 24);
					serial_puts("¡_|_¡");
					vt100_move(pix,piy);
					serial_puts(tab_invader);


					//position invader


					//mouvement vers la droite
					if (clavier2 == 0x71) {
						i -= 1;
						vt100_clear_screen();
						vt100_move(i, 24);
						serial_puts("¡_|_¡");

					}
					//mouvement vers la gauche
					if (clavier2 == 0x64) {
						i += 1;
						vt100_clear_screen();
						vt100_move(i, 24);
						serial_puts("¡_|_¡");
					}


					// commande de tir
					if (clavier2 == 0x66) {
						pmy = 23;
						while (pmy != 0) {
							pmx = i + 2;
							pmy -= 1;
							vt100_clear_screen();

							// on garde l'affichage des vaisseaux pendant le tir
							vt100_move(i, 24);
							serial_puts("¡_|_¡");
							vt100_move(pix,piy);
							serial_puts(tab_invader);

							//bloc de commande du tir
							vt100_move(pmx, pmy);
							serial_putchar('^');
							if (pmy == piy && pmx == pix+4){
								while (cib < 10){
								tab_invader[cib] = ' ';
								cib++;
								}
								break;
							}

							for(c=0;c<200000;c++);

							//destruction invader
						}
						vt100_clear_screen();
					}
					else {
						vt100_move(i, 24);
						serial_puts("¡_|_¡");
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


						vt100_move(pix,piy);
						serial_puts(tab_invader);

					}

	}

	if (clavier2 == 0x6D){
		//exit = 1;
		return 1;
	}
	if (clavier2 == 0x1B){
		//exit = 2;
		return 2;
	}
	//return exit;
};


