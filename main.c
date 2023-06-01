#include <stdio.h>
#include <stdlib.h>
#include "bateaux.h"
#include "bateaux.c"


int main() {
	Bateau port[] = {
		{.nom = "voilier1", .categorie = VOILIER, .specificites.voilier
		.surfaceVoilure = 300},
		{.nom = "peche1", .categorie = MOTEUR,
		 .specificites.moteur.sousCategorie = PECHE,
		 .specificites.moteur.puissance = 100,
		 .specificites.moteur.sousSpecificites.peche.tonnePoisson = 10},
		{.nom = "plaisance1", .categorie = MOTEUR,
		 .specificites.moteur.sousCategorie = PLAISANCE,
		 .specificites.moteur.puissance = 200,
		.specificites.moteur.sousSpecificites.plaisance.longueur = 100,
		.specificites.moteur.sousSpecificites.plaisance.nomProprietaire = "Mr.Navire"},
		{.nom = "voilier2", .categorie = VOILIER,
		 .specificites.voilier.surfaceVoilure = 100},
		{.nom = "plaisance2", .categorie = MOTEUR,
			.specificites.moteur.sousCategorie = PLAISANCE,
			.specificites.moteur.puissance = 90,
			.specificites.moteur.sousSpecificites.plaisance.longueur = 70,
			.specificites.moteur.sousSpecificites.plaisance.nomProprietaire = "Mr"
																									".Cargo"},
		{.nom = "peche2", .categorie = MOTEUR,
			.specificites.moteur.sousCategorie = PECHE,
			.specificites.moteur.puissance = 500,
			.specificites.moteur.sousSpecificites.peche.tonnePoisson = 350},
	};

	//calculer toutes les taxes annuelles
	for(int i = 0; i < sizeof(port)/sizeof(*port); ++i){
		calculTaxe(port + i);
	}

	//trier par taxe annuelle
	qsort(port,sizeof(port)/sizeof(*port),sizeof(*port),comparerTaxes);

	//imprimer les bateaux et caracteristiques
	for(int i = 0; i < sizeof(port)/sizeof(*port); ++i){
		afficherBateau(port[i]);
	}

	//imprimer somme mediane moyenne et ecart-type
	printf("\nVOILIERS:\n");
	afficherParType(port, sizeof(port)/sizeof(*port), VOILIER, AUCUN);
	printf("PECHE:\n");
	afficherParType(port, sizeof(port)/sizeof(*port), MOTEUR, PECHE);
	printf("PLAISANCE:\n");
	afficherParType(port, sizeof(port)/sizeof(*port), MOTEUR, PLAISANCE);

	return 0;
}
