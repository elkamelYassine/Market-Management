
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>
#include"liste.h"
#include "math.h"

/***** Fonction cr�ation *****/
void creer_liste(struct liste *LP)
{
    LP->premier=NULL ;
    LP->dernier=NULL ;
}
               /***** Fonction test *****/
int recherche_produit (liste_p LP, int num)
{
    struct cellule *p=LP.premier;
   	while(p)
   	    {if((p->info).code==num)
   	        return 1;
   	    else
   	        p=p->suivant;
   	    }
   	return 0;
}
 /***** Fonction taille *****/
int taille_liste_produit (liste_p LP)
{
    struct cellule *p=LP.premier;
    int t=0;
   	while(p)
    {
        t++;
        p=p->suivant;
    }
   	return t;
}

/**********************************/
int verif4(char ch[])
{
    int i;
    for(i=0;i<10;i++)
        if(i==2||i==5)
        {
            if(ch[i]!='/')
                return 0;
        }
        else
            if(ch[i]<'0'||ch[i]>'9')
                return 0;
    return 1;
}


/********FONCTION BISSEXTILE*******/
int BISSEXTILE(int a)
{
    if((a%4==0 && a%100!=0)|| (a%400==0))
        return 1;
    else
        return 0;

}
/********FONCTION JOUR_MAX**********/

int verif_date(char ch[])
{
    char jj[3],mm[3],aa[5];
    int j,k,i, m, a,jmax;
    for(i=0;i<2;i++)
        jj[i]=ch[i];
    jj[i]='\0';
    for(i++,k=0;i<5;i++)
        mm[k++]=ch[i];
    mm[k]='\0';
    for(i++,k=0;ch[i];i++)
        aa[k++]=ch[i];
    aa[k]='\0';
    j=atoi(jj);
    m=atoi(mm);
    a=atoi(aa);
    switch(m)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            jmax =31 ;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            jmax =30 ;
            break;
        case 2:
            if(BISSEXTILE(a))
                jmax=29;
            else
                jmax=28;
    }
     return j>=1 && j<=jmax && m>=1 && m<=12 && a>=1900 && verif4(ch) && strlen(ch)==10;
}



                /***** Fonction saisie_produit *****/
produit saisie_produit(liste_p LP )
{
    produit p;
    do
    {
        printf("donnez le code : ");
        scanf("%d",&p.code);
    }while(!(recherche_produit (LP, p.code)==0));
    printf("Donner le nom : ");
    fflush(stdin);
    scanf("%s",p.nom);
    do
    {
        printf("Donner la date de production sous la forme jj/mm/aaaa : ");
        fflush(stdin);
        scanf("%s",&p.dp);
    }while(!(verif_date(p.dp)));
    do
    {
        printf("Donner la date d'expiration sous la forme jj/mm/aaaa : ");
        fflush(stdin);
        scanf("%s",&p.de);
    }while(!(verif_date(p.de)));
    printf("Donner le prix: ");
    fflush(stdin);
    scanf("%f",&p.prix);
    printf("Donner la quantite: ");
    fflush(stdin);
    scanf("%d",&p.qte);
   return p;
}

 /***** Fonction inserer_queue_produit *****/
liste_p inserer_queue_produit(liste_p LP,produit x)
{
    struct cellule *q;
    q = (struct cellule*)malloc(sizeof(struct cellule));
    q->info = x;
    q->suivant = NULL ;
    if(LP.dernier==NULL)
        LP.premier=q;
    else
        (LP.dernier)->suivant=q;
    LP.dernier = q;
    return LP;
}
/***** Fonction inserer_tete_produit *****/
liste_p inserer_tete_produit(liste_p LP,produit x)
{
    struct cellule * q;
    q = (struct cellule*)malloc(sizeof(struct cellule));
    q->info = x;
    q->suivant = LP.premier ;
    if(LP.premier==NULL)
        LP.dernier=q;
    LP.premier = q;
    return LP;
}
/***INSERE POS***/

void insere_pos_produit(liste_p LP, int pos,produit x )
{
    struct cellule * p2;
    struct cellule *p1=LP.premier;
    int i=1;
    while(i<pos-1)
    {
        p1=p1->suivant;
        i++;
    }
    p2=(struct cellule*)malloc(sizeof(struct cellule));
    p2->info=x;
    p2->suivant=p1->suivant;
    p1->suivant=p2;
}
                      /***** Fonction affiche *****/
