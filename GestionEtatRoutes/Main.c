/*
 * Main.c
 *
 *  Created on: 23 mars 2020
 *      Author: sdklm
 */


/* --- Fichiers d'entête --- */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* --- Contantes --- */
#define MAX_ROUTES 100
#define T_MAX_NUM 6
#define T_MAX_TEXTE_TYPE 30
#define T_MAX_TEXTE_ETAT 10
#define NON_TROUVE -1
#define INCONNU -1

/* --- Type global --- */
struct TRoute
    {
      char CodeNumero[T_MAX_NUM]  ;
      int Annee                   ;
      int Etat                    ;
      int Vitesse                 ;
      int NbAccidents             ;

    };

/* --- Variables globales --- */
struct TRoute TabRoutes[MAX_ROUTES] ;
int NbRoutes = 0                    ;

/* --- déclarations préliminaires --- */
void Saisie()                                            ;
void conv_maj(char ch[])                                 ;
void Interprete_Type_Route(char Numero[], char texte[])  ;
int Interprete_Limitation_Route(char Numero[], int Etat) ;
void Interprete_Etat_Route(int Etat, char texte[])       ;
void Affichage()                                         ;
int recherche(char ch[20])                               ;
void ModifRoute()                                        ;
void TotalAccidentsParType()                             ;
void tri_insertion(struct TRoute tab[],int nb)           ;
void AfficheAccidentogenes()                             ;
int recherche(char ch[20])                               ;
void quitter()                                           ;


/* =========================== */
/* === programme principal === */
/* =========================== */
int main()
{
 int choix = -1 ;

 while (choix != 0)
 {
    printf("-1- Ajout/Saisie de nouvelles routes\n")        ;
    printf("-2- Affichage des routes\n")                    ;
    printf("-3- Modification d'une route\n")                ;
    printf("-4- Total des accidents par type de routes\n")  ;
    printf("-5- Routes les plus accidentogenes\n")          ;
    printf("-0- Quitter\n")                                 ;
    printf("Choix : ")  ;
    scanf("%d",&choix)  ;
    switch(choix)
    {
        case 1 : Saisie()                 ;
                 break                    ;
        case 2 : Affichage()              ;
                 break                    ;
        case 3 : ModifRoute()             ;
                 break                    ;
        case 4 : TotalAccidentsParType()  ;
                 break                    ;
        case 5 : AfficheAccidentogenes()  ;
                 break                    ;
        case 0 : quitter()                ;
                 break                    ;
        default: printf("Choix erroné\n") ;
                 break;
    }
    printf("\n");
 }

 return 0 ;
}

/* ------------------------------------ */
/* --- saisie d'une liste de Routes --- */
/* ------------------------------------ */
void Saisie()
{
 struct TRoute Route                 ;
 int i = NbRoutes                    ;
 char TypeLibelle[T_MAX_TEXTE_TYPE]  ;

 Route.CodeNumero[0]='\0'            ;
 while (strcmp(Route.CodeNumero,"FIN") != 0)
 {
   printf("Numéro de la route (fin pour terminer) : ") ;
   scanf("%s", Route.CodeNumero)                       ;
   conv_maj(Route.CodeNumero)                          ;
   if (strcmp(Route.CodeNumero,"FIN") != 0 )
   {
     Interprete_Type_Route(Route.CodeNumero, TypeLibelle)  ;
     printf("-> Route                 : %s\n",TypeLibelle) ;
     printf("Annee de construction    : ")  ;
     scanf("%d", &Route.Annee)              ;
     Route.Etat = 1                         ;
     Route.Vitesse = Interprete_Limitation_Route(Route.CodeNumero, Route.Etat);
     Route.NbAccidents = 0                  ;
     TabRoutes[i++] = Route                 ;
   }
 }
 NbRoutes = i ;
 printf("--- Nombre de routes : %d ---\n",NbRoutes);
}

