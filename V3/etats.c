#include <string.h>
#include <stdlib.h>
#include "yystype.h"
#include "etats.h"

/* Affichage de la table des etats */
void afficherTable (tabEtats t){
  int i,j;
  
  printf("\n\nAffichage des etats\n");
  
  /* Parcours des etats */
  for (i=0;i<t.nbEtats;i++) {
      printf("\n   Etat %s", t.vecEtats[i].nomEtat);
      if (t.vecEtats[i].etatInitial) printf("\n      Etat initial");
      if (t.vecEtats[i].etatFinal) printf("\n      Etat final");
      
      /* Parcours des arcs */
      if (t.vecEtats[i].nbArcs > 0) {
          printf("\n      Affichage des arcs");
          for (j=0;j<t.vecEtats[i].nbArcs;j++)
              printf("\n         Arc : Etiquette %s - Etat d arrivee %s",t.vecEtats[i].vecArcs[j].nomEtiquette,t.vecEtats[i].vecArcs[j].nomEtatArrivee);
      }
      else printf("\n      Aucun arc");
      printf("\n");
  }
}


/* Initialisation de la table des etats */
void initTable (tabEtats *t) {
    t->nbEtats = 0; /* Initialisation a 0 du nombre d etats */
}


/* Recherche de l etat de nom s dans le tableau des etats          */
/* Retourne l indice de la case du tableau contenant s s il existe */
/* sinon retourne -1                                               */
int chercherEtat(tabEtats t, char *s) {
  int i = 0;
  int trouve = -1;
  
  /* Recherche du nom s */
  while ((i < t.nbEtats) && (trouve == -1)) {
    if (strcmp(s, t.vecEtats[i].nomEtat)==0) trouve = i;
    else i++;
  }
  
  return trouve;
}


/* Ajout de l etat de nom s dans le tableau des etats s il n existe pas            */
/* Si l etat est deja present dans le tableau, declenchement d une erreur          */
/* S il n y a plus de places dans le tableau des etats, declenchement d une erreur */
void insererEtat (tabEtats *t, char *s) { 
  if (chercherEtat(*t, s) == -1) {
    if (t->nbEtats==MAX_ETATS)
      yyerror("Nombre max d'états atteint") ;
    else { /* Ajout de l etat de nom s */
           strcpy(t->vecEtats[t->nbEtats].nomEtat, s);
           t->vecEtats[t->nbEtats].etatInitial = FAUX;
           t->vecEtats[t->nbEtats].etatFinal = FAUX;
           t->vecEtats[t->nbEtats].nbArcs = 0;
           t->nbEtats++;
    }
  }
  else yyerror("Cet état existe déjà");
}


/* Mise a jour du champ etatInitial pour l etat de nom s       */
/* Si l etat de nom s n existe pas, declenchement d une erreur */
void definirEtatInitial (tabEtats *t, char *s) { 
  /* Recherche de l indice de l etat de nom s dans le tableau des etats */
  int indEtat = chercherEtat(*t, s); 
  
  if (indEtat == -1)
    yyerror("Etat initial non defini") ;
  else t->vecEtats[indEtat].etatInitial = VRAI;
}


/* Mise a jour du champ etatFinal pour l etat de nom s */
void definirEtatFinal (tabEtats *t, char *s) { 
  t->vecEtats[chercherEtat(*t, s)].etatFinal = VRAI;
}


/* Recherche de l arc d etat d arrivee de nom s et d etiquette de nom e */
/* Retourne l indice de la case du vecteur contenant l arc s il existe  */
/* sinon retourne -1                                                    */
int chercherArc(etatInfos s, char *d, char *e) {
  int i = 0;
  int trouve = -1;
  
  /* Parcours des arcs */
  while ((i < s.nbArcs) && (trouve == -1)) {
    if ((strcmp(d, s.vecArcs[i].nomEtatArrivee)==0) && (strcmp(e, s.vecArcs[i].nomEtiquette)==0)) trouve = i;
    else i++;
  }
  
  return trouve;
}


/* Ajout de l arc s -> d d etiquette e dans le tableau des etats s il n existe pas */
/* Si l arc est deja present dans le tableau, declenchement d une erreur           */
/* S il n y a pas de places dans le vecteur des arcs, declenchement d une erreur   */
void insererArc (tabEtats *t, char *s, char *d, char *e) {
  /* Recherche de l indice de l etat de nom s dans le tableau des etats */
  int indEtat = chercherEtat(*t, s);



 
  
  if (chercherArc(t->vecEtats[indEtat], d, e) == -1) {
    if (t->vecEtats[indEtat].nbArcs==MAX_ARCS)
        yyerror("Nombre max d'arcs atteint") ;
    else { /* Ajout de l arc */
           strcpy(t->vecEtats[indEtat].vecArcs[t->vecEtats[indEtat].nbArcs].nomEtatArrivee, d);
           strcpy(t->vecEtats[indEtat].vecArcs[t->vecEtats[indEtat].nbArcs].nomEtiquette, e);
           t->vecEtats[indEtat].nbArcs++;
    }
  }
  else yyerror("Cet arc existe déjà") ;  
}