void affiche(liste_p LP)
{
    struct cellule *P=LP.premier;
    if(P==NULL)
        printf("Liste vide\n");
    else
    {
    printf("Code\tNom\tDate production\tDate expiration\tPrix\tQuantite\n");
    while (P)
    {
       printf("%d\t%s\t%s\t%s\t%.3f\t%d\n",(P->info).code,(P->info).nom,(P->info).dp,(P->info).de,P->info.prix,P->info.qte);
       P=P->suivant;
    }
  }
}
liste_p creation(liste_p LP)
{
    int rep,pos ,t;
    produit x;
    do
    {
        t=taille_liste_produit(LP);
        do
        {
            printf("Donner la position entre 1 et %d: ",t+1);
            scanf("%d",&pos);
        }while(!(pos>=1 && pos<=t+1));
        x=saisie_produit(LP);
        if(pos==1)
            LP=inserer_tete_produit(LP,x);
        else
            if(pos==t+1)
                LP=inserer_queue_produit(LP,x);
            else
                insere_pos_produit(LP,pos,x);
        do
        {
            printf("Voulez vous ajouter un autre produit 1/0 � (1 pour Oui, 0 pour Non):");
            scanf("%d",&rep);
        }while(!(rep==1 || rep==0));
    }while(rep);
    return LP;
}
/*****Fonction suppression tete*******/
liste_p supprimer_tete_produit( liste_p LP)
{
    struct cellule * s;
    s= LP.premier;
    LP.premier = s->suivant;
    free(s);
    /* exception une liste form�e d�un seul �l�ment */
    if(LP.premier ==NULL)
        LP.dernier=NULL;
    return LP;
}
/*****Fonction suppression queue*******/
liste_p supprimer_queue_produit( liste_p LP)
{
    struct cellule * p; /*pour parcourir ll */
    if(LP.premier==LP.dernier) /* liste form� d�un seul �l�ment*/
        LP=supprimer_tete_produit(LP);
    else
    {
        p=LP.premier;
        while(p->suivant!= LP.dernier)
            p=p->suivant;
        p->suivant=NULL; /* mise � jour */
        free(LP.dernier); /* lib�rer de dernier */
        LP.dernier=p; /* mise � jour */

    }
    return LP;
}
void  supprime_position( liste_p LP, int  pos )
{
    struct cellule * p1=LP.premier;
    struct cellule *p2 ;
    int  i =1;
    while(i<pos-1)
    {
        i ++;
        p1=p1->suivant ;
    }
    p2=p1->suivant ;
    p1->suivant=p2->suivant ;
    free (p2) ;
}
/*****Suppression produit donn�*****/
liste_p  SUPP_PRODUIT(liste_p LP,int num)
{
    struct cellule *p=LP.premier,*q;
    int ok=0;
    if((p->info).code==num)
    {  if (taille_liste_produit(LP)>0)
            LP.premier=p->suivant;


        else  creer_liste(&LP);
        free(p);
        return LP;
    }
    else
    {    while(p->suivant)
            if((p->suivant)->info.code==num)
            {
                ok=1;
                break;
            }
            else
                p=p->suivant;
        if(ok)
        {   q=p->suivant;
            if(q==LP.dernier)
                LP.dernier=p;
            p->suivant=q->suivant;
            free(q);
        }
    }
    return LP;
}
date conversion_chaine_structure(char ch[])
{
    date d;
    char jj[3],mm[3],aa[5];
    int j,k,i, m, a,jmax;
    for(i=0;i<2;i++)
        jj[i]=ch[i];
    jj[i]='\0';
    for(i++,k=0;i<5;i++)
        mm[k++]=ch[i];
    mm[k]='\0';
    for(i++,k=0;ch[i];i++)
        aa[k++]=ch[i];
    aa[k]='\0';
    d.j=atoi(jj);
    d.m=atoi(mm);
    d.a=atoi(aa);
    return d;
}
/******Fonction COMPARER DATE *****/
int comparer_date (char d1[], char d2[])
{

    date date1,date2;
    date1=conversion_chaine_structure(d1);
    date2=conversion_chaine_structure(d2);
    if (date1.a < date2.a)
       return -1;
    else
        if (date1.a>date2.a)
            return 1;
        else
            if (date1.a == date2.a)
            {
                if (date1.m<date2.m)
                    return -1;
                else
                    if (date1.m>date2.m)
                        return 1;
                    else
                        if (date1.m == date2.m)
                        {
                            if (date1.j<date2.j)
                                return -1;
                            else
                                if (date1.j>date2.j)
                                    return 1;
                                else
                                    return 0;
                        }
            }
}


char * date_systeme ()
 {

char *ch;
int mois;
ch=(char *)malloc (40*sizeof (char));

    SYSTEMTIME t; // Declare SYSTEMTIME struct

    GetLocalTime(&t); // Fill out the struct so that it can be used

    // Use GetSystemTime(&t) to get UTC time
   itoa(t.wDay,ch,10);

    ch[2]='/';

mois =t.wMonth;
if (mois <10)
    ch[3]='0';

    itoa(t.wMonth,ch+4,10);

    ch[5]='/';

    itoa(t.wYear,ch+6,10);


    ch[10]='\0';

return ch;
}


