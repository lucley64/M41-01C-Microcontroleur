#include "libTPIUT.h"
#include "robot.h"

#define BP1 25
#define BP2 26
#define DEL_GAUCHE 30
#define DEL_MILLIEU 21
#define DEL_DROITE 27
#define TIMER Timer1
#define TIMER_RESET Timer0
#define BOUT_ROT 24
#define TIMER_MOTEURS Timer2

void resetMot();
void resetMoteurLent();

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
	timerModeDeclenchement(TIMER, HDIV2, 420000UL, REPETITIF);
	
	allumerPeriph(TIMER_MOTEURS);
	timerModeDelai(TIMER_MOTEURS, HDIV2, 1680000UL, REPETITIF, INC);
	
	allumerPeriph(TIMER_RESET);
	timerModeDelai(TIMER_RESET,HDIV2, 42000000UL, NON_REPETITIF, INC);
	autoriserITTimer(TIMER_RESET, LIMITE, 0, resetMoteurLent);
	
	allumerPeriph(ConvAN);
	initConvAN(10, RES12BITS);
	programmerLigne(PortA, BOUT_ROT, ENTREE);
	programmerLigne(PortA, 22, ENTREE);
	programmerLigne(PortA, 23, ENTREE);
	programmerLigne(PortA, 6, ENTREE);
	programmerLigne(PortA, 5, ENTREE);
	declenchementConvAN(TIMER);
}

float positionnerMoteurLent(int moteur, float angle, float prevAngle){
	if (!(angle < -90 || angle > 90)){
		lancerTimer(TIMER_MOTEURS);
			if (angle > prevAngle){
				for (int i = prevAngle; i < angle; i++){
					positionnerMoteur(moteur, i);
					while (!(testerEtatTimer(TIMER_MOTEURS, LIMITE)));
				}
			}
			else{
				for (int i = prevAngle; i > angle; i--){
					positionnerMoteur(moteur, i);
					while (!(testerEtatTimer(TIMER_MOTEURS, LIMITE)));
				}
			}
		arreterTimer(TIMER_MOTEURS);
		return angle;
	}
	else{
		printf("NOPE\n");
		return prevAngle;
	}
}

int indicePos[] = {0, 0, 0, 0, 0};
float prevAngle[] = {0, 0, 0, 0, 0};
int isInterrompu = 0;	

void resetMot(){
	for (int i = 0; i < 5; i++){
		prevAngle[i] = positionnerMoteurLent(i, 0, prevAngle[i]);
		indicePos[i] = 0;
	}
	isInterrompu = 1;
}

void resetMoteurLent(){
	int done = 0;
		lancerTimer(TIMER_MOTEURS);
		do{
		done = 0;
		for(int i = 0; i < 5; i++){
			if(prevAngle[i] < 0){
				prevAngle[i]+=1;
				positionnerMoteur(i, prevAngle[i]);
			}
			else if(prevAngle[i] > 0){
				prevAngle[i]-=1;
				positionnerMoteur(i, prevAngle[i]);
			}
			else{
				indicePos[i] = 0;
				done ++;
			}
		}
		while (!(testerEtatTimer(TIMER_MOTEURS, LIMITE)));
	}while(done<5);
		arreterTimer(TIMER_MOTEURS);
		isInterrompu = 1;
}

int bougerMoteurAvecVitesse(int vitesse, int moteur, int angleActuel){
	unsigned long int longVitesse = ((vitesse+10)*160000)/20;
	printf("%d\n", longVitesse);
	//timerModeDelai(TIMER_MOTEURS, HDIV2, 1680000UL, REPETITIF, INC);
	int angle = angleActuel + vitesse;
	int nouvAngle = positionnerMoteurLent(moteur, angle, angleActuel);
	return nouvAngle;
}

int main (void) {
	init();
	int posision[] = {30, 0, -30, 0};
	int del[] = {DEL_GAUCHE, DEL_MILLIEU, DEL_DROITE};
	int portsDel[] = {PortC, PortA, PortB};
	int indiceMot = 0;
	int mes = 0;
	int cANs[] = {FIN_CONV2, FIN_CONV3, FIN_CONV4, FIN_CONV5, FIN_CONV6};
	int indiceCAN = 0;
	int correctionEntree[] = {0, 1, 1, 0, 0};
	choisirEntreeConvAN(indiceCAN+2);
	lancerTimer(TIMER);
	lancerConversionAN();
	/// TP2 petit:
	//while (1){
		//if(lireLigne(PortB, BP1)){
			//lancerTimer(TIMER_RESET);
			//while(lireLigne(PortB, BP1));
			//arreterTimer(TIMER_RESET);
			//if (!isInterrompu){
				//prevAngle[0] = positionnerMoteurLent(BASE, posision[indicePos[0]], prevAngle[0]);
				//indicePos[0] = (indicePos[0]+1)%4;
				//while(lireLigne(PortB, BP1));
			//}
			//isInterrompu = 0;
		//}
	//}
	
	/// TP1 et 2 : 
	while(1) {
		if(lireLigne(PortB, BP1)){
			lancerTimer(TIMER_RESET);
			while(lireLigne(PortB, BP1));
			arreterTimer(TIMER_RESET);
			if (!isInterrompu) {
				if(indiceMot == 5){
					resetMoteurLent();
				}
				else{
					printf("BP1 appuié\n");
					prevAngle[indiceMot] = positionnerMoteurLent(indiceMot, posision[indicePos[indiceMot]], prevAngle[indiceMot]);
					indicePos[indiceMot] = (indicePos[indiceMot]+1)%4;
				}
			}
			isInterrompu = 0;
		}
		else if(lireLigne(PortC, BP2)){
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
		if (testerEtatConvAN(cANs[indiceCAN])){
			mes = lireValeurConvAN(indiceCAN+2);
			printf("CAN num %d %d : %d\n",indiceCAN, mes, ((((mes/10)*20)/409)-10)+correctionEntree[indiceCAN]);
			if (indiceCAN == 4)
			{
				prevAngle[indiceCAN] = positionnerMoteurLent(indiceCAN, ((((mes/10)*90)/409)-45), prevAngle[indiceCAN]);
			} 
			else
			{
				prevAngle[indiceCAN] = bougerMoteurAvecVitesse(((((mes/10)*20)/409)-10)+correctionEntree[indiceCAN], indiceCAN, prevAngle[indiceCAN]);
			}
			lancerTimer(TIMER);
			indiceCAN = (indiceCAN+1)%5;
			choisirEntreeConvAN(indiceCAN+2);
		}
	}
	
	
	// Test
	//int mes = 0;
	//int prevAngle = 0;
	//lancerConversionAN();
	//while(1){
		//while(!testerEtatConvAN(FIN_CONV6));
		//lancerTimer(TIMER);
		//mes = lireValeurConvAN(6);
		//positionnerMoteur(PINCE, ((mes*180)/1023)-90);
		//while(!testerEtatTimer(TIMER, LIMITE));
		//arreterTimer(TIMER);
	//}
}