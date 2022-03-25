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

void initRobotMoi(){
	allumerPeriph(PILOTE_BASE);
	allumerPeriph(PILOTE_EPAULE);
	allumerPeriph(PILOTE_COUDE);
	allumerPeriph(PILOTE_POIGNET);
	allumerPeriph(PILOTE_PINCE);
	
	initGeneSignal(PILOTE_BASE, DIV32, 52500UL, 3938UL, INVERSE);
	initGeneSignal(PILOTE_EPAULE, DIV32, 52500UL, 3938UL, INVERSE);
	initGeneSignal(PILOTE_COUDE, DIV32, 52500UL, 3938UL, INVERSE);
	initGeneSignal(PILOTE_POIGNET, DIV32, 52500UL, 3938UL, INVERSE);
	initGeneSignal(PILOTE_PINCE, DIV32, 52500UL, 3938UL, INVERSE);
	
	allumerPeriph(PORT_BASE);
	allumerPeriph(PORT_EPAULE);
	allumerPeriph(PORT_COUDE);
	allumerPeriph(PORT_POIGNET);
	allumerPeriph(PORT_PINCE);
	
	programmerLigne(PORT_BASE, LIGNE_BASE, FONCTIONB);
	programmerLigne(PORT_EPAULE, LIGNE_EPAULE, FONCTIONB);
	programmerLigne(PORT_COUDE, LIGNE_COUDE, FONCTIONB);
	programmerLigne(PORT_POIGNET, LIGNE_POIGNET, FONCTIONB);
	programmerLigne(PORT_PINCE, LIGNE_PINCE, FONCTIONB);
}

void positionnerMoteurMoi(int moteur, float angle){
	Peripherique genSig[] = {PILOTE_BASE, PILOTE_EPAULE, PILOTE_COUDE, PILOTE_POIGNET, PILOTE_PINCE};
	uint16_t seuil = (((((uint16_t)angle+90)*1800)/180)+600)/(8/21);
	modifierSeuilGeneSignal(genSig[moteur], seuil);
}

void init(){
	initCarte();
	configureConsole();
	initRobotMoi();
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

float positionnerMoteurLent(int moteur, float angle, float prevAngle, int vitesse){
	if (!(angle < -90 || angle > 90)){
		lancerTimer(TIMER_MOTEURS);
		if (angle > prevAngle){
			for (int i = prevAngle; i < angle; i+=vitesse){
				positionnerMoteur(moteur, i);
				while (!(testerEtatTimer(TIMER_MOTEURS, LIMITE)));
			}
		}
		else{
			for (int i = prevAngle; i > angle; i-=vitesse){
				positionnerMoteur(moteur, i);
				while (!(testerEtatTimer(TIMER_MOTEURS, LIMITE)));
			}
		}
		positionnerMoteur(moteur, angle);
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
		prevAngle[i] = positionnerMoteurLent(i, 0, prevAngle[i], 1);
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
	int longVitesse = vitesse;
	if (longVitesse < 0){
		longVitesse = -1*longVitesse;
	}
	printf("vitesse : %i\n", longVitesse);
	int angle = angleActuel + vitesse;
	int nouvAngle = positionnerMoteurLent(moteur, angle, angleActuel, longVitesse);
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
					prevAngle[indiceMot] = positionnerMoteurLent(indiceMot, posision[indicePos[indiceMot]], prevAngle[indiceMot], 1);
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
				prevAngle[indiceCAN] = positionnerMoteurLent(indiceCAN, ((((mes/10)*90)/409)-45), prevAngle[indiceCAN], 1);
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