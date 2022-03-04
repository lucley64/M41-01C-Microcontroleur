/*
 * libTPsIUT.h
 *
 * Created: 22/11/2016
 * Author : Dalmau
 */ 

#ifndef LIBTPIUT_INCLUSE
#define LIBTPIUT_INCLUSE

#include "sam3xa.h"
#include "stdbool.h"
#include "stdint.h"
#include "periphs.h"
/*
	Connexion des ports à la carte Arduino Due :
	--------------------------------------------
 Ligne	PortA	PortB	PortC	PortD
	0	CANRX					25
	1	CANTX			33		26
	2	A7				34		27
	3	A6				35		28
	4	A5				36		14
	5					37		15
	6	A4				38		29
	7	31				39		11
	8	0				40		12
	9	1				41		30
	10	19						32
	11	18						X
	12	17		20		51		X
	13	16		21		50		X
	14	23		53		49		X
	15	24		DAC0	48		X
	16	A0		DAC1	47
	17	SDA1	A8		46
	18	SCL1	A9		45
	19	42		A10		44
	20	43		A11
	21	Led		52		9
	22	A3				8
	23	A2				7
	24	A1				6
	25			2		5
	26			22		4
	27			13+Led
	28			Jtag	3
	29			Jtag	10
	30	X		Jtag	Led
	31	X		Jtag	X
*/

/*
		Connexions de la carte Arduino Due :
		------------------------------------
Connexion	Ligne	Connexion	Ligne	Connexion	Ligne
	A0		PA16		SCL1	PA18		14		PD4		
	A1		PA24		SDA1	PA17		15		PD5
	A2		PA23		13		PB27		16		PA13
	A3		PA22		12		PD8			17		PA12
	A4		PA6			11		PD7			18		PA11
	A5		PA4			10		PC29		19		PA10
	A6		PA3			9		PC21		20		PB12
	A7		PA2			8		PC22		21		PB13
	A8		PB17		7		PC23
	A9		PB18		6		PC24
	A10		PB19		5		PC25
	A11		PB20		4		PC26
	DAC0	PB15		3		PC28
	DAC1	PB16		2		PB25
	CANRX	PA1			1		PA9
	CANTX	PA0			0		PA8
	
	Connecteur 36 points :
Connexion	Ligne	Connexion	Ligne
	22		PB26		38		PC6
	23		PA14		39		PC7
	24		PA15		40		PC8
	25		PD0			41		PC9
	26		PD1			42		PA19
	27		PD2			43		PA20
	28		PD3			44		PC19
	29		PD6			45		PC18
	30		PD9			46		PC17
	31		PA7			47		PC16
	32		PD10		48		PC15
	33		PC1			49		PC14
	34		PC2			50		PC13
	35		PC3			51		PC12
	36		PC4			52		PB21
	37		PC5			53		PB14
*/	

/*
Lignes de mesure sur les timers
-------------------------------
	Timer	Ligne	Fonction
	Timer0	PB25	FONCTIONB
	Timer1	PA2		FONCTIONA
	Timer2	PA5		FONCTIONA
	Timer3	PB0		FONCTIONB
	Timer4	PB2		FONCTIONB
	Timer5	PB4		FONCTIONB
	Timer6	PC25	FONCTIONB
	Timer7	PC28	FONCTIONB
	Timer8	PD7		FONCTIONB
*/

/*
Lignes de commande (RàZ) sur les timers
----------------------------------------
	Timer	Ligne	Fonction
	Timer0	PB27	FONCTIONB
	Timer1	PA3		FONCTIONA
	Timer2	PA6		FONCTIONA
	Timer3	PB1		FONCTIONB
	Timer4	PB3		FONCTIONB
	Timer5	PB5		FONCTIONB
	Timer6	PC26	FONCTIONB
	Timer7	PC29	FONCTIONB
	Timer8	PD8		FONCTIONB
*/

/*
Lignes d'entrée du convertisseur A/N
------------------------------------
	Entrée	Ligne	Entrée	Ligne
		0	PA2			8	PB12
		1	PA3			9	PB13
		2	PA4			10	PB17
		3	PA6			11	PB18
		4	PA22		12	PB19
		5	PA23		13	PB20
		6	PA24		14	PB21
		7	PA16		15	Capteur de température
		
Trigger externe du convertisseur A/N = PA11 en FONCTIONB		
*/