/********** enregistrement **********/

void enregistrement(liste_p LP)
{
    FILE *f;
     struct cellule *p=LP.premier;
    f=fopen("produit.txt","w");
    while(p)
    {
        fprintf(f,"%d|%s|%s|%s|%f|%d\n",p->info.code,p->info.nom,p->info.dp,p->info.de,p->info.prix,p->info.qte);
        p=p->suivant;
    }
    fclose(f);
}
liste_p recuperation()
{
    FILE * f;
    f = fopen("produit.txt", "r");
    produit prod;
    liste_p LP;
    creer_liste(&LP);
    while(!feof(f))
    {
        fscanf(f,"%d|%[^|]|%[^|]|%[^|]|%f|%d\n", &prod.code, prod.nom, prod.dp, prod.de,&prod.prix,&prod.qte);
        LP=inserer_queue_produit(LP,prod);
    }
    fclose(f);
    return LP;

}
void affiche_produits_expires(liste_p LP)
{
    struct cellule *P=LP.premier;
    while (P)
    {
       if(comparer_date (P->info.de,date_systeme())==-1)
           printf("%d\t%s\t%s\t%s\t%.3f\t%d\n",(P->info).code,(P->info).nom,(P->info).dp,(P->info).de,P->info.prix,P->info.qte);
       P=P->suivant;
    }


}


int verif_numerique (char ch[])
{int i;
    for(i=0;i<strlen(ch);i++)
    {
        if((ch[i]<'0') || (ch[i]>'9'))
            return 0;
    }
    return 1;


}

int verif_charactere(char ch[])
{int i;
    for(i=0;i<strlen(ch);i++)
    {
        if((ch[i]<'A') || ((ch[i]>'Z')&&(ch[i]<'a'))||(ch[i]>'z'))
            return 0;
    }
    return 1;


}



int saisie_code (char*info,liste_p LP )
{   int code;
    if (verif_numerique(info))
        code=(int)info;
    else
        return 0;
    if (recherche_produit (LP, code)==0)
        return 1;

    else
        return 0 ;

}

int saisie_code_existant (char*info,liste_p LP )
{   int code;
    if (verif_numerique(info))
        code=(int)info;
    else
        return 0;
    if (recherche_produit (LP, code)==1)
        return 1;

    else
        return 0 ;

}


int saisie_nom(char * nom )
{
    if (verif_charactere(nom)&& strlen(nom)<30)
        return 1;
    else
        return 0;
}

int saisie_prix (char ch[])
{
    int i,j,k,s=0;
    char*ch2,*ch3;
    ch2=(char*)malloc(30*sizeof (char));
    ch3=(char*)malloc(30*sizeof (char));
    for(i=0;i<strlen(ch);i++)
    {   if (ch[i]=='.')
        {s=1;
            for (j=0;j<i;j++)
                ch2[j]=ch[j];
            ch2[i]='\0';


            if (!(verif_numerique(ch2)))
                return 0;

            for (j=i+1,k=0;j<strlen(ch);j++,k++)
                ch3[k]=ch[j];
            ch3[strlen(ch)-i-1]='\0';

            if (!(verif_numerique(ch3)))
                return 0;

    }

    }
    if (s==0)
        return (verif_numerique(ch));
return 1;
}

int saisie_position (char *position,liste_p LP)
{
int pos,t;
    t=taille_liste_produit(LP);

    if (verif_numerique(position))
    {pos=(int)(atof(position));


       if  (pos>1 && pos<t+1)
        return 1;
    }
return 0;
}




int saisie_qte (char * qte)
{
    return (verif_numerique(qte));
}


void graphAjouterTQProduit (int k)
{   int i;
    char *c;
    gotoxy(2,6);
    for (i=0;i<=117;i++)
        printf("-");


    if (k==0)
    {
        gotoxy(48-strlen("Ajouter un produit en TETE")%2,7);
        printf ("Ajouter un produit en TETE");

    }
    if (k==1)
    {
        gotoxy(48-strlen("Ajouter un produit en QUEUE")%2,7);
        printf ("Ajouter un produit en QUEUE");

    }
    gotoxy(2,8);

    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(40-strlen("Matricule de produit : "),9);
    printf ("Matricule de produit : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Nom de produit : "),11);
    printf ("Nom de produit : ");

    gotoxy(2,12);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date de production : "),13);
    printf ("Date de production : ");
    gotoxy(41,13);
    printf ("jj/mm/aaaa");

    gotoxy(2,14);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date d'expiration : "),15);
    printf ("Date d'expiration : ");
    gotoxy(41,15);
    printf ("jj/mm/aaaa");

    gotoxy(2,16);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("prix : "),17);
    printf ("prix : ");
    gotoxy(2,18);


    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("quantite : "),19);
    printf ("quantite : ");
    gotoxy(2,20);

    for (i=0;i<=117;i++)
        printf("-");

    for (i=7;i<=20;i+=2)
    {
        gotoxy(1,i);
        printf("|");
        gotoxy (120,i);
        printf("|");


    }
