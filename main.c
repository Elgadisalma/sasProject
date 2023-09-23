#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TACHES 100

struct Tache 
{
    char nom[50];
    int id;
    char t_nom[50];
    char t_desc[20];
    char dateLimite[11];
    char statut[20];
};

struct Tache taches[MAX_TACHES];
int numID = 1;
int nombreTaches = 0;

int afficherTaches();
void ajouterTache();
void modifierTache();
void triAlphabetique();
void triDeadline();
void supprimerTache();
void joursRestants();
int rechercher();
void rechercher_par_id();
void rechercher_par_nom();
void statistiques();
void nombreTtci();
void nombreJoursRestant();

int main() 
{
    int choix;

    while (1) 
    {
        printf("\n*************** ACCUEIL *****************\n");
        printf("1: Ajouter une tâche\n");
        printf("2: Modifier une tâche\n");
        printf("3: Supprimer une tâche\n");
        printf("4: Afficher les tâches\n");
        printf("5: Rechercher une tâche\n");
        printf("6: Afficher les statistiques\n");
        printf("7: Quitter\n");
        scanf("%d", &choix);

        switch (choix) 
        {
            case 1:
                ajouterTache();
                break;
            case 2:
                modifierTache();
                break;
            case 3:
                supprimerTache();
                break;
            case 4:
                afficherTaches();
                break;
            case 5:
                rechercher();
                break;
            case 6:
                statistiques();
                break;
            case 7:
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    }
}

int afficherTaches() 
{
    int choixTri;
    printf("\n Vous souhaitez afficher les tâches en : \n"
           "\n 1- Triant par ordre alphabétique\n "
           "\n 2- Triant par date limite '<'\n "
           "\n 3- Afficher les tâches dont la date limite est dans 3 jours ou moins \n");
    printf(" 4: Retour\n");
    scanf("%d", &choixTri);

    switch (choixTri) 
    {
        case 1:
            triAlphabetique();
            break;
        case 2:
            triDeadline();
            break;
        case 3:
            joursRestants();
            break;
        case 4:
            return 0;
        default:
            printf("Paramètres invalides\n");
            break;
    }
}

void ajouterTache() 
{
    printf("\n AJOUTER UNE TÂCHE\n");

    printf("\nL'ID de cette tâche est : %d\n", numID);
    taches[nombreTaches].id = numID;
    printf("\nEntrez le nom de la tâche :\n");
    scanf(" %[^\n]", taches[nombreTaches].t_nom);

    printf("\nEntrez la description de la tâche :\n");
    scanf(" %[^\n]", taches[nombreTaches].t_desc);

    printf("\nIndiquez une date limite (aaaa-mm-jj) :\n");
    scanf(" %[^\n]", taches[nombreTaches].dateLimite);

    strcpy(taches[nombreTaches].statut, "à faire");

    nombreTaches++;
    numID++;

    printf("Tâche ajoutée avec succès.\n");
}

void modifierTache() 
{
    int targetID;
    printf("Entrez l'ID de la tâche : \n");
    scanf(" %d",&targetID);
    int found = 0;

    for (int i = 0; i < nombreTaches; i++) 
    {
        if (taches[i].id == targetID) 
        {
            printf("\nEntrez une nouvelle description de tâche :\n");
            scanf(" %[^\n]", taches[i].t_desc);

            printf("\nEntrez un nouveau statut (à faire, en cours, termine) :\n");
            scanf(" %[^\n]", taches[i].statut);

            printf("\nEntrez une nouvelle date limite (aaaa-mm-jj) :\n");
            scanf(" %[^\n]", taches[i].dateLimite);

            printf("Modifiée avec succès\n");
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("%d non trouvé\n", targetID);
    }
}

void triAlphabetique() 
{
    struct Tache cmp;
    for (int i = 0; i < nombreTaches - 1; i++) 
    {
        for (int j = nombreTaches - 1; j > i; j--) 
        {
            if (strcmp(taches[j].t_nom, taches[j - 1].t_nom) < 0) 
            {
                cmp = taches[j];
                taches[j] = taches[j - 1];
                taches[j - 1] = cmp;
            }
        }
    }

    for (int i = 0; i < nombreTaches; i++) 
    {
        printf("ID de la tâche : %d\n", taches[i].id);
        printf("Nom de la tâche : %s\n", taches[i].t_nom);
        printf("Description de la tâche : %s\n", taches[i].t_desc);
        printf("Statut de la tâche : %s\n", taches[i].statut);
        printf("Date limite de la tâche : %s\n", taches[i].dateLimite);
        printf("-------------------------------\n");
    }
}

void triDeadline()
{
    struct Tache temp;
    for (int i = 0; i < nombreTaches - 1; i++) 
    {
        for (int j = nombreTaches - 1; j > i; j--) 
        {
            if (strcmp(taches[j].dateLimite, taches[j - 1].dateLimite) < 0) 
            {
                temp = taches[j];
                taches[j] = taches[j - 1];
                taches[j - 1] = temp;
            }
        }
    }
     for (int i = 0; i < nombreTaches; i++) 
    {
        printf("ID de la tâche : %d\n", taches[i].id);
        printf("Nom de la tâche : %s\n", taches[i].t_nom);
        printf("Description de la tâche : %s\n", taches[i].t_desc);
        printf("Statut de la tâche : %s\n", taches[i].statut);
        printf("Date limite de la tâche : %s\n", taches[i].dateLimite);
        printf("-------------------------------\n");
    }
}

void supprimerTache() 
{
    int targetID;
    printf("\nEntrez l'ID à supprimer:\n");
    scanf("%d", &targetID);
    int found = 0;

    for (int i = 0; i < nombreTaches; i++) 
    {
        if (taches[i].id == targetID) 
        {
            found = 1;
            for (int j = i; j < nombreTaches - 1; j++) 
            {
                taches[j] = taches[j + 1];
            }
            nombreTaches--;
            printf("Tâche %d supprimée avec succès\n", targetID);
            break;
        }
    }

    if (!found) 
    {
        printf("%d non trouvé\n", targetID);
    }
}

void joursRestants() 
{ 
    time_t maintenant;
    time(&maintenant);  // Obtenir l'heure actuelle
    struct tm heure_actuelle;
    localtime_r(&maintenant, &heure_actuelle);

    struct tm dateLimitePlus3 = heure_actuelle;
    dateLimitePlus3.tm_mday += 3;
    mktime(&dateLimitePlus3);
    double secondes_restantes;
    int jours_restants;
    struct tm date_limite = {0};

    for (int i = 0; i < nombreTaches; i++) 
    {
        if (sscanf(taches[i].dateLimite, "%4d-%2d-%2d", &date_limite.tm_year, &date_limite.tm_mon, &date_limite.tm_mday) == 3) 
        {
            date_limite.tm_year -= 1900;
            date_limite.tm_mon -= 1;

            time_t tempsTache = mktime(&date_limite);
            secondes_restantes = difftime(tempsTache, maintenant);
            jours_restants = (int)(secondes_restantes / (60 * 60 * 24));

            if (jours_restants >= 0 && jours_restants <= 3) 
            {
                printf("ID de la tâche : %d\n", taches[i].id);
                printf("Nom de la tâche : %s\n", taches[i].t_nom);
                printf("Jours restants : %d\n", jours_restants);
                printf("----------------------------\n");
            }
        }
    }
}

int rechercher()
{
    int choixRecherche;
    printf("\n 1: Rechercher par ID\n");
    printf(" 2: Rechercher par titre\n");
    printf(" 3: Retour\n");
    scanf("%d", &choixRecherche);

    switch (choixRecherche) 
    {
        case 1:
            rechercher_par_id();
            break;
        case 2:
            rechercher_par_nom();
            break;
        case 3:
            return 0;
        default:
            printf("Paramètres invalides\n");
            break;
    }
}

void rechercher_par_id() 
{
    printf("\nRECHERCHER PAR ID\n");
    int id_entre;
    printf("Entrez l'ID : ");
    scanf("%d", &id_entre);

    for (int i = 0; i < nombreTaches; i++) 
    {
        if (taches[i].id == id_entre) 
        {
            printf("Nom de la tâche : %s\n", taches[i].t_nom);
            printf("Description de la tâche : %s\n", taches[i].t_desc);
            printf("Date limite de la tâche : %s\n", taches[i].dateLimite);
            printf("Statut de la tâche : %s\n", taches[i].statut);
            printf("----------------------------\n");
            return;
        }
    }

    printf("%d non trouvé\n", id_entre);
}

void rechercher_par_nom() 
{
    char nom_entre[50];
    printf("\nRECHERCHER PAR NOM\n");
    printf("Entrez le nom de la tâche : ");
    scanf(" %[^\n]", nom_entre);

    for (int i = 0; i < nombreTaches; i++)
    {
        if (strcmp(taches[i].t_nom, nom_entre) == 0)
        {
            printf("Nom de la tâche : %s\n", taches[i].t_nom);
            printf("Description de la tâche : %s\n", taches[i].t_desc);
            printf("Date limite de la tâche : %s\n", taches[i].dateLimite);
            printf("Statut de la tâche : %s\n", taches[i].statut);
            printf("----------------------------\n");
        }
        else
            printf("%s non trouvé \n",nom_entre);
        
    }
}

void statistiques()
{
    int choixStat;
    printf(" 1- Afficher le nombre de tâches totales ,complètes et incomplètes\n"
           " 2- Afficher le nombre de jours restants jusqu'au délai de chaque tâche\n");
    scanf("%d",&choixStat); 

        switch(choixStat)
        {
            case 1:
            nombreTtci();
            break;

            case 2:
            nombreJoursRestant();
            break;
        }   
}
void nombreTtci()
{
    int complete = 0 ,incomplete = 0;
    int i;

    for (int i = 0; i < nombreTaches; i++)
    {
        if (strcmp(taches[i].statut,"termine" ) == 0)
            complete++;
        else
            incomplete++;
    }
    i= complete + incomplete;
    printf("total %d\n",i);
    printf("complete %d\n",complete);
    printf("incomplete %d\n",incomplete);
}

void nombreJoursRestant()
{
    time_t maintenant;
    time(&maintenant);  
    struct tm heure_actuelle;
    localtime_r(&maintenant, &heure_actuelle);

    struct tm dateLimitePlus3 = heure_actuelle;
    dateLimitePlus3.tm_mday += 3;
    mktime(&dateLimitePlus3);
    double secondes_restantes;
    int jours_restants;
    struct tm date_limite = {0};

    for (int i = 0; i < nombreTaches; i++) 
    {
        if (sscanf(taches[i].dateLimite, "%4d-%2d-%2d", &date_limite.tm_year, &date_limite.tm_mon, &date_limite.tm_mday) == 3) 
        {
            date_limite.tm_year -= 1900;
            date_limite.tm_mon -= 1;

            time_t tempsTache = mktime(&date_limite);
            secondes_restantes = difftime(tempsTache, maintenant);
            jours_restants = (int)(secondes_restantes / (60 * 60 * 24));
             if (jours_restants >= 0 ) 
            {
                printf("ID de la tâche : %d\n", taches[i].id);
                printf("Nom de la tâche : %s\n", taches[i].t_nom);
                printf("Jours restants : %d\n", jours_restants);
                printf("----------------------------\n");
            }

    }
}



}