/*
Lignes de sortie du convertisseur N/A
	Sortie		Ligne
		0		PB15
		1		PB16
*/

/*
Lignes de sortie des générateurs de signaux
-------------------------------------------
	Générateur		sortie directe	sortie inverse
	GeneSignal0		PA8  FONCTIONB	PA21 FONCTIONB
					PB12 FONCTIONB	PB16 FONCTIONB
					PC3  FONCTIONB	PC2  FONCTIONB
	GeneSignal1		PA19 FONCTIONB	PA12 FONCTIONB
					PB13 FONCTIONB	PB17 FONCTIONB
					PC5  FONCTIONB	PC4	 FONCTIONB
	GeneSignal2		PA13 FONCTIONB	PA20 FONCTIONB
					PB14 FONCTIONB	PB18 FONCTIONB
					PC7  FONCTIONB	PC6  FONCTIONB
	GeneSignal3		PA9  FONCTIONB	PA0  FONCTIONB
					PB15 FONCTIONB	PB19 FONCTIONB
					PC9  FONCTIONB	PC8  FONCTIONB
	GeneSignal4		PC20 FONCTIONB	PC21 FONCTIONB
	GeneSignal5		PC19 FONCTIONB	PC22 FONCTIONB
	GeneSignal6		PC18 FONCTIONB	PC23 FONCTIONB
	GeneSignal7						PC24 FONCTIONB

Pour la sortie inverse le seuil règle la durée du 1 si on choisit la polarité INVERSE	
Pour la sortie directe le seuil règle la durée du 1 si on choisit la polarité DIRECTE
*/

// Type de microcontroleur utilisé
#define SAM3XA (SAM3X4 || SAM3X8 || SAM3A4 || SAM3A8)

// Horloges du SAM3X8E : l'horloge du processeur et des périphériques est de 84MHz
#define FREQ_HORLOGE		(12UL*14UL*1000000UL)
#define FREQ_CPU			CHIP_FREQ_CPU_MAX
#define FREQ_PERIPHS		CHIP_FREQ_CPU_MAX
#define FREQ_HORLOGE_LENTE	CHIP_FREQ_XTAL_32K

// Tension d'alimentation et de réference des convertisseurs
#define TENSION_ALIMENTATION	(3.3F)

// Nombre maximal de fonctions d'IT pouvant être définies
#define NBR_MAX_INTERRUPTIONS	(8)

// Les priorités d'interruption vont de 0 à 15 (__NVIC_PRIO_BITS vaut 4 pour le SAM3X8E)
#define MIN_PRIORITE ( (1 << __NVIC_PRIO_BITS) -1 )
#define MAX_PRIORITE (0)

/***************************************************************/
/* Initialisation des horloges processeur et des périphériques */
/***************************************************************/
void initCarte(void);

/**************************************************/
/* Initialisation du port série pour printf/scanf */
/**************************************************/
void configureConsole(void);

// Noms des périphériques
typedef enum _peripheriques {
	 PortA			= 0,
	 PortB			= 1,
	 PortC			= 2,
	 PortD			= 3,
	 Timer0			= 4,
	 Timer1			= 5,
	 Timer2			= 6,
	 Timer3			= 7,
	 Timer4			= 8,
	 Timer5			= 9,
	 Timer6			= 10,
	 Timer7			= 11,
	 Timer8			= 12,
	 ConvAN			= 13,
	 ConvNA			= 14,
	 GeneSignal0	= 15,
	 GeneSignal1	= 16,
	 GeneSignal2	= 17,
	 GeneSignal3	= 18,
	 GeneSignal4	= 19,
	 GeneSignal5	= 20,
	 GeneSignal6	= 21,
	 GeneSignal7	= 22
} Peripherique;

// Lignes utilisées par la console
#define PORT_CONSOLE	PortA
#define CONSOLE_RX		8
#define CONSOLE_TX		9

// Nombre de périphériques par catégorie
#define NB_PORTS			(4)
#define NB_TIMERS			(9)
#define NB_CANAUX_CAN		(16)
#define NB_GENE_SIGNAUX		(8)

/************************************/
/* Mise en marche d'un périphérique */
/************************************/
void allumerPeriph(Peripherique periph);

/***************************/
/* Arrêt d'un périphérique */
/***************************/
void eteindrePeriph(Peripherique periph);

//			Ports

