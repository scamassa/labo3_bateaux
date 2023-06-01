#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int comparerDouble(const double el1, const double el2){
	if (el1 < el2) return -1;
	if (el1 > el2) return 1;
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

void afficherParType(Bateau port[], int size, Categorie cat, SousCategorie sousCat){
	int compteurBateaux = 0;
	double somme = 0, moyenne = 0, mediane = 0, ecartType = 0;
	double taxes[10];
	for(int i = 0; i < size; ++i){
		if(port[i].categorie == cat && port[i].specificites.moteur.sousCategorie ==
			sousCat){
			taxes[compteurBateaux] = port[i].taxeAnuelle.taxeAnnuelle;
			//somme
			somme += port[i].taxeAnuelle.taxeAnnuelle;
			compteurBateaux++;
		}
	}

	//moyenne
	moyenne = somme/compteurBateaux;

	int taille = sizeof(taxes)/sizeof(double);

	//ecart-type
	for (int i = 0; i < taille; ++i) {
		ecartType += pow(taxes[i] - moyenne, 2.0);
	}
	ecartType = ecartType / (taille - 1);
	ecartType = sqrt(ecartType/taille);

	//mediane
	qsort(taxes, taille, sizeof(double), comparerDouble);
	mediane = (taille % 2) == 0 ? taxes[taille/2] : (taxes[taille/2 - 1] +
		taxes[taille/2])/2;

	printf("somme: %.1f - moyenne: %.1f - mediane: %.1f - ecart-type: %f\n", somme,
			 moyenne, mediane, ecartType);
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
