#include <stdio.h>
#include <stdlib.h>
#include "bateaux.h"
#include "bateaux.c"

//comparaison par taxe annuelle
int comparerTaxes(const Bateau* el1, const Bateau el2){
	int t1 = el1->taxeAnuelle.taxeAnnuelle;
	int t2 = el2.taxeAnuelle.taxeAnnuelle;
	if (t1 < t2) return 1;
	if (t1 > t2) return -1; //inversés pour être décroissant
	return 0;
};

void afficherBateau(Bateau b){
	switch (b.categorie) {
		case VOILIER:
			printf("nom: %s - taxe annuelle: %d - voilure: %d\n", b.nom, b
				.taxeAnuelle.taxeAnnuelle, b.specificites.voilier
						 .surfaceVoilure);
			break;
		case MOTEUR:
			printf("nom: %s - taxe annuelle: %d - puissance: %d - ", b.nom,
					 b.taxeAnuelle.taxeAnnuelle,
					 b.specificites.moteur.puissance);
			switch(b.specificites.moteur.sousCategorie){
				case PECHE:
					printf("tonne poisson: %d\n", b
						.specificites.moteur.sousSpecificites.peche.tonnePoisson);
					break;
				case PLAISANCE:
					printf("longueur: %d - proprietaire: %s\n", b.specificites
						.moteur.sousSpecificites.plaisance.longueur, b
								 .specificites.moteur.sousSpecificites.plaisance.nomProprietaire);
					break;
				default:
					printf("\n");
					break;
			}
			break;
		default:
			printf("nom: %s\n", b.nom);
			break;
	}
}

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
			.specificites.moteur.sousSpecificites.plaisance.nomProprietaire = "Mr.Cargo"}
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

	return 0;
}