// Dernier n° de ligne de chacun des ports
#define MAX_LIGNE_PORTA		(29)
#define MAX_LIGNE_PORTB		(31)
#define MAX_LIGNE_PORTC		(30)
#define MAX_LIGNE_PORTD		(10)

// Modes possibles pour les lignes de ports
typedef enum _modeligne {
	 ENTREE		= PIO_INPUT,
	 SORTIE0	= PIO_OUTPUT_0,
	 SORTIE1	= PIO_OUTPUT_1,
	 FONCTIONA	= PIO_PERIPH_A,
	 FONCTIONB	= PIO_PERIPH_B,
} ModeLigne;

// Limites de delai pour le flitrage des lignes (en ms)
#define FILTRE_DELAI_MIN	(1)
#define FILTRE_DELAI_MAX	(250)

// Fronts détectables sur les lignes
typedef enum _fronts {
	 FRONT_MONTANT		= PIO_IT_RISE_EDGE,
	 FRONT_DESCENDANT	= PIO_IT_FALL_EDGE, 
	 FRONT_TOUS			= 0
} Front;

/*************************************************************************************
* Programmation d'une ligne de port
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
* mode = ENTREE ou SORTIE0 ou SORTIE1 ou FONCTIONA ou FONCTIONB
**************************************************************************************/
void programmerLigne(Peripherique port, int ligne, ModeLigne mode);

/*************************************************************************************
* Mise en place du filtrage sur une ligne de port
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
* delai = durée en ms pendant laquelle la ligne est instable (1 à 250)
**************************************************************************************/
void activerFiltrageLigne(Peripherique port, int ligne, uint32_t delai);

/*************************************************************************************
* Suppression du filtrage sur une ligne de port
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
**************************************************************************************/
void desactiverFiltrageLigne(Peripherique port, int ligne);

/*************************************************************************************
* Ecriture dans une ligne de port
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
* valeur = 0 ou 1
**************************************************************************************/
void ecrireLigne(Peripherique port, int ligne, int valeur);

/*************************************************************************************
* Lecture d'une ligne de port 
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
* renvoie 0 ou 1
**************************************************************************************/
int lireLigne(Peripherique port, int ligne);

/*************************************************************************************
* Interdire l'IT sur une ligne de port
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
**************************************************************************************/
void interdireITLigne(Peripherique port, int ligne);

/*************************************************************************************
* Associer une fonction d'IT à la détection d'un front sur une ligne de port
* port = PortA ... PortD
* ligne = 0 à 29 pour PortA, 0 à 31 pour PortB, 0 à 30 pour PortC, 0 à 10 pour PortD
* front = FRONT_MONTANT ou FRONT_DESCENDANT ou FRONT_TOUS
* priorité = priorité de l'IT (0 max à 15 min) 
     ATTENTION la priorité doit être la même pour toutes les lignes d'un même port
* fct = fonction déclenchée par l'IT
**************************************************************************************/
void autoriserITLigne(Peripherique port, int ligne, Front front, int priorite, void (*fct) (void));

//			Timers

// Valeur maximale de limite pour un timer 
#define LIMITE_TIMER_MAX	4294967295ul

// Horloges possibles pour un timer
typedef enum _divisions { 
	 HDIV2		= TC_CMR_TCCLKS_TIMER_CLOCK1,
	 HDIV8		= TC_CMR_TCCLKS_TIMER_CLOCK2,
	 HDIV32		= TC_CMR_TCCLKS_TIMER_CLOCK3,
	 HDIV128	= TC_CMR_TCCLKS_TIMER_CLOCK4, 
	 H_32768	= TC_CMR_TCCLKS_TIMER_CLOCK5
} DivisionTimer;

// Mode répétitif ou pas pour un timer
typedef enum _repetitions { 
	REPETITIF		= 0,
	NON_REPETITIF	= TC_CMR_CPCSTOP
} Repetition;

// Mode incrément ou inc/dec
typedef enum _incdec { 
	INC			= TC_CMR_WAVSEL_UP_RC,
	INC_DEC		= TC_CMR_WAVSEL_UPDOWN_RC
} IncDec;

// Mesures possibles par un timer : période de 0 à 0 ou de 1 à 1 ou durée du 0 ou du 1
typedef enum _mesures_timer {
	DE_0_A_0,
	DE_0_A_1,
	DE_1_A_0,
	DE_1_A_1
} MesureTimer;

