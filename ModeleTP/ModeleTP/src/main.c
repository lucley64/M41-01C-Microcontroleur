#include "libTPIUT.h"
#include "robot.h"

#define BP1 25
#define BP2 26
#define DEL_GAUCHE 30
#define DEL_MILLIEU 21
#define DEL_DROITE 27
#define TIMER Timer1
#define TIMER_RESET Timer0

void resetMot();

void init(){
	initCarte();
	configureConsole();
	initRobot();
	allumerPeriph(PortA);
	allumerPeriph(PortB);
	allumerPeriph(PortC);
	activerFiltrageLigne(PortB, BP1, 40);
	programmerLigne(PortB, BP1, ENTREE);
	activerFiltrageLigne(PortB, BP1, 40);
	programmerLigne(PortC, BP2, ENTREE);
	activerFiltrageLigne(PortC, BP2, 40);
	programmerLigne(PortA, DEL_MILLIEU, SORTIE1);
	programmerLigne(PortB, DEL_DROITE, SORTIE0);
	programmerLigne(PortC, DEL_GAUCHE, SORTIE1);
	
	allumerPeriph(TIMER);
	timerModeDelai(TIMER, HDIV2, 1680000UL, REPETITIF, INC);
	
	allumerPeriph(TIMER_RESET);
	timerModeDelai(TIMER_RESET,HDIV2, 42000000UL, NON_REPETITIF, INC);
	autoriserITTimer(TIMER_RESET, LIMITE, 0, resetMot);
}

float positionnerMoteurLent(int moteur, float angle, float prevAngle){
	lancerTimer(TIMER);
	if (angle > prevAngle){
		for (int i = prevAngle; i < angle; i++){
			positionnerMoteur(moteur, i);
			while (!(testerEtatTimer(TIMER, LIMITE)));
		}
	}
	else{
		for (int i = prevAngle; i > angle; i--){
			positionnerMoteur(moteur, i);
			while (!(testerEtatTimer(TIMER, LIMITE)));
		}
	}
	arreterTimer(TIMER);
	return angle;
}

int indicePos[] = {0, 0, 0, 0, 0};
float prevAngle[] = {0, 0, 0, 0, 0};
int isInter = 0;	

void resetMot(){
	for (int i = 0; i < 5; i++){
		prevAngle[i] = positionnerMoteurLent(i, 0, prevAngle[i]);
		indicePos[i] = 0;
	}
	isInter = 1;
}

int main (void) {
	init();
	int posision[] = {30, 0, -30, 0};
	int del[] = {DEL_GAUCHE, DEL_MILLIEU, DEL_DROITE};
	int portsDel[] = {PortC, PortA, PortB};
	int indiceMot = 0;
	/// TP2 : 
	
	//while (1){
		//if(lireLigne(PortB, BP1)){
			//lancerTimer(TIMER_RESET);
			//while(lireLigne(PortB, BP1));
			//arreterTimer(TIMER_RESET);
			//if (!isInter){
				//prevAngle[0] = positionnerMoteurLent(BASE, posision[indicePos[0]], prevAngle[0]);
				//indicePos[0] = (indicePos[0]+1)%4;
				//while(lireLigne(PortB, BP1));
			//}
			//isInter = 0;
		//}
	//}
	
	/// TP1 et 2 : 
	while(true) {
		if(lireLigne(PortB, BP1)){
			lancerTimer(TIMER_RESET);
			while(lireLigne(PortB, BP1));
			arreterTimer(TIMER_RESET);
			if (!isInter) {
				if(indiceMot == 5){
					resetMot();
				}
				else{
					printf("BP1 appuié\n");
					prevAngle[indiceMot] = positionnerMoteurLent(indiceMot, posision[indicePos[indiceMot]], prevAngle[indiceMot]);
					indicePos[indiceMot] = (indicePos[indiceMot]+1)%4;
				}
			}
			isInter = 0;
		}
		if(lireLigne(PortC, BP2)){
			printf("BP2 appuié\n");
			indiceMot = (indiceMot+1)%6;
			int indiceMotToBin = indiceMot;
			if (indiceMot != 5){
				for(int i = 0; i < 3; i++){
					int bin = !(indiceMotToBin%2);
					printf("%d", !bin);
					if (del[i] == DEL_DROITE){
						bin = !bin;
					}
					ecrireLigne(portsDel[i], del[i], bin);
					indiceMotToBin /= 2;
				}
				printf("\n");
			}
			else{
				ecrireLigne(PortC, DEL_GAUCHE, 0);
				ecrireLigne(PortA, DEL_MILLIEU, 0);
				ecrireLigne(PortB, DEL_DROITE, 1);
			}
			while(lireLigne(PortC,BP2));
		}
	}
}