gotoxy (1,22);

}


void scangraphAjouterTQProduit (liste_p *LP,int k)
{
char * Matricule,*Nom,*Datep,*Datee,*prix,*qte;
produit x;
Matricule=(char *)malloc (20*sizeof (char));
Nom=(char *)malloc (20*sizeof (char));
Datep=(char *)malloc (20*sizeof (char));
Datee=(char *)malloc (20*sizeof (char));
prix=(char *)malloc (20*sizeof (char));
qte=(char *)malloc (20*sizeof (char));


gotoxy(41,9);
fflush(stdin);
scanf("%s",Matricule);


    while  (!(saisie_code(Matricule, *LP)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);

        };


gotoxy(41,11);
fflush(stdin);
scanf("%s",Nom);

   while  (!(saisie_nom(Nom)))
        {
            gotoxy(41,11);
            printf ("                                                                 ");
            gotoxy(41,11);
            fflush(stdin);
            scanf("%s",Nom);
        };


gotoxy(41,13);
printf ("                                                                 ");
gotoxy(41,13);
fflush(stdin);
scanf("%s",Datep);


    while  (!(verif_date(Datep)))
        {   fflush(stdin);
            gotoxy(41,13);
            printf ("                                                                 ");
            gotoxy(41,13);
            fflush(stdin);
            scanf("%s",Datep);
        };


gotoxy(41,15);
printf ("                                                                 ");
gotoxy(41,15);
fflush(stdin);
scanf("%s",Datee);

    while  (!(verif_date(Datee)))
        {
            gotoxy(41,15);
            printf ("                                                                 ");
            gotoxy(41,15);
            fflush(stdin);
            scanf("%s",Datee);

        };

gotoxy(41,17);
fflush(stdin);
scanf("%s",prix);

    while  (!(saisie_prix(prix)))
        {
            gotoxy(41,17);
            printf ("                                                                 ");
            gotoxy(41,17);
            fflush(stdin);
            scanf("%s",prix);

        };


gotoxy(41,19);
fflush(stdin);
scanf("%s",qte);

    while  (!(saisie_qte(qte)))
        {
            gotoxy(41,19);
            printf ("                                                                 ");
            gotoxy(41,19);
            fflush(stdin);
            scanf("%s",qte);

        };




    Remplir_produit(&x,Matricule,Nom,Datep,Datee,prix,qte);
    if (k==0)

        *LP=inserer_tete_produit(*LP,x);
    if (k==1)
        *LP=inserer_queue_produit(*LP,x);

printf("\nCONTENU DE LA LISTE \n");
    affiche(*LP);


}
void Remplir_produit(produit *p,char * Matricule,char*Nom,char*Datep,char*Datee,char *prix,char *qte)
{//produit p;
    int i;
    p->code=(int)(atof(Matricule));
    strcpy(p->nom,Nom);
    strcpy(p->dp,Datep);
    strcpy(p->de,Datee);
    p->prix=(float)(atof(prix));
    p->qte=(int)(atof(qte));

    return p;
}




void graphAjouterPosProduit ()
{   int i;
    char *c;
    gotoxy(2,6);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(45-strlen("Ajouter un produit en position donnee")%2,7);
    printf ("Ajouter un produit en position donnee");

    gotoxy(2,8);

    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(40-strlen("POSITION : "),9);
    printf ("POSITION : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(2,22);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(40-strlen("Matricule de produit : "),11);
    printf ("Matricule de produit : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Nom de produit : "),13);
    printf ("Nom de produit : ");

    gotoxy(2,12);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date de production : "),15);
    printf ("Date de production : ");
    gotoxy(41,15);
    printf ("jj/mm/aaaa");

    gotoxy(2,14);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date d'expiration : "),17);
    printf ("Date d'expiration : ");
    gotoxy(41,17);
    printf ("jj/mm/aaaa");

    gotoxy(2,16);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("prix : "),19);
    printf ("prix : ");
    gotoxy(2,18);


    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("quantite : "),21);
    printf ("quantite : ");
    gotoxy(2,20);

    for (i=0;i<=117;i++)
        printf("-");

    for (i=7;i<=22;i+=2)
    {
        gotoxy(1,i);
        printf("|");
        gotoxy (120,i);
        printf("|");


    }