// Indicateurs/cause d'IT de timer
typedef enum _it_timers { //
	//	DEBORDEMENT = TC_SR_COVFS,
	LIMITE		= TC_SR_CPCS,
	MESURE		= TC_SR_LDRBS,
	RAZ_EXT		= TC_SR_ETRGS
} IndicateurTimer;

/*******************************************************************************************
* Programmation d'un timer pour générer un délai répétitif ou pas
* timer = Timer0 à Timer 8
* DIV = division de l'horloge CPU (84MHz) = DIV2, DIV8, DIV32, DIV128
      ou utilisation de l'horloge à 32,768KHz = H_32768
* LIM = limite de comptage = 1 à LIMITE_MAX => durée du délai
* repet = REPETITIF ou NON_REPETITIF
* sens = sens de comptage = INC ou INC_DEC
* Le timer produit un événement LIMITE à la fin du délai puis il s'arrête ou pas selon repet
********************************************************************************************/
void timerModeDelai(Peripherique timer, DivisionTimer DIV, uint32_t LIM, Repetition repet, IncDec sens);

/*******************************************************************************************
* Programmation d'un timer en mode mesure
* timer = Timer0 à Timer 8
* DIV = division de l'horloge CPU (84MHz) = DIV2, DIV8, DIV32, DIV128
      ou utilisation de l'horloge à 32,768KHz = H_32768
* LIM = limite de comptage = 1 à LIMITE_MAX permet de définir une limite maximum à la mesure
* mesure = DE_0_A_0, DE_0_A_1, DE_1_A_0 ou DE_1_A_1 pour mesurer le temps entre :
*  - deux passages à 0 successifs (période)
*  - un passage à 0 suivi d'un passage à 1 (durée du 0)
*  - un passage à 1 suivi d'un passage à 0 (durée du 1)
*  - deux passages à 1 successifs (période)
* Le timer s'arrête à la fin de la mesure et produit l'événement CAPTURE
* Le timer repart de 0 lorsqu'il atteint 4294967295
* Les lignes de capture sont dans l'ordre : PB15, PA2, PA5, PB0, PB2, PB4, PC25, PC28, PD7
* Elles doivent être programmées en FONCTIONB sauf PA2 et PA5 qui doivent être en FONCTIONA	  
*******************************************************************************************/
void timerModeMesure(Peripherique timer, DivisionTimer DIV, uint32_t LIM, MesureTimer mesure);

/************************************************************************
* Programmation d'un timer pour déclenchement du conv A/N
* timer = Timer0 à Timer 3
* DIV = division de l'horloge CPU (84MHz) = DIV2, DIV8, DIV32, DIV128
      ou utilisation de l'horloge à 32,768KHz = H_32768
* LIM = limite de comptage = 1 à LIMITE_MAX => durée du délai
* repet = REPETITIF ou NON_REPETITIF
*************************************************************************/
void timerModeDeclenchement(Peripherique timer, DivisionTimer DIV, uint32_t LIM, Repetition repet);

/******************************************************************************************
* Activer la RàZ et le redémarrage d'un timer par ligne externe
* timer = Timer0 à Timer 8
* front = FRONT_MONTANT ou FRONT_DESCENDANT ou FRONT_TOUS
* Les lignes de RàZ sont dans l'ordre : PB27, PA3, PA6, PB1, PB3, PB5, PC26, PC29, PD9
* Elles doivent être programmées en FONCTIONB sauf PA3 et PA6 qui doivent être en FONCTIONA
*******************************************************************************************/
void activerRazExterne(Peripherique timer, Front front);

/************************************************************************
* Desactiver la RàZ et le redémarrage d'un timer par ligne externe
* timer = Timer0 à Timer 8
*************************************************************************/
void desactiverRazExterne(Peripherique timer);

/****************************
* Démarage d'un timer
* timer = Timer0 à Timer 8
****************************/
void lancerTimer(Peripherique timer);

/***************************
* Arrêt d'un timer
* timer = Timer0 à Timer 8
***************************/
void arreterTimer(Peripherique timer);

/********************************
* Lecture du compteur d'un timer
* timer = Timer0 à Timer 8
*  renvoie la valeur du compteur
*********************************/
uint32_t lireTimer(Peripherique timer);

