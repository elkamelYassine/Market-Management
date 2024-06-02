
typedef struct
{
    int code;
    char nom[20];
    char dp[11];
    char de[11];
    float prix;
    int qte;
}produit;

struct cellule
{
    produit info;
    struct cellule *suivant;
};

struct liste
{
    struct cellule * premier ;
    struct cellule * dernier ;
} ;
typedef struct liste liste_p;

typedef struct
{
    int j,m,a;

}date;

void creer_liste(struct liste *);
int recherche_produit (liste_p , int);
int taille_liste_produit (liste_p );
produit saisie_produit(liste_p  );
liste_p inserer_queue_produit(liste_p ,produit );
liste_p inserer_tete_produit(liste_p ,produit );
void affiche(liste_p );
liste_p creation(liste_p );
liste_p supprimer_tete_produit( liste_p );
liste_p supprimer_queue_produit( liste_p );
void  supprime_position( liste_p , int  );
liste_p  SUPP_PRODUIT(liste_p ,int );
int BISSEXTILE(int );
int verif4(char ch[]);
int verif_date(char ch[] );
void enregistrement(liste );
liste_p recuperation();
date conversion_chaine_structure(char ch[]);
void affiche_produits_expires(liste_p );
void graphAjouterProduit (int);
void scangraphAjouterTQProduit (liste_p* ,int );
void graphAjouterPosProduit ();
void scangraphAjouterPosProduit (liste_p );
liste_p graphscan_datep(liste_p );
liste_p scan_datep(liste_p );
liste_p graphscan_datee(liste_p );
liste_p scan_datee(liste_p );

liste_p graphscan_2datep(liste_p );
liste_p scan_2datep(liste_p );
