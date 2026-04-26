/*
 * counter.c
 *
 *  Created on: Feb 16, 2026
 *      Author: imane
 */



// static STATE state;
 // mémorise où on est

/*void counter_init(void)
{
    state = NO_DETECTED;
    counter = 0;
}

void update_counter(int left_detected, int right_detected){
	if(state==NO_DETECTED){
		if(left_detected){
			state=LEFT_FIRST;
		}
		else if(right_detected){
			state=RIGHT_FIRST;
		}
	}
	if(state==LEFT_FIRST){
		if(right_detected){
			counter++;
			state=NO_DETECTED;
		}
	}
	if(state==RIGHT_FIRST){
		if(left_detected){
			counter--;
			state=NO_DETECTED;
		}
	}
}

int value_counter(void){
	return counter;
}*/

#include "utils.h"
#include "counter.h"
#define SEUIL 2000

void update_counter(int tab[8][8], int counter)
{
	if(moy(tab[3]) < SEUIL)
	{
	    while(moy(tab[7]) > SEUIL)
	    {
	    	setup();
	    }

	    while(moy(tab[7]) < SEUIL)
	    {
	    	setup();
	    }

	    counter++;
	}

	else if(moy(tab[4]) < SEUIL)
	{
	    while(moy(tab[0]) > SEUIL)
	    {
	    	setup();
	    }

	    while(moy(tab[0]) < SEUIL)
	    {
	    	setup();
	    }
	    counter--;
	}
}






