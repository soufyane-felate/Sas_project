#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct User
{
    int id;
    char titre[200];
    char description[300];
    char Due_date[16];
    char priority[50];
};

void create(struct User *u, int id)
{
    u->id = id;
    printf("\n______________________________\n");
    printf("Entrer le titre : ");
    scanf(" %s", u->titre); // read string with spaces

    printf("Entrer la description : ");
    scanf(" %s", u->description);

    printf("Entrer la date (MM/DD/YYYY) : ");
    scanf(" %s", u->Due_date);

    printf("Entrer la priorité (1.high, 2.low): ");
    scanf(" %s", u->priority);

    printf("\n______________________________\n");
}

void display(struct User u)
{
    if (u.id != 0)
    {
        printf("\nID: %d\nTitre: %s\nDescription: %s\nDate d'échéance: %s\nPriorité: %s\n",
               u.id, u.titre, u.description, u.Due_date, u.priority);
    }
    else
    {
        printf("Aucune tâche\n");
    }
}

void update(struct User *u, int field, char nv[])
{
    printf("Modifier une Tâche : ");
    switch (field)
    {
    case 1:
        strcpy(u->description, nv);
        break;
    case 2:
        strcpy(u->Due_date, nv);
        break;
    case 3:
        strcpy(u->priority, nv);
        break;
    default:
        printf("Votre choix est incorrect\n");
        break;
    }
}

void delete(struct User *u)
{
    u->id = 0;
    strcpy(u->titre, "");
    strcpy(u->description, "");
    strcpy(u->Due_date, "");
    strcpy(u->priority, "");
    printf("Tâche supprimée avec succès\n");
}

int main()
{
    struct User u[MAX] = {0};
    int id = 0;
    int choix;

    do
    {
        printf("\n<< Menu >>\n1. Ajouter\n2. Afficher\n3. Modifier\n4. Supprimer\n5. Filtrer\n0. Exit\n");
        scanf("%d", &choix);
        printf("\n___________________________________________________________________________\n");

        switch (choix)
        {
        case 1:
            if (id < MAX)
            {
                create(&u[id], id + 1);
                id++;
            }
            else
            {
                printf("Nombre maximum de tâches atteint\n");
            }
            break;
        case 2:
            for (int i = 0; i < id; i++)
            {
                display(u[i]);
            }
            break;
        case 3:
        {
            int update_id, field;
            char nv[300];
            printf("Entrer l'ID de la tâche pour mise à jour : ");
            scanf("%d", &update_id);

            if (update_id < 1 || update_id > id)
            {
                printf("ID incorrect\n");
            }
            else
            {
                printf("<< Saisissez le choix que vous souhaitez modifier >>");
                printf("\n1. Description\n2. Date d'échéance\n3. Priorité\n");
                scanf("%d", &field);
                printf("Entrer la nouvelle valeur : ");
                scanf(" %s", nv); 

                update(&u[update_id - 1], field, nv);
            }
            break;
        }
        case 4:
        {
            int delete_id;
            printf("Entrer l'ID de la tâche à supprimer : ");
            scanf("%d", &delete_id);

            if (delete_id < 1 || delete_id > id)
            {
                printf("ID incorrect\n");
            }
            else
            {
                delete(&u[delete_id - 1]);
            }
            break;
        }
        case 0:
            printf("Fin du programme...\n");
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    } while (choix != 0);

    return 0;
}