gotoxy (1,24);

}

void scangraphAjouterPosProduit (liste_p LP)
{
char * Matricule,*Nom,*Datep,*Datee,*prix,*qte,*position;
produit x;
position=(char *)malloc (20*sizeof (char));

Matricule=(char *)malloc (20*sizeof (char));
Nom=(char *)malloc (20*sizeof (char));
Datep=(char *)malloc (20*sizeof (char));
Datee=(char *)malloc (20*sizeof (char));
prix=(char *)malloc (20*sizeof (char));
qte=(char *)malloc (20*sizeof (char));


gotoxy(41,9);

fflush(stdin);
scanf("%s",position);


    while  (!(saisie_position(position, LP)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",position);

        };




gotoxy(41,11);
fflush(stdin);
scanf("%s",Matricule);

    while  (!(saisie_code(Matricule, LP)))
        {
            gotoxy(41,11);
            printf ("                                                                 ");
            gotoxy(41,11);
            fflush(stdin);
            scanf("%s",Matricule);

        };


gotoxy(41,13);
fflush(stdin);
scanf("%s",Nom);

    while  (!(saisie_nom(Nom)))
        {
            gotoxy(41,13);
            printf ("                                                                 ");
            gotoxy(41,13);
            fflush(stdin);
            scanf("%s",Nom);
        };


gotoxy(41,15);
printf ("                                                                 ");
gotoxy(41,15);
fflush(stdin);
scanf("%s",Datep);


    while  (!(verif_date(Datep)))
        {   fflush(stdin);
            gotoxy(41,15);
            printf ("                                                                 ");
            gotoxy(41,15);
            fflush(stdin);
            scanf("%s",Datep);
        };


gotoxy(41,17);
printf ("                                                                 ");
gotoxy(41,17);
fflush(stdin);
scanf("%s",Datee);

    while  (!(verif_date(Datee)))
        {
            gotoxy(41,17);
            printf ("                                                                 ");
            gotoxy(41,17);
            fflush(stdin);
            scanf("%s",Datee);

        };

gotoxy(41,19);
fflush(stdin);
scanf("%s",prix);

    while  (!(saisie_prix(prix)))
        {
            gotoxy(41,19);
            printf ("                                                                 ");
            gotoxy(41,19);
            fflush(stdin);
            scanf("%s",prix);

        };


gotoxy(41,21);
fflush(stdin);
scanf("%s",qte);

    while  (!(saisie_qte(qte)))
        {
            gotoxy(41,21);
            printf ("                                                                 ");
            gotoxy(41,21);
            fflush(stdin);
            scanf("%s",qte);

        };


int pos ;
pos=(int)(atof(position));

    Remplir_produit(&x,Matricule,Nom,Datep,Datee,prix,qte);
    insere_pos_produit(LP,pos,x);

printf("\nCONTENU DE LA LISTE \n");
    affiche(LP);

}

void graphSuppressionPos()
{
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(39-strlen("Suppression de produit en position donnee")%2,4);
    printf ("Suppression de produit en position donnee");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("POSITION : "),9);
    printf ("POSITION : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");

gotoxy(16,1);
}


void scangraphSuppressionPos (liste_p LP)
{
char *position;
int pos;
position=(char *)malloc (20*sizeof (char));

gotoxy(41,9);

fflush(stdin);
scanf("%s",position);


    while  (!(saisie_position(position, LP)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",position);

        };

pos=(int)(atof(position));

supprime_position( LP, pos );
}


void graphSuppressionProd()
{
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(45-strlen("Suppression de produit donnee")%2,4);
    printf ("Suppression de produit donnee");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Matricule : "),9);
    printf ("Matricule : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");

gotoxy(1,20);
}

void scangraphSuppressionProd (liste_p LP)
{
char *Matricule;
int code;
Matricule=(char *)malloc (20*sizeof (char));

gotoxy(41,9);

fflush(stdin);
scanf("%s",Matricule);


    while  (!(verif_numerique (Matricule)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);

        };

code=(int)(atof(Matricule));

if  (recherche_produit(LP,code)!=1)
        {

            gotoxy(1,14);
            printf("l'element inexistant !");
            gotoxy (1,18);
            return ;


        };

gotoxy(1,18);
printf ("                                                                 ");



    SUPP_PRODUIT ( LP, code );

gotoxy(1,18);
}


void graphModPrix()
{
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(45-strlen("Modifier le prix d'un produit")%2,4);
    printf ("Modifier le prix d'un produit");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Matricule : "),9);
    printf ("Matricule : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");

    gotoxy(40-strlen("Prix : "),11);
    printf ("Prix : ");
    gotoxy(2,12);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,11);
    printf ("|");
    gotoxy(120,11);
    printf ("|");



gotoxy(1,20);
}


