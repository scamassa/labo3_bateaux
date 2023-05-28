#include "bateaux.h"

void CalculTaxe(Bateau *b) {
	int taxeBase = 0, taxeSpecifique = 0;
	if (b->categorie == VOILIER) {
		taxeBase = 50;
		if (b->specificites.voilier.surfaceVoilure >= 200) {
			taxeSpecifique = 25;
		}
	}
	else if (b->categorie == MOTEUR) {
		taxeBase = 100;
		if (b->specificites.moteur.sousCategorie == PECHE) {
			if (b->specificites.moteur.sousSpecificites.peche.tonnePoisson >= 20) {
				taxeSpecifique = 100;
			}
		} else if (b->specificites.moteur.sousCategorie == PLAISANCE) {
			if (b->specificites.moteur.puissance < 100) {
				taxeSpecifique = 50;
			}
			else {
				taxeSpecifique = 15 * b->specificites.moteur.sousSpecificites.plaisance.longueur;
			}
		}
	}
	b->taxeAnuelle.taxeBase = taxeBase;
	b->taxeAnuelle.taxeSpecifique = taxeSpecifique;
	b->taxeAnuelle.taxeAnnuelle = taxeBase + taxeSpecifique;
}