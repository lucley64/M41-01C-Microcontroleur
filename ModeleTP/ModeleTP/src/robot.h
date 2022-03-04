/*
 * robot.h
 *
 * Created: 03/07/2016 10:50:16
 *  Author: Dalmau
 */ 

/*****************************************************************
				Pilotage du robot :
******************************************************************
Base =    ligne 5  du port C (connection Arduino 37), GeneSignal 1
Epaule =  ligne 7  du port A (connection Arduino 39), GeneSignal 2
Coude =   ligne 9  du port C (connection Arduino 41), GeneSignal 3
Poignet = ligne 19 du port C (connection Arduino 44), GeneSignal 5
Pince =   ligne 18 du port C (connection Arduino 45), GeneSignal 6
******************************************************************/

#include "libTPIUT.h"

#ifndef ROBOT_H_
#define ROBOT_H_

// Tension sur VIN quand la carte est alimentée par l'alim externe
#define TENSION_MOTEURS 7.0

// Articulations du robot
#define NB_MOTEURS 5
#define BASE	0
#define EPAULE	1
#define COUDE	2
#define POIGNET 3
#define PINCE	4

// Pilotes des moteurs du robot : Générateurs
#define PILOTE_BASE		GeneSignal1
#define PILOTE_EPAULE	GeneSignal2
#define PILOTE_COUDE	GeneSignal3
#define PILOTE_POIGNET	GeneSignal5
#define PILOTE_PINCE	GeneSignal6
// Pilotes des moteurs du robot : ports des lignes de sortie du signal
#define PORT_BASE		PortC
#define PORT_EPAULE		PortC
#define PORT_COUDE		PortC
#define PORT_POIGNET	PortC
#define PORT_PINCE		PortC
// Pilotes des moteurs du robot : lignes de sortie du signal
#define LIGNE_BASE		5
#define LIGNE_EPAULE	7
#define LIGNE_COUDE		9
#define LIGNE_POIGNET	19
#define LIGNE_PINCE		18

// Init des 5 moteurs en position initiale
void initRobot(void); 

// Positionnement d'un moteur désigné par son nom (BASE, EPAULE, COUDE, POIGNET ou PINCE) 
// à un angle donné en degrés
// La valeur de retour est false si les paramètres sont incorrects
bool positionnerMoteur(int moteur, float angle); 

#endif /* ROBOT_H_ */