void scangraphModPrix (liste_p LP)
{
char *Matricule;
char *prix;
struct cellule *p;
int code;

Matricule=(char *)malloc (20*sizeof (char));
prix=(char *)malloc (20*sizeof (char));

p=LP.premier;
gotoxy(41,9);

fflush(stdin);
scanf("%s",Matricule);


    while  (!(verif_numerique (Matricule)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);

        };

code=(int)(atof(Matricule));

while  (recherche_produit(LP,code)!=1)
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(1,18);
            printf("l'element inexistant !");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);
            code=(int)(atof(Matricule));
        };

gotoxy(1,18);
printf ("                                                                 ");


gotoxy(41,11);

fflush(stdin);
scanf("%s",prix);


    while  (!(saisie_prix (prix)))
        {
            gotoxy(41,11);
            printf ("                                                                 ");
            gotoxy(41,11);
            fflush(stdin);
            scanf("%s",prix);

        };

while (p->info.code!=code)
    p=p->suivant;

p->info.prix=(float)(atof(prix));
gotoxy(1,20);
}


void graphModQuantite()
{
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(45-strlen("Modifier la quantite d'un produit")%2,4);
    printf ("Modifier la quantite d'un produit");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Matricule : "),9);
    printf ("Matricule : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");

    gotoxy(40-strlen("Quantite : "),11);
    printf ("Quantite : ");
    gotoxy(2,12);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,11);
    printf ("|");
    gotoxy(120,11);
    printf ("|");



gotoxy(1,20);
}



void scangraphModQuantite (liste_p LP)
{
char *Matricule;
char *quantite;
struct cellule *p;
int code;

Matricule=(char *)malloc (20*sizeof (char));
quantite=(char *)malloc (20*sizeof (char));

p=LP.premier;

gotoxy(41,9);

fflush(stdin);
scanf("%s",Matricule);


    while  (!(verif_numerique (Matricule)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);

        };

code=(int)(atof(Matricule));

while  (recherche_produit(LP,code)!=1)
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(1,18);
            printf("l'element inexistant !");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);
            code=(int)(atof(Matricule));
        };

gotoxy(1,18);
printf ("                                                                 ");


gotoxy(41,11);

fflush(stdin);
scanf("%s",quantite);


    while  (!(verif_numerique (quantite)))
        {
            gotoxy(41,11);
            printf ("                                                                 ");
            gotoxy(41,11);
            fflush(stdin);
            scanf("%s",quantite);

        };

while (p->info.code!=code)
    p=p->suivant;

p->info.qte=(int)(atof(quantite));

printf("\nCONTENU DE LA LISTE \n");
    affiche(LP);
}


void tableau(int M,int N,int X,int Y,int A,int B)
{
  int  hauteur;
  int  largeur;
  int  cases_hau;
  int  cases_lar;

  gotoxy(M,N);
  printf("\xDA");
  for (largeur=1 ; largeur<=X ; largeur++)
  {
    for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf("\xC4");
    printf("\xC2");
  }
  printf("\b\xBF");
  for (hauteur=0 ; hauteur<Y ; hauteur++)
  {
    for (cases_hau=1 ; cases_hau<=B ; cases_hau++)
    {
      if (cases_hau==B)
      {
        gotoxy(M,N+cases_hau+(hauteur*(B+1))+1);
        printf("\xC3");
        for (largeur=1 ; largeur<=X ; largeur++)
        {
          for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf("\xC4");
          printf("\xC5");
        }
        printf("\b\xB4");
      }
      gotoxy(M,N+cases_hau+(hauteur*(B+1)));
      printf("\xB3");
      for (largeur=1 ; largeur<=X ; largeur++)
      {
        for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf(" ");
        printf("\xB3");
      }
    }
  }
  gotoxy(M,N+(Y*(B+1)));
  printf("\xC0");
  for (largeur=1 ; largeur<=X ; largeur++)
  {
    for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf("\xC4");
    printf("\xC1");
  }
  printf("\b\xD9");
}


