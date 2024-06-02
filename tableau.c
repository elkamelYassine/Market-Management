#include <stdio.h>
#include <conio.c>

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

void main()
{
  int  positionX;
  int  positionY;
  int  nbcaseshauteur;
  int  nbcaseslargeur;
  int  taillecaseshauteur;
  int  taillecaseslargeur;
  gotoxy(40,1);
  printf("Entrez la position X du tableau : ");
  scanf("%d",&positionX);
  gotoxy(40,2);
  printf("Entrez la position Y du tableau : ");
  scanf("%d",&positionY);
  gotoxy(40,3);
  printf("Entrez un nombre de cases en hauteur : ");
  scanf("%d",&nbcaseshauteur);
  gotoxy(40,4);
  printf("Entrez un nombre de cases en largeur : ");
  scanf("%d",&nbcaseslargeur);
  gotoxy(40,5);
  printf("Entrez une hauteur de cases : ");
  scanf("%d",&taillecaseshauteur);
  gotoxy(40,6);
  printf("Entrez une largeur de cases : ");
  scanf("%d",&taillecaseslargeur);
  tableau(positionX,positionY,nbcaseslargeur,nbcaseshauteur,taillecaseslargeur,taillecaseshauteur);
  getch();
}