/* ------------------------------------------------------ */
/* --- interprétation du libellé du type de la route --- */
/* ------------------------------------------------------ */
void Interprete_Type_Route(char Numero[], char texte[])
{
  char Initiale = Numero[0];
  switch (Initiale)
  {
    case 'A' : strcpy(texte,"Autoroute")       ; break ;
    case 'N' : strcpy(texte,"Nationale")       ; break ;
    case 'D' : strcpy(texte,"Departementale")  ; break ;
    case 'V' : strcpy(texte,"Vicinale")        ; break ;
    default : strcpy(texte,"Inconnu")          ; break ;
  }
}
/* ------------------------------------------------------ */
/* --- interprétation de la limitation de vitesse selon le type de la route --- */
/* ------------------------------------------------------ */
int Interprete_Limitation_Route(char Numero[], int Etat)
{
  char Initiale = Numero[0]  ;
  int Vitesse = INCONNU      ;
  switch (Initiale)
  {
    case 'A' : Vitesse=130  ; break ;
    case 'N' : Vitesse=80   ; break ;
    case 'D' : Vitesse=70   ; break ;
    case 'V' : Vitesse=50   ; break ;
  }
  if (Etat == 2)
    Vitesse = Vitesse-10  ;
  else if (Etat == 0)
    Vitesse = 0           ;

  return Vitesse ;
}
/* ------------------------------------------------------ */
/* --- interprétation de l'état de la route --- */
/* ------------------------------------------------------ */
void Interprete_Etat_Route(int Etat, char texte[])
{
  switch (Etat)
  {
    case 1  : strcpy(texte,"Bon")      ; break ;
    case 2  : strcpy(texte,"Degrade")  ; break ;
    case 3  : strcpy(texte,"Fermee")   ; break ;
    default : strcpy(texte,"Inconnu")  ; break ;
  }
}

/* --------------------------------------------- */
/* --- Affichage de la liste des Routes --- */
/* --------------------------------------------- */
void Affichage()
{
  struct TRoute Route                ;
  int i                              ;
  char TypeLibelle[T_MAX_TEXTE_TYPE] ;
  char EtatLibelle[T_MAX_TEXTE_ETAT] ;

  if (NbRoutes == 0)
   printf("Aucune route à afficher\n")  ;
  else
  {
   printf("-------------------------------------------------------------------\n");
   printf("%-6s %-15s %10s %-10s %7s %11s \n","Num","Type","Annee","Etat","Vitesse","NbAccidents");
   printf("-------------------------------------------------------------------\n");
   for (i = 0 ; i<NbRoutes ; i++)
   {
     Route = TabRoutes[i]                                  ;
     Interprete_Type_Route(Route.CodeNumero, TypeLibelle)  ;
     Interprete_Etat_Route(Route.Etat, EtatLibelle)        ;
     printf("%-6s %-15s %10d %-10s %7d %11d\n",Route.CodeNumero,TypeLibelle,Route.Annee,EtatLibelle,Route.Vitesse,Route.NbAccidents);
   }
   printf("-------------------------------------------------------------------\n");
  }
}

/* -------------------------------------------------------------------- */
/* --- outil de conversion en majuscules d'une chaîne de caractères --- */
/* -------------------------------------------------------------------- */
void conv_maj(char ch[])
{
  int i, taille       ;

  taille = strlen(ch) ;
  for (i=0 ; i< taille ; i++)
  {
    ch[i] = toupper(ch[i]) ;
  }
}

/* --------------------------- */
/* --- fonction de recherche --- */
/* --------------------------- */
int recherche(char ch[20])
{
  int i, numcase=NON_TROUVE ;
  struct TRoute Route       ;

  for (i = 0 ; i<NbRoutes ; i++)
  {
    Route = TabRoutes[i] ;
    if (strcmp(Route.CodeNumero,ch) == 0)
    {
      numcase = i ;
    }
  }
 return numcase ;
}

