#include "libTPIUT.h"
#include "robot.h"

#define BP1 25
#define MOT_BASE 5

void init(){
	initCarte();
	configureConsole();
	initRobot();
	allumerPeriph(PortB);
	programmerLigne(PortB, BP1, ENTREE);
	activerFiltrageLigne(PortB, BP1, 20);
}

int main (void)
{
	init();
	int posision[] = {10, 0, -10, 0};
	int i = 0;
	while(true) {
		if(lireLigne(PortB, BP1)){
			positionnerMoteur(BASE, posision[i]);
			printf("Bouton appuié");
			i = (i+1)%4;
			while(lireLigne(PortB, BP1));
		}
	}
}