/**************************************************
* Lecture de la mesure de temps faite par un timer
* timer = Timer0 à Timer 8
*  renvoie la valeur capturée par le timer
***************************************************/
uint32_t lireMesureTimer(Peripherique timer);

/*****************************************
* Lecture de la valeur limite d'un timer
* timer = Timer0 à Timer 8
*  renvoie la valeur limite du timer
******************************************/
uint32_t lireLimiteTimer(Peripherique timer);

/*********************************************
* Modification de la valeur limite d'un timer
* timer = Timer0 à Timer 8
*  valeur = nouvelle limite du timer
**********************************************/
void modifierLimiteTimer(Peripherique timer, uint32_t valeur);

/**********************************************************
* renvoie la fréquence d'horloge actuelle d'un timer en Hz)
* timer = Timer0 à Timer 8
***********************************************************/
uint32_t frequenceTimer(Peripherique timer);

/********************************************************
* Test d'un indicateur d'état de timer
* timer = Timer0 à Timer 8
*  cause = 	LIMITE ou MESURE ou RAZ_EXT 
*  renvoie true si l'événement a été détecté false sinon
*********************************************************/
bool testerEtatTimer(Peripherique timer, IndicateurTimer etat);

/***********************************************
* Interdire la génération d'une IT par un timer
* timer = Timer0 à Timer 8
*  cause = 	LIMITE ou MESURE ou RAZ_EXT 
************************************************/
void interdireITTimer(Peripherique timer, IndicateurTimer cause);

/***********************************************************************
* Associer une fonction d'IT à la détection d'un événement par un timer
* timer = Timer0 à Timer 8
*  cause = 	LIMITE ou MESURE ou RAZ_EXT
* priorité = priorité de l'IT (0 max à 15 min)
* fct = fonction déclenchée par l'IT
************************************************************************/
void autoriserITTimer(Peripherique timer, IndicateurTimer cause, int priorite, void (*fct) (void));

//					Convertisseur AN

// Temps de conversion minimal et maximal (en micro secondes) pour le convertisseur A/N
#define DELAI_MIN_CONVAN	(3)
#define DELAI_MAX_CONVAN	(100)

// Résolutions du conv AN
typedef enum _resolutions { 
	RES10BITS		= ADC_MR_LOWRES_BITS_10,
	RES12BITS		= ADC_MR_LOWRES_BITS_12 
} Resolution;

// Déclenchements possibles du conv AN
typedef enum _declenchements { 
	PROG			= ADC_TRIG_SW,
	PROG_CONTINU	= 9999, 
//	EXT				= ADC_TRIG_EXT, 
	TIMER0			= ADC_TRIG_TIO_CH_0,
	TIMER1			= ADC_TRIG_TIO_CH_1,
	TIMER2			= ADC_TRIG_TIO_CH_2
} Declenchement;

// Gains appliquables en entrée
typedef enum _gains_entrees {
	G_1		= 1,
	G_2		= 2,
	G_4		= 3
} GainEntree;

// Comparaison de seuils du conv AN
typedef enum _modes_seuils { 
	INF			= ADC_EMR_CMPMODE_LOW,
	SUP			= ADC_EMR_CMPMODE_HIGH,
	DANS		= ADC_EMR_CMPMODE_IN,
	HORS		= ADC_EMR_CMPMODE_OUT
} ModeSeuil;

// Indicateurs/cause d'IT du conv AN
typedef enum _it_can { 
	FIN_CONV0		= ADC_ISR_EOC0,
	FIN_CONV1		= ADC_ISR_EOC1,
	FIN_CONV2		= ADC_ISR_EOC2,
	FIN_CONV3		= ADC_ISR_EOC3,
	FIN_CONV4		= ADC_ISR_EOC4,
	FIN_CONV5		= ADC_ISR_EOC5,
	FIN_CONV6		= ADC_ISR_EOC6,
	FIN_CONV7		= ADC_ISR_EOC7,
	FIN_CONV8		= ADC_ISR_EOC8,
	FIN_CONV9		= ADC_ISR_EOC9,
	FIN_CONV10		= ADC_ISR_EOC10,
	FIN_CONV11		= ADC_ISR_EOC11,
	FIN_CONV12		= ADC_ISR_EOC12,
	FIN_CONV13		= ADC_ISR_EOC13,
	FIN_CONV14		= ADC_ISR_EOC14,
	FIN_CONVTEMP	= ADC_ISR_EOC15,
	SEUILS			= ADC_ISR_COMPE,
	FIN_SEQUENCE	= ADC_ISR_ENDRX
} IndicateurCAN;