void graphafficher(liste_p LP,int x)
{
    int nb=0;
    int i;
    int l=8;
    struct cellule *P=LP.premier;

    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");
    if (x ==0)

{       gotoxy(50-strlen("Affichage de produits")%2,4);
        printf ("Affichage de produits");
}
    else if (x==1)
{
        gotoxy(39-strlen("Recherche produit par date de production")%2,4);
        printf ("Recherche produit par date de production");
}

    else if (x==2)
{
        gotoxy(40-strlen("Recherche produit par date d'expiration")%2,4);
        printf ("Recherche produit par date d'expiration");
}
    else if (x==3)
{
        gotoxy(36-strlen("Recherche produit entre deux dates de production")%2,4);
        printf ("Recherche produit entre deux dates de production");
}

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");


    tableau (1,7,6,taille_liste_produit(LP)+1,18,2);

    gotoxy(2,8);
    printf("Code");

    gotoxy(21,8);
    printf("Nom de produit");

    gotoxy(40,8);
    printf("Date de production");

    gotoxy(59,8);
    printf("Date d'expiration");

    gotoxy(78,8);
    printf("Prix");

    gotoxy(97,8);
    printf("Quantite");

    while (P)
    {   nb++;
        affiche_prod(P,nb);
        P=P->suivant;
    }

    for (i=1;i<=nb+1;i++)
        l+=3;

    gotoxy(1,l+2);
}
void affiche_prod(struct cellule * P , int nb)
{
int l=8,i ;

    for (i=1;i<=nb;i++)
        l+=3;

    gotoxy (2,l);
    printf ("%d",P->info.code);

    gotoxy (21,l);
    printf ("%s",P->info.nom);

    gotoxy (40,l);
    printf ("%s",P->info.dp);

    gotoxy (59,l);
    printf ("%s",P->info.de);

    gotoxy (78,l);
    printf ("%f",P->info.prix);

    gotoxy (97,l);
    printf ("%d",P->info.qte);

}

void Rech_code (liste_p LP)
{
    struct cellule *P=LP.premier;
    int code =graphscan_code (LP);
    int i;
    if (code==0)
        return;
    clrscr() ;

    while (P && P->info.code!=code)
        P=P->suivant ;

    if (P)
 {
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(45-strlen("Recherche produit par code")%2,4);
    printf ("Recherche produit par code");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    tableau (1,7,6,2,18,2);

    gotoxy(2,8);
    printf("Code");
    gotoxy(21,8);
    printf("Nom de produit");
    gotoxy(40,8);
    printf("Date de production");
    gotoxy(59,8);
    printf("Date d'expiration");
    gotoxy(78,8);
    printf("Prix");
    gotoxy(97,8);
    printf("Quantite");



    affiche_prod(P,1);
    gotoxy(1,14);


}
}

/********Rech code****************/
int graphscan_code(liste_p LP)
{
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(45-strlen("Recherche produit par code")%2,4);
    printf ("Recherche produit par code");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Matricule : "),9);
    printf ("Matricule : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");
return (scan_code(LP));
}



