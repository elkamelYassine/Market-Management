#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include "myconio.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "liste.h"


liste_p LP;
liste_p L;
struct cellule *P;
struct cellule *q;
int sup=0;

int c=0;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void addmenus(HWND);
void CreateBtt(HWND hwnd) ;

HWND hname ,hage,hout,hogo,Add,Finnish;
 HDC hdc;
HMENU hmenu ;

HBITMAP hlogoImage , hgenerateImage;
int intro=1 ;
char ch[30] ;
long p ;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("my project");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+7;


    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("my project"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1295,                 /* The programs width */
           770,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
  /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{static HBITMAP  hBmp;


   /* if(intro)
    {
        system("start test.exe") ;
        intro=0;
    }*/

    switch (message)                  /* handle the messages */
    {

        case WM_COMMAND:
        switch(wParam)
        {
    /*****creation liste*********/
        case 22:
            if (c==0)
            {   c=1;
                creer_liste(&LP);
            }
            else
                MessageBox(0,"Liste déjà créée ","Création erreur",0);

            break;
        /*****************ajouter Tete***************/
        case 1:
                if (c==0)
                {
                    MessageBox(0,"Il faut créer la liste!","Erreur",0);
                    break;}

                    system("color F9");
                    ShowWindow(hwnd,SW_HIDE);
                    graphAjouterTQProduit (0);

                    scangraphAjouterTQProduit (&LP,0);
                    system("pause");

                    ShowWindow(hwnd,SW_NORMAL);
                    system("cls");
                break;
        /**********ajouter queue**********/
        case 2:
                if (c==0)
                {
                    MessageBox(0,"Il faut créer la liste!","Erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                graphAjouterTQProduit (1);

                scangraphAjouterTQProduit (&LP,1);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
      /**********ajouter pos *****************/
        case 3:
                if (c==0)
                {
                    MessageBox(0,"Il faut créer la liste!","Erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                graphAjouterPosProduit ();

                scangraphAjouterPosProduit (LP);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        /*************supp tete**************/
        case 4:
                if (taille_liste_produit(LP)>0)
                {
                    if(MessageBox(hwnd,"       Vous voulez vraiment supprimer la tete de la liste ?", "Suppression Tete", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                    LP=supprimer_tete_produit(LP);

                }
                else
                {   MessageBox(0,"Suppression non valide","Suppression erreur",0);

                }

                break;
       /*************supp queue************/
        case 5:
                if (taille_liste_produit(LP)>0)
                {
                    if(MessageBox(hwnd,"       Vous voulez vraiment supprimer le queue de la liste ?", "Suppression Queue", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                    LP=supprimer_tete_produit(LP);

                }
                else
                {   MessageBox(0,"Suppression non valide","Suppression erreur",0);

                }

                break;
       /*********supp pos************/
        case 6:
                if (taille_liste_produit(LP)>1)
                {


                    system("color F9");
                    ShowWindow(hwnd,SW_HIDE);
                    gotoxy(25,10);
                    graphSuppressionPos();
                    scangraphSuppressionPos (LP);
                    system("pause");
                    ShowWindow(hwnd,SW_NORMAL);
                    system("cls");}
                else
                {   MessageBox(0,"Suppression non valide","Suppression erreur",0);

                }

                break;

      /*************supp pord*************/
        case 7:

                    if ((LP.premier==NULL)&&(LP.dernier==NULL))
                       {MessageBox(0,"       La liste est vide!", "Suppression erreur",0);
                        break;}

                    system("color F9");
                    ShowWindow(hwnd,SW_HIDE);
                    graphSuppressionProd();
                    scangraphSuppressionProd(LP);
                    system("pause");
                    ShowWindow(hwnd,SW_NORMAL);
                    system("cls");


                break;
        /*************supp date exp******/

        case 8:
            if (taille_liste_produit(LP)==0)
                {MessageBox(0,"       La liste est vide!", "Suppression erreur",0);
                        break;}

        else
                {
                    if(MessageBox(hwnd,"       Vous voulez vraiment supprimer les produits expiree ?", "Suppression Produit", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                   {

                        P=LP.premier;
                    while (P)
                {
                   if(comparer_date (P->info.de,date_systeme())==-1)
                   LP=SUPP_PRODUIT(LP,P->info.code);
                   P=P->suivant;
                }


                   }


                }
            break;
        /*******Mod Prix******/
        case 9:
            if (taille_liste_produit(LP)==0)
                {MessageBox(0,"       La liste est vide!", "Modification erreur",0);
                  break;}

            system("color F9");
            ShowWindow(hwnd,SW_HIDE);
            graphModPrix();
            scangraphModPrix(LP);
            system("pause");
            ShowWindow(hwnd,SW_NORMAL);
            system("cls");
            break;
        /*******Mod Qte******/
        case 10:
            if (taille_liste_produit(LP)==0)
                {MessageBox(0,"       La liste est vide!", "Modification erreur",0);
                  break;}

            system("color F9");
            ShowWindow(hwnd,SW_HIDE);
            graphModQuantite();
            scangraphModQuantite(LP);
            system("pause");
            ShowWindow(hwnd,SW_NORMAL);
            system("cls");
            break;
       /*******affichage liste********/
        case 11:
                if (taille_liste_produit(LP)==0)
                    {MessageBox(0,"       La liste est vide!", "AFFICHAGE erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                graphafficher(LP,0);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        /******Rech code*********/
        case 12:
                if (taille_liste_produit(LP)==0)
                    {MessageBox(0,"       La liste est vide!", "AFFICHAGE erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                Rech_code(LP);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        /************Rech datep********/
        case 13:
                if (taille_liste_produit(LP)==0)
                    {MessageBox(0,"       La liste est vide!", "AFFICHAGE erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                creer_liste(&L);
                L=graphscan_datep(LP);
                if (taille_liste_produit(L)!=0)
                    graphafficher(L,1);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
      /*******Rech datee******/
        case 14:
                if (taille_liste_produit(LP)==0)
                    {MessageBox(0,"       La liste est vide!", "AFFICHAGE erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                creer_liste(&L);
                L=graphscan_datee(LP);
                if (taille_liste_produit(L)!=0)
                    graphafficher(L,2);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        /*******Rech 2 datep******/
        case 15:
                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                creer_liste(&L);
                L=graphscan_2datep(LP);
                if (taille_liste_produit(L)!=0)
                    graphafficher(L,3);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;


        /************tri1***********/
        case 16:
                if (taille_liste_produit(LP)==0)
                    {MessageBox(0,"       La liste est vide!", "AFFICHAGE erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                tri_liste_qte (&LP);
                graphafficher(LP,0);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        /************tri2***********/
        case 17:
                if (taille_liste_produit(LP)==0)
                    {MessageBox(0,"       La liste est vide!", "AFFICHAGE erreur",0);
                    break;}

                system("color F9");
                ShowWindow(hwnd,SW_HIDE);
                tri_liste_datep(&LP);
                graphafficher(LP,0);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;


        /*********enregistrer********/
        case 18:

            if (c==0)
                {
                    MessageBox(0,"Il faut créer la liste!","Erreur",0);
                    break;}

            MessageBox(0,"       Fichier enregistré!", "Enregistrer",0);
            enregistrement(LP);
            break;

        /******charger**********/
        case 19:
            MessageBox(0,"       Fichier chargé!", "Chargement",0);
            LP=recuperation();
            c=1;
            break;


        /************quitter***********/
        case 20:
                if (MessageBox(hwnd,"       Vous voulez quitter ?", "QUITTER", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {

                    DestroyWindow(hwnd);
                    system("cls");
                }
            break;


        case 21 :
            system("projet-3.pdf");
}
    case WM_CREATE :
        addmenus(hwnd);
//         CreateBtt(hwnd) ;


            /*****************ajouter fond **********************/
            hBmp=LoadImage(NULL,"pr.bmp",IMAGE_BITMAP,1280,720,LR_LOADFROMFILE);

            break;

        case WM_PAINT :
            {



         PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);

            DrawState(hdc,NULL,NULL,(long)hBmp,0,0,0,0,0,DST_BITMAP);

            EndPaint(hwnd, &ps);}
        break;
        case WM_DESTROY:
            PostQuitMessage (0);        /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void addmenus(HWND hwnd)
{
    hmenu=CreateMenu();
    HMENU htp=CreateMenu();
    HMENU htp1=CreateMenu();
    HMENU htp2=CreateMenu();

    HMENU hex1=CreateMenu();
    HMENU hex2=CreateMenu();
    HMENU hex3=CreateMenu();

    //AppendMenu(hmenu,MF_STRING,0,"création du repertoire");
    /*******************************************************/
    AppendMenu(hmenu,MF_STRING,22,"Creation de liste");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp,"Mise à jour");

    AppendMenu(htp,MF_POPUP,(UINT_PTR)hex1,"Ajouter un nouvel produit");
        AppendMenu(hex1,MF_STRING,1,"Ajout en Tete"); /*Sous partie de l'ex3*/
        AppendMenu(hex1,MF_STRING,2,"Ajout en queue");
        AppendMenu(hex1,MF_STRING,3,"Ajout dans une position");

    AppendMenu(htp,MF_POPUP,(UINT_PTR)hex2,"Supprimer un produit");
        AppendMenu(hex2,MF_STRING,4,"Suppression Tete"); /*Sous partie de l'ex3*/
        AppendMenu(hex2,MF_STRING,5,"Suppression en queue");
        AppendMenu(hex2,MF_STRING,6,"Suppression à partir d'une position");
        AppendMenu(hex2,MF_STRING,7,"Suppression à produit donné");
        AppendMenu(hex2,MF_STRING,8,"Suppression des produits expirés");


    AppendMenu(htp,MF_POPUP,(UINT_PTR)hex3,"Modifier un produit");
        AppendMenu(hex3,MF_STRING,9,"Prix"); /*Sous partie de l'ex3*/
        AppendMenu(hex3,MF_STRING,10,"Quantité");

/***************************************************************/

     AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp1,"Recherche et Affichage");

      AppendMenu(htp1,MF_STRING,11,"Contenu de la liste des produits");
      AppendMenu(htp1,MF_STRING,12,"Recherche par code produit");
      AppendMenu(htp1,MF_STRING,13,"Recherche par date de production");
      AppendMenu(htp1,MF_STRING,14,"Recherche par date d'éxpiration");
      AppendMenu(htp1,MF_STRING,15,"Recherche des produits entre deux dates de production");

      AppendMenu(htp1,MF_STRING,16,"Tri 1");
      AppendMenu(htp1,MF_STRING,17,"Tri 2");

/***************************************************************/
     AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp2,"Enregistrement et chargement");

      AppendMenu(htp2,MF_STRING,18,"Enregistrement");
      AppendMenu(htp2,MF_STRING,19,"Chargement");

/***************************************************************/
    AppendMenu(hmenu,MF_STRING,21,"Enoncee");
    AppendMenu(hmenu,MF_STRING,20,"Quitter");



    SetMenu(hwnd,hmenu);
}

