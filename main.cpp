#include <stdio.h>

struct EtapeSt{
    float distance_plat; //représente la distance(en kilomètres) sur terrain plat
    float distance_montagne; // et distance_montagne représente la distance sur terrain montageux.
};
typedef struct EtapeSt Etape;

struct CoureurSt{
    int dossard; //dossard représente le numéro identifiant le coureur,
    float vitesse_plat; //vitesse plat représente la vitesse moyenne (en km/h) du coureur sur terrain plat
    float vitesse_montagne; // vitesse montagne la vitesse moyenne (en km/h) du coureur sur terrain montagneux.
};
typedef struct CoureurSt Coureur;

struct TourSt{
    Coureur coureurs[100]; // coureurs contient les structures décrivant les coureurs
    int nb_coureurs; // nb coureurs indique le nombre de coureurs engagés dans la compétition
    Etape etapes[100]; // etapes contient les structures décrivant les étapes
    int nb_etapes; // nb etapes est le nombre d’étapes total de la course.
};
typedef struct TourSt Tour;

/*
 * 1. Ecrire une fonction :
float distance totale( Etape e )
qui retourne la distance totale (en kilomètres) de l’étape e passée en paramètre.
 * */
float distance_totale(Etape e)
{
    return e.distance_plat+e.distance_montagne;
}

/*
 * 2. Ecrire une fonction :
float temps etape( Etape e, Coureur c )
qui retourne le temps total (en heures) mis par le coureur c pour parcourir l’étape e.
 * */
float temps_etape(Etape e, Coureur c)
{
    return e.distance_plat/c.vitesse_plat + e.distance_montagne/c.vitesse_montagne;
}

/*
 *3. Ecrire une fonction :
int arrive avant( Etape e, Coureur c1, Coureur c2 )
qui retourne vrai si le coureur c1 termine l’étape e avant le coureur c2, et retourne faux sinon. On considèrera
que les coureurs partent toujours en meme temps et qu’il n’y a jamais  égalité.
 * */
int arrive_avant(Etape e, Coureur c1, Coureur c2)
{
    int flag;
    if (temps_etape(e,c1)-temps_etape(e,c2)<0)
        flag = 1;
    else
        flag = 0;
    return flag;
    //return temps_etape(e,c1)<temps_etape(e,c2);
}

/*
 *4. Ecrire une fonction :
int arrive avant tous( Etape e, Coureur c, Coureur coureurs[], int nb coureurs )
qui retourne vrai si le coureur c arrive premier à l’étape e, c’est-à-dire qu’il arrive avant tous les autres,
 et qui retourne faux dans le cas contraire.
 Le tableau coureurs de taille nb coureurs contient l’ensemble des coureurs participant à l’étape, y compris c.
 * */
int arrive_avant_tous( Etape e, Coureur c, Coureur coureurs[], int nb_coureurs )
{
    int flag;
    int i,j,k;
    Coureur c1[nb_coureurs-1]; // ce sont les coureurs sauf c
    for (i = 0,j = 0; i < nb_coureurs ; ++i) {
        if (temps_etape(e,c)-temps_etape(e,coureurs[i])!=0){
            c1[j]=coureurs[i];
            j++;
        }
    }
    for ( k = 0; k < nb_coureurs-1; ++k) {
        if (temps_etape(e,c)-temps_etape(e,c1[k])<0)
            flag = 1;
        else flag = 0;
    }
    return flag;

    /*int i;
    for(i=0;i<nb_coureurs;i++){
        if(arrive_avant(e,coureurs[i],c)){
            return 0;
        }
    }
    return 1;*/
}

/*
 *5. Ecrire une fonction :
float distance totale tour( Tour t )
qui retourne la distance totale (en kilomètres) de l’ensemble des étapes du tour.
 * */
float distance_totale_tour(Tour t)
{
    float dis_totale = 0.0;
    for (int i = 0; i <t.nb_etapes ; ++i) {
        dis_totale+=distance_totale(t.etapes[i]);
    }
    return dis_totale;
}

/*
 * 6. Ecrire une fonction :
Coureur vainqueur etape( Etape e, Coureur coureurs[], int nb coureurs )
qui retourne le coureur arrivé premier lors de l’étape e.
coureurs est un tableau contenant l’ensemble des cou-reurs et nb coureurs indique
 le nombre d’éléments dans ce tableau.
 * */
Coureur vainqueur_etape(Etape e, Coureur coureurs[], int nb_coureurs)
{
    int i,flag=0; // 0: Non trouve , 1: trouve
    Coureur vainqueur;
    for (i = 0; (i <nb_coureurs) && (flag == 0) ; ++i) {
        if (arrive_avant_tous(e,coureurs[i],coureurs,nb_coureurs)){
            flag =1;
            vainqueur = coureurs[i];
        }
    }
    return vainqueur;
}

/*
 *7. On considère que le vainqueur du Tour de France est le coureur ayant remporté le plus d’étapes
 * (c’est-à-dire  étant arrivé premier sur le plus grand nombre d’étapes). Ecrire une fonction :
Coureur vainqueur tour( Tour t )
qui retourne le coureur ayant remporté le Tour de France.
 * */
void vainqueur_tour_parcours(Tour t)
{
    int i,j;
    Coureur vainqueur[100];
    for (i = 0,j=0; i <t.nb_etapes ; ++i) {
       vainqueur[j] =(vainqueur_etape(t.etapes[i],t.coureurs,t.nb_coureurs));
        j++;
    }
    for (int k = 0; k < j ; ++k) {
        printf("%d\n", vainqueur[k].dossard);
    }
}

Coureur vainqueur_tour(Tour t)
{
    int i,j,k;
// pour chaque conreur[i], supposons il ont nbr de reussi 0(CAD combien de fois comme Champion)
    int nb_reussi[100]={0};
    Coureur vainqueur_final;
    for (i = 0; i <t.nb_etapes ; ++i) {
        vainqueur_final =(vainqueur_etape(t.etapes[i],t.coureurs,t.nb_coureurs)); // Le vainqueur final de l'etape i

        for (j = 0; j <t.nb_coureurs ; ++j) //On trouve sa position donc l'indice dans le tableau coureurs[]
        {
            if (t.coureurs[i].dossard == vainqueur_final.dossard)
            {
                nb_reussi[i]++;
            }
        }
    }
    // à chaque fois il a remporté le plus d'étape temporairement, On trouve le vainqueur final après parcourir de tout
    int max_champions=0;
    for (k = 0; k <t.nb_coureurs ; ++k)
    {
        if (nb_reussi[i] > max_champions)
        {
            max_champions =nb_reussi[i];
            vainqueur_final=t.coureurs[i];
        }
    }
    return vainqueur_final;
}

/*
 *8. Ecrire une procédure :
void podium tour( Tour t )
qui place dans le tableau podium les trois coureurs ayant remporté
 le plus d’étapes lors du tour t, ordonnés par nombre de victoires décroissant.
 * */
void podium_tour(Tour t)
{

}

int main(){
/*    int nb_reussi[10]={0};
    for (int i = 0; i <10 ; ++i) {
        printf("%d", nb_reussi[i]);
    }*/
    return 0;
}