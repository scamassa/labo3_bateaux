#ifndef LABO3_BATEAUX_BATEAUX_H
#define LABO3_BATEAUX_BATEAUX_H

#include <stdint.h>

typedef char *Nom;

typedef enum {
	VOILIER, MOTEUR
} Categorie;

typedef enum {
	PECHE, PLAISANCE
} SousCategorie;

struct TaxeAnuelle {
	int taxeBase;
	int taxeSpecifique;
	int taxeAnnuelle;
};

typedef struct {
	uint16_t surfaceVoilure;
} Voilier;

typedef struct {
	uint8_t tonnePoisson;
} Peche;

typedef struct {
	uint8_t longueur;
	Nom nomProprietaire;
} Plaisance;

typedef union {
	Peche peche;
	Plaisance plaisance;
} SousSpecificites;

typedef struct {
	uint16_t puissance;
	SousSpecificites sousSpecificites;
	SousCategorie sousCategorie;
} Moteur;

typedef union {
	Voilier voilier;
	Moteur moteur;
} Specificites;

typedef struct {
	Nom nom;
	struct TaxeAnuelle taxeAnuelle;
	Specificites specificites;
	Categorie categorie;
} Bateau;

void calculTaxe(Bateau *b);

#endif //LABO3_BATEAUX_BATEAUX_H