int scan_code(liste_p LP)
{
    char *Matricule;

struct cellule *p;
int code;

Matricule=(char *)malloc (20*sizeof (char));


gotoxy(41,9);

fflush(stdin);
scanf("%s",Matricule);


    while  (!(verif_numerique (Matricule)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",Matricule);

        };

code=(int)(atof(Matricule));

while  (recherche_produit(LP,code)!=1)
        {
            gotoxy(1,14);
            printf("l'element inexistant !");
            gotoxy(1,18);
            return 0 ;
        }

gotoxy(1,18);
printf ("                                                                 ");


gotoxy(41,11);

return code;
}





liste_p graphscan_datee(liste_p LP)
{
      liste_p L;
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(40-strlen("Recherche produit par date d'expiration")%2,4);
    printf ("Recherche produit par date d'expiration");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date d'expiration : "),9);
    printf ("Date d'expiration : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");
    L=scan_datee(LP);
    if (taille_liste_produit(L)!=0)
        clrscr();
    return (L);
}




liste_p scan_datee(liste_p LP)
{
    char * datee;
liste_p L;
struct cellule *P=LP.premier;

creer_liste(&L);
datee=(char *)malloc (20*sizeof (char));


gotoxy(41,9);

fflush(stdin);
scanf("%s",datee);


    while  (!(verif_date (datee)))
        {
        gotoxy(41,9);
        printf ("                                                                 ");
        gotoxy(41,9);
        fflush(stdin);
        scanf("%s",datee);

        };


    while (P)
    {
       if(comparer_date (P->info.de,datee)==0)
       {
        if (taille_liste_produit(L)==0)
            L=inserer_tete_produit(L,P->info);
        else
            L=inserer_queue_produit(L,P->info);

        }
        P=P->suivant;
    }
    if (taille_liste_produit(L)==0)
{
        gotoxy(1,14);
        printf("date inexistante !");
        gotoxy(1,18);
        return L;
}


    gotoxy(41,11);

    return L;
}





liste_p graphscan_datep(liste_p LP)
{
      liste_p L;
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(39-strlen("Recherche produit par date de production")%2,4);
    printf ("Recherche produit par date de production");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date de production : "),9);
    printf ("Date de production : ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");
    L=scan_datep(LP);
    if (taille_liste_produit(L)!=0)
        clrscr();
return (L);
}


liste_p scan_datep(liste_p LP)
{
    char * datep;
    liste_p L;
    struct cellule *P=LP.premier;

    creer_liste(&L);
    datep=(char *)malloc (20*sizeof (char));


    gotoxy(41,9);

    fflush(stdin);
    scanf("%s",datep);


    while  (!(verif_date (datep)))
        {
        gotoxy(41,9);
        printf ("                                                                 ");
        gotoxy(41,9);
        fflush(stdin);
        scanf("%s",datep);

        };


    while (P)
    {
       if(comparer_date (P->info.dp,datep)==0)
       {
            if (taille_liste_produit(L)==0)
                L=inserer_tete_produit(L,P->info);
            else
                L=inserer_queue_produit(L,P->info);

            }
        P=P->suivant;
    }
    if (taille_liste_produit(L)==0)
{
        gotoxy(1,14);
        printf("date inexistante !");
        gotoxy(1,18);
        return L;
}

    gotoxy(41,11);

    return L;
}




liste_p graphscan_2datep(liste_p LP)
{
      liste_p L;
      int i;
    gotoxy(31,3);
    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(36-strlen("Recherche produit entre deux dates de production")%2,4);
    printf ("Recherche produit entre deux dates de production");

    gotoxy(31,5);

    for (i=30;i<=85;i++)
        printf("-");

    gotoxy(30,4);
    printf ("|");
    gotoxy(87,4);
    printf ("|");

    gotoxy(2,8);
    for (i=0;i<=117;i++)
        printf("-");

    gotoxy(40-strlen("Date de production 1: "),9);
    printf ("Date de production 1: ");
    gotoxy(2,10);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,9);
    printf ("|");
    gotoxy(120,9);
    printf ("|");

    gotoxy(40-strlen("Date de production 2: "),11);
    printf ("Date de production 2: ");
    gotoxy(2,12);
    for (i=0;i<=117;i++)
        printf("-");
    gotoxy(1,11);
    printf ("|");
    gotoxy(120,11);
    printf ("|");

    L=scan_2datep(LP);
    if (taille_liste_produit(L)!=0)
{
        clrscr();

}


return (L);
}


liste_p scan_2datep(liste_p LP)
{
    char * datep1,* datep2;
liste_p L;
struct cellule *P=LP.premier;
int i=20;

creer_liste(&L);
datep1=(char *)malloc (20*sizeof (char));
datep2=(char *)malloc (20*sizeof (char));


gotoxy(41,9);

fflush(stdin);
scanf("%s",datep1);


    while  (!(verif_date (datep1)))
        {
            gotoxy(41,9);
            printf ("                                                                 ");
            gotoxy(41,9);
            fflush(stdin);
            scanf("%s",datep1);

        };

gotoxy(41,11);

fflush(stdin);
scanf("%s",datep2);


    while  (!(verif_date (datep2)))
        {
            gotoxy(41,11);
            printf ("                                                                 ");
            gotoxy(41,11);
            fflush(stdin);
            scanf("%s",datep2);

        };




    while (P)
    {
        if((comparer_date (P->info.dp,datep1)==1)&& (comparer_date (P->info.dp,datep2)==-1))
       {
        if (taille_liste_produit(L)==0)

            L=inserer_tete_produit(L,P->info);

        else
            L=inserer_queue_produit(L,P->info);

        }
        P=P->suivant;
    }
if (taille_liste_produit(L)==0)
{gotoxy(1,13);

          printf("il n'existe pas des dates entre ces deux date de production !");


}


gotoxy(1,16);

return L;
}





void tri_liste_qte (liste_p *LP)  //Tri 1
{
    struct cellule *aux, *min,*p,*q=(LP)->premier;
    aux = (struct cellule *)malloc(sizeof(struct cellule));

    while(q)
    {
        p = q;
        min=p;
        while(p)
        {
            if(min->info.qte < p->info.qte)
                min=p;
            p=p->suivant;
        }
        aux->info=q->info;
        q->info=min->info;
        min->info=aux->info;
        q=q->suivant;
    }
}

void tri_liste_datep (liste_p *LP)  //Tri 2
{
    struct cellule *aux, *max,*p,*q=(LP)->premier;
    aux = (struct cellule *)malloc(sizeof(struct cellule));

    while(q)
    {
        p = q;
        max=p;
        while(p)
        {
            if(comparer_date( max->info.dp , p->info.dp)==1)
                max=p;
            p=p->suivant;
        }
        aux->info=q->info;
        q->info=max->info;
        max->info=aux->info;
        q=q->suivant;
    }
}