/* ------------------------------------------ */
/* --- Procédure de Modification d'une route --- */
/* ------------------------------------------ */
void ModifRoute()
{
  char CodeRoute[T_MAX_NUM]          ;
  int numcase                        ;
  struct TRoute Route                ;
  char TypeLibelle[T_MAX_TEXTE_TYPE] ;
  char EtatLibelle[T_MAX_TEXTE_ETAT] ;

  if (NbRoutes == 0)
   printf("Aucune route à modifier\n")  ;
  else
  {

    printf("Numéro de la route à modifier : ") ;
    scanf("%s", CodeRoute)                      ;
    conv_maj(CodeRoute)                         ;
    numcase = recherche(CodeRoute)              ;
    if (numcase == NON_TROUVE)
    {
      printf("%s pas trouvé !\n",CodeRoute)     ;
    }
    else
    {
      Route = TabRoutes[numcase]  ;

      Interprete_Type_Route(Route.CodeNumero, TypeLibelle)  ;
      Interprete_Etat_Route(Route.Etat, EtatLibelle)        ;

      printf("-------------------------------------------------------------------\n");
      printf("%-6s %-15s %10s %-10s %7s %11s \n","Num","Type","Annee","Etat","Vitesse","NbAccidents");
      printf("-------------------------------------------------------------------\n");
      printf("%-6s %-15s %10d %-10s %7d %11d\n",Route.CodeNumero,TypeLibelle,Route.Annee,EtatLibelle,Route.Vitesse,Route.NbAccidents);
      printf("-------------------------------------------------------------------\n");

      printf("Nouvel etat (1=Bon, 2=Degrade, 3=Fermee) : ") ;
      scanf("%d",&Route.Etat)                               ;
      if (Route.Etat != 1)
      {
        Route.Vitesse = Interprete_Limitation_Route(Route.CodeNumero, Route.Etat);
      }

      printf("Nouveau nombre d'accidents               : ") ;
      scanf("%d",&Route.NbAccidents)                        ;

      TabRoutes[numcase] = Route                            ;
    }
  }
}

/* ---------------------------------------------------- */
/* --- Affichage total accidents par type de routes --- */
/* ---------------------------------------------------- */
void TotalAccidentsParType()
{
  struct TRoute Route                        ;
  int i,TotalA=0,TotalN=0,TotalD=0,TotalV=0  ;
  char CategorieRoute                        ;

  if (NbRoutes == 0)
   printf("Aucune route pour calculer le total des accidents\n")  ;
  else
  {
   for (i = 0 ; i<NbRoutes ; i++)
   {
     Route            = TabRoutes[i]       ;
     CategorieRoute   = Route.CodeNumero[0];
     switch (CategorieRoute)
     {
       case 'A' : TotalA+=Route.NbAccidents  ; break ;
       case 'N' : TotalN+=Route.NbAccidents  ; break ;
       case 'D' : TotalD+=Route.NbAccidents  ; break ;
       case 'V' : TotalV+=Route.NbAccidents  ; break ;
     }
   }
   printf("-------------------------------------------------------------------\n");
   printf("Total des accidents par type de route :\n");
   printf("-------------------------------------------------------------------\n");
   printf("      Autoroute      = %10d\n",TotalA) ;
   printf("      Nationale      = %10d\n",TotalN) ;
   printf("      Departementale = %10d\n",TotalD) ;
   printf("      Vicinale       = %10d\n",TotalV) ;
   printf("-------------------------------------------------------------------\n");
  }
}

/* ---------------------------------------------------- */
/* --- Affichage total accidents par type de routes --- */
/* ---------------------------------------------------- */
void AfficheAccidentogenes()
{
  tri_insertion(TabRoutes,NbRoutes) ;
  Affichage()                       ;
}

/* ----------------- */
/* procédure de tri  */
/* ----------------- */
void tri_insertion(struct TRoute tab[],int nb)
{
  int i, j            ;
  struct TRoute Route ;
  for (i=0 ; i<nb ; i++)
  {  Route=tab[i] ;
     j=i          ;
     while ( (j>0) && (Route.NbAccidents > tab[j-1].NbAccidents) )
     {
       tab[j]=tab[j-1] ;
       j--             ;
     }
     tab[j]=Route      ;
  }
}

/* --------------- */
/* --- quitter --- */
/* --------------- */
void quitter()
{
    printf("Au revoir\n");
}
