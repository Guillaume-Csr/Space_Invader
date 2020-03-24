/*
 * option_display.h
 *
 *  Created on: 10 mars 2020
 *      Author: cuisinier
 */

#ifndef OPTION_DISPLAY_H_
#define OPTION_DISPLAY_H_


void vie(uint8_t nb_invader, uint8_t nb_vie);
uint8_t player(uint8_t xp,uint8_t xmi, uint8_t ymi);
uint8_t invader(uint8_t xi,uint8_t yi,uint8_t xm,uint8_t ym, uint8_t pp);


void game_over();
void win();

#endif /* OPTION_DISPLAY_H_ */
