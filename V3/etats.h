/* Definition constantes */
#define MAX_ETATS 500     /* Nombre maximum d etats */
#define MAX_ARCS 100      /* Nombre maximum d arcs par etat */
#define TAILLE_CHAINE 50  /* Taille maximum d un nom */
#define FAUX 0
#define VRAI 1

/* Definition du type chaine de caracteres */
typedef char chaineC[TAILLE_CHAINE];

/* Definition de la structure contenant un arc */
typedef struct { chaineC nomEtatArrivee; /* Nom de l etat d arrivee */
                 chaineC nomEtiquette;   /* Nom de l etiquette */
} arcInfos ;

/* Definition de la structure contenant un etat et ses arcs */
typedef struct { chaineC nomEtat;           /* Nom de l etat */
                 int etatInitial;           /* VRAI ssi etat initial */
                 int etatFinal;             /* VRAI ssi etat final */
                 int nbArcs;                /* Nombre d'arcs */
                 arcInfos vecArcs[MAX_ARCS]; /* Vecteur des arcs */
} etatInfos ;

/* Definition de la structure contenant les etats */
typedef struct { int nbEtats;                   /* Nombre d etats */
                 etatInfos vecEtats[MAX_ETATS]; /* Vecteur des etats */
} tabEtats ;

/* Affichage de la table des etats */
void afficherTable (tabEtats t);

/* Initialisation de la table des etats */
void initTable (tabEtats *t);

/* Recherche de l etat de nom s dans le tableau des etats */
int chercherEtat (tabEtats t, char *s);

/* Ajout de l etat de nom s dans le tableau des etats s il n existe pas */
void insererEtat (tabEtats *t, char *s);

/* Mise a jour du champ etatInitial pour l etat de nom s */
void definirEtatInitial (tabEtats *t, char *s);

/* Mise a jour du champ etatFinal pour l etat de nom s */
void definirEtatFinal (tabEtats *t, char *s);

/* Recherche de l arc d etat d arrivee de nom s et d etiquette de nom e */
int chercherArc(etatInfos s, char *d, char *e);

/* Ajout de l arc s -> d d etiquette e dans le tableau des etats s il n existe pas */
void insererArc (tabEtats *t, char *s, char *d, char *e);