// Entrée correspondant au capteur de température
#define CAPT_TEMP	(15)

// Longueur maximale de séquence d'entrée
#define LG_MAX_SEQUENCE	(15)

// Nombre maximum de comparaisons de seuil pour déclencher un événement
#define CPM_FILTRE_MAX	(4)

/*************************************************
* Initialisation du convertisseur AN
* duree = vitesse de conversion = 3 à 100 (micros)
* resolution = RES10BITS ou RES12BITS
**************************************************/
void initConvAN(int duree, Resolution resolution);

/***************************************************
* Mode de déclenchement du convertisseur AN
*  decl = 	PROG ou PROG_CONTINU ou TIMER0 à TIMER3
****************************************************/
void declenchementConvAN(Declenchement decl);

/***************************************************************************************************************
* Choix de l'entrée du convertisseur AN (c'est la seule utilisée)
* num = n° d'entrée = 0 à 15 (15 est relié au capteur de température)
* Les lignes d'entrée sont dans l'ordre : 
*	PA2, PA3, PA4, PA6, PA22, PA23, PA24, PA16, PB12, PB13, PB17, PB18, PB19, PB20, PB21, Capteur de température
****************************************************************************************************************/
void choisirEntreeConvAN(int num);

/***************************************************************************************************************
* désactivation d'une entrée du convertisseur AN 
* num = n° d'entrée = 0 à 15 (15 est relié au capteur de température)
* Les lignes d'entrée sont dans l'ordre :
*	PA2, PA3, PA4, PA6, PA22, PA23, PA24, PA16, PB12, PB13, PB17, PB18, PB19, PB20, PB21, Capteur de température
****************************************************************************************************************/
void desactiverEntreeConvAN(int num);

/***************************************************************************************************************
* Définition d'une suite d'entrées du convertisseur AN à mesurer
* nombre = nombre d'entrées de la liste (entre 1 et 15)
* Les paramètres qui suivent sont les n°s des entrées du convertisseur à mesurer dans cet ordre
* ATTENTION seules les entrées 0 à 14 peuvent apparaître (la capteur de température ne peut pas être utilisé)
****************************************************************************************************************/
void listeEntreesConvAN(int lgliste, ...);

/**********************************************************
* Choix d'un gain appliqué à l'entrée du convertisseur AN 
* num = n° d'entrée = 0 à 14
* gain = G_1 ou G_2 ou G_4 pour un gain de 1 , 2 ou 4
***********************************************************/
void amplificationEntreeConvAN(int num, GainEntree gain);

/************************************************************************
* Lancement d'une conversion AN si on est en déclenchement PROG
*************************************************************************/
void lancerConversionAN(void);

/************************************************************************
* Récupération de la valeur convertie sur une entrée 
* num = n° d'entrée = 0 à 15 (15 est relié au capteur de température)
*************************************************************************/
uint32_t lireValeurConvAN(int num);

/************************************************************************
* Récupération de la température en degrés sur le capteur de température
*************************************************************************/
float lireTemperature(void);

/******************************************************************************
* Récupération de la valeur convertie sur une entrée en Volts
* Tient compte de la résolution (10 ou 12 bits) et du gain éventuel (1, 2 ou 4)
* num = n° d'entrée = 0 à 15 (15 est relié au capteur de température)
*******************************************************************************/
float lireTensionConvAN(int num);

/*****************************************************************
* Récupération d'une liste de valeurs converties
* table = tableau de uint16_t recevant la liste des mesures 
*  (sa taille doit être au moins égale à la longueur de la liste)
*****************************************************************/
int lireListeValeursConverties(uint16_t * table);

/*******************************************************************************
* Récupération d'une liste de valeurs converties en volts
* Tient compte de la résolution (10 ou 12 bits) et du gain éventuel (1, 2 ou 4)
* table = tableau de float recevant la liste des mesures 
*  (sa taille doit être au moins égale à la longueur de la liste)
********************************************************************************/
int lireListeTensionsConverties(float * table);

