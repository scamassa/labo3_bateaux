#ifndef LABO3_BATEAUX_BATEAUX_H
#define LABO3_BATEAUX_BATEAUX_H

#include <stdint.h>

typedef char *Nom;
//typedef enum {VOILIER, PECHE, PLAISANCE} type;

struct Plaisance{
	uint8_t longueurBateau;
	Nom nomProprietaire;
};

union PecheOuPlaisance {
	uint8_t tonnePoisson;
	struct Plaisance plaisance;
};

struct Moteur{
	uint16_t puissanceMoteur;
	union PecheOuPlaisance pecheOuPlaisance;
};

union VoilierOuMoteur {
	uint16_t surfaceVoilure;
	struct Moteur moteur;
};

struct bateau {
	Nom nom;
	union VoilierOuMoteur voilierOuMoteur;
};

struct bateau B1 = {.nom = "test", .voilierOuMoteur.moteur.puissanceMoteur = 2,
	.voilierOuMoteur.moteur.pecheOuPlaisance.tonnePoisson = 5}; //c'est trop moche
	// on va changer

#endif //LABO3_BATEAUX_BATEAUX_H
