#include "bateaux.h"
#include <stdio.h>
#include <math.h>

void calculTaxe(Bateau *b) {
   int taxeBase = 0, taxeSpecifique = 0;
   if (b->categorie == VOILIER) {
      taxeBase = 50;
      if (b->specificites.voilier.surfaceVoilure >= 200) {
         taxeSpecifique = 25;
      }
   } else if (b->categorie == MOTEUR) {
      taxeBase = 100;
      if (b->specificites.moteur.sousCategorie == PECHE &&
          b->specificites.moteur.sousSpecificites.peche.tonnePoisson >= 20) {
         taxeSpecifique = 100;
      } else if (b->specificites.moteur.sousCategorie == PLAISANCE) {
         if (b->specificites.moteur.puissance < 100) {
            taxeSpecifique = 50;
         } else {
            taxeSpecifique = 15 * b->specificites.moteur.sousSpecificites
                .plaisance.longueur;
         }
      }
   } else {
      printf("\nCategorie de bateau non connue\n");
      return;
   }
   b->taxeAnuelle.taxeBase = taxeBase;
   b->taxeAnuelle.taxeSpecifique = taxeSpecifique;
   b->taxeAnuelle.taxeAnnuelle = taxeBase + taxeSpecifique;
}

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