/*********************************************************************************
* Mise en place de la comparaison de seuils sur une entrée du convertisseur A/N
* num = n° d'entrée = 0 à 15 (15 est relié au capteur de température)
* mode = type de comparaison = 	INF ou SUP ou DANS ou HORS
* nombre = nombre de comparaisons réussies pour positionner l'indicateur (1 à 4)
* bas = seuil bas
* haut = seuil haut
**********************************************************************************/
void activerSeuilsConvAN(int num, ModeSeuil mode, int nombre, uint32_t bas, uint32_t haut);

/***************************************************************************
* Test d'événement du convertisseur A/N
*  cause = 	FIN_CONV0 à FIN_CONV14 ou FIN_CONVTEMP ou SEUILS ou FIN_SEQUENCE 
*  renvoie true si l'événement s'est produit false sinon
****************************************************************************/
bool testerEtatConvAN(IndicateurCAN cause);

/**********************************************************************************
* Interdire la génération d'une IT de fin de conversion par le convertisseur A/N
*  cause = FIN_CONV0 à FIN_CONV14 ou FIN_CONVTEMP ou SEUILS ou FIN_SEQUENCE
***********************************************************************************/
void interdireITConvAN(IndicateurCAN cause);

/***************************************************************************
* Associer une fonction d'IT à la fin de conversion sur une ligne
*  cause = FIN_CONV0 à FIN_CONV14 ou FIN_CONVTEMP ou SEUILS ou FIN_SEQUENCE
* priorité = priorité de l'IT (0 max à 15 min)
* fct = fonction déclenchée par l'IT
****************************************************************************/
void autoriserITConvAN(IndicateurCAN cause, int priorite, void (*fct) (void));

//					Convertisseur NA

// Valeurs min et max de tension en sortie du convertisseur NA
#define TENSION_MIN_CONVNA	(TENSION_ALIMENTATION / 6)
#define TENSION_MAX_CONVNA	(TENSION_ALIMENTATION * 5/6)

/************************************
* Initialisation du convertisseur NA
*************************************/
void initConvNA(void);

/*****************************************************
* Activation d'une sortie du convertisseur NA
* num = 0 ou 1
* Les lignes de sortie sont dans l'ordre : PB15, PB16
******************************************************/
void activerSortieConvNA(int num);

/***************************************************
* Desactivation d'une sortie du convertisseur NA
* num = 0 ou 1
****************************************************/
void desactiverSortieConvNA(int num);

/***************************************************
* Ecriture de la valeur à convertir dans une sortie
* valeur = 0 à 4095
* num = 0 ou 1
****************************************************/
void ecrireValeurConvNA(uint16_t valeur, int num);

/****************************************************
* Ecriture d'une tension à convertir dans une sortie
* tension = 0 à 3,3
* num = 0 ou 1
*****************************************************/
void ecrireTensionConvNA(float tension, int num);

/*****************************************************************
* Test de la fin de conversion sur une ligne du convertisseur N/A
*  renvoie true si la conversion est terminée false sinon
******************************************************************/
bool testerEtatConvNA(void);

//					Générateurs de signaux

// Fréquences minimale et maximale programmables pour les horloges A et B (322Hz à 3MHz)
#define FREQ_MIN_HAB	(322UL)
#define FREQ_MAX_HAB	(3000000UL)

// Horloges applicables à un générateur de signal
typedef enum _divisions_pwm {
	DIV1		= PWM_CMR_CPRE_MCK,
	DIV2		= PWM_CMR_CPRE_MCK_DIV_2,
	DIV4		= PWM_CMR_CPRE_MCK_DIV_4,
	DIV8		= PWM_CMR_CPRE_MCK_DIV_8,
	DIV16		= PWM_CMR_CPRE_MCK_DIV_16,
	DIV32		= PWM_CMR_CPRE_MCK_DIV_32,
	DIV64		= PWM_CMR_CPRE_MCK_DIV_64,
	DIV128		= PWM_CMR_CPRE_MCK_DIV_128,
	DIV256		= PWM_CMR_CPRE_MCK_DIV_256,
	DIV512		= PWM_CMR_CPRE_MCK_DIV_512,
	DIV1024		= PWM_CMR_CPRE_MCK_DIV_1024,
	HORLOGEA	= PWM_CMR_CPRE_CLKA,
	HORLOGEB	= PWM_CMR_CPRE_CLKB
} DivisionGeneSignal;

// Polarités des lignes de sortie
typedef enum _polarite_pwm {
	DIRECTE		= 0,
	INVERSE		= 1
} PolariteGeneSignal;

/*************************************************************************************************
* Initialisation d'un générateur de signal
* pwm = GeneSignal 0 à 7
* DIV = DIV1, DIV2, DIV4, DIV8, DIV16, DIV32, DIV64, DIV128, DIV256, DIV1024, HORLOGEA ou HORLOGEB
* periode = 0 à 65535
* seuil = 0 à 65535
* polarite = DIRECTE ou INVERSE
* Pour que le seuil règle la durée du 1 mettre :
*   INVERSE si on utilise une sortie inverse et DIRECTE si on utilise sortie directe
* Les lignes de sortie inverse doivent être programmées en FONCTIONB ce sont :
*	Générateur0 : PA21 ou PB16 ou PC2
*	Générateur1 : PA12 ou PB17 ou PC4
*	Générateur2 : PA20 ou PB18 ou PC6
*	Générateur3 : PA0 ou PB19 ou PC8
*	Générateur4 : PC21
*	Générateur5 : PC22
*	Générateur6 : PC23
*	Générateur7 : PC24
* Les lignes de sortie directe doivent être programmées en FONCTIONB ce sont :
*	Générateur0 : PA8 ou PB12 ou PC3
*	Générateur1 : PA19 ou PB13 ou PC5
*	Générateur2 : PA13 ou PB14 ou PC7
*	Générateur3 : PA9 ou PB15 ou PC9
*	Générateur4 : PC20
*	Générateur5 : PC19
*	Générateur6 : PC18
*	Générateur7 : aucune
***************************************************************************************************/
void initGeneSignal(Peripherique pwm, DivisionGeneSignal DIV, uint16_t periode, uint16_t seuil, PolariteGeneSignal polarite);

/************************************************************************
* Definir la fréquence de l'horloge A utilisable par tous les générateurs
* frequence = fréquence de l'horloge A (322 à 3 000 000 Hz)
*************************************************************************/
void definirHorlogeA(uint32_t frequence);

/************************************************************************
* Definir la fréquence de l'horloge B utilisable par tous les générateurs
* frequence = fréquence de l'horloge B (322 à 3 000 000 Hz)
*************************************************************************/
void definirHorlogeB(uint32_t frequence);

/************************************************************************
* Modification de la période d'un générateur de signal
* pwm = GeneSignal 0 à 7
* periode = 0 à 65535
*************************************************************************/
void modifierPeriodeGeneSignal(Peripherique pwm, uint16_t periode);

/*************************************************************************************************************
* Modification du seuil d'un générateur de signal (durée du 1 ou du 0 selon la polarité et la ligne de sortie)
* pwm = GeneSignal 0 à 7
* seuil = 0 à 65535
**************************************************************************************************************/
void modifierSeuilGeneSignal(Peripherique pwm, uint16_t seuil);

/**************************************************************************
* Renvoie la fréquence d'horloge actuelle d'un générateur de signal (en Hz)
* pwm = GeneSignal 0 à 7
***************************************************************************/
uint32_t freqGeneSignal(Peripherique pwm);

/*************************************************************************
* Renvoie la période actuelle d'un générateur de signal 
* pwm = GeneSignal 0 à 7
**************************************************************************/
uint32_t periodeGeneSignal(Peripherique pwm);

/*************************************************************************
* Renvoie le seuil actuel d'un générateur de signal 
* pwm = GeneSignal 0 à 7
**************************************************************************/
uint32_t seuilGeneSignal(Peripherique pwm);

/************************************************************************
* Tester l'indicateur de fin de période d'un générateur de signal
* pwm = GeneSignal 0 à 7
*  renvoie true si le PWM a atteint la fin de période false sinon
*************************************************************************/
bool testerEtatGeneSignal(Peripherique pwm);

/*********************************************************************
* Interdire l'IT associée à la fin de période un générateur de signal
* pwm = GeneSignal 0 à 7
**********************************************************************/
void interdireITGeneSignal(Peripherique pwm);

/*************************************************************************************
* Associer une fonction d'IT à l'événement de fin de période d'un générateur de signal
* priorité = priorité de l'IT (0 max à 15 min)
* fct = fonction déclenchée par l'IT
**************************************************************************************/
void autoriserITGeneSignal(Peripherique pwm, int priorite, void (*fct) (void));

#endif