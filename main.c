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
    int month, day, year;

    u->id = id ;
    printf("\n______________________________\n");
    printf("entrer le titre : ");
    scanf(" %[^\n]", u->titre);
    printf("entrer la description : ");
    scanf(" %[^\n]", u->description);

    while (1)
    {
        printf("Enter the date ([MM-DD-YYYY]): ");
        scanf("%10s", u->Due_date);

        if (sscanf(u->Due_date, "%2d-%2d-%4d", &month, &day, &year) != 3 ||
            month < 1 || month > 12 ||
            day < 1 || day > 31 ||
            year < 2024 || year > 2040)
        {
            printf("\nInvalid format. Please enter the date in MM-DD-YYYY format.\n");
        }
        else break;
        
    }

    while (1)
    {
        printf("Entrer la priorite (high/low): ");
        scanf("%s", u->priority);

        if (strcmp(u->priority, "high") == 0 || strcmp(u->priority, "low") == 0)
        {
            break;
        }
        else
        {
            printf("Invalide entrer, veuillez entrer 'high' ou 'low'.\n");
        }
    }

    printf("\n________________________________________________________\n");
}

void display(struct User u)
{
    if (u.id != 0)
    {
        printf("\nVotre information :\n ");
        printf("ID : %d\ntitre : %s\ndescription : %s\ndate d'echeance : %s\npriorite : %s",
               u.id, u.titre, u.description, u.Due_date, u.priority);
        printf("\n________________________________________________________\n");
    }
    else
    {
        printf("Aucune tâche\n");
    }
}

void update(struct User *u, int field, char nv[])
{
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
        printf("votre choix est incorrect\n");
        break;
    }
}

void delete(struct User *u)
{
    u->id = 0;
    
    printf("Tache supprimee avec succes\n");
}

void filter(struct User u[], int id, char fp[])
{
    int found = 0;
    for (int i = 0; i < id; i++)
    {
        if (strcmp(u[i].priority, fp) == 0)
        {
            display(u[i]);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Non trouvée ...\n");
    }
}

int main()
{
    struct User u[MAX] = {0};
    int id = 0;
    int choix, id_deleted;
    char fp[100];

    do
    {
        printf("\n<<  Menu  >>\n1. Ajouter\n2. Afficher\n3. Modifier\n4. Supprimer\n5. Filtrer\n0. Exit\n");
        scanf("%d", &choix);
        printf("\n________________________________________________________\n");

        switch (choix)
        {
        case 0:
            break;
        case 1:
            if (id < MAX)
            {
                create(&u[id], id + 1);
                id++;
            }
            else
            {
                printf("Nombre maximum des tâches atteint\n");
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
            char nv[200];

            printf("Entrer l'ID de la tâche pour mise à jour : ");
            scanf("%d", &update_id);

            if (update_id > id || update_id < 1)
            {
                printf("ID incorrect\n");
            }
            else
            {
                printf("<< Saisissez le choix que vous souhaitez modifier >>");
                printf("\n1.description\n2.la date d'echeance\n3.la priorite.");
                scanf("%d", &field);
                printf("Entrer la nouvelle valeur : ");
                scanf(" %[^\n]", nv);

                update(&u[update_id - 1], field, nv);
            }
            break;
        }
        case 4:
        {
            printf("Entrer l'ID de la tâche à supprimer : ");
            scanf("%d", &id_deleted);
            if (id_deleted <= id && id_deleted >= 1)
            {
                delete(&u[id_deleted - 1]);
            }
            else
            {
                printf("ID incorrect\n");
            }
            break;
        }
        case 5:
        {
            printf("Entrer la priorité pour filtrer (high/low) : ");
            scanf("%s", fp);
            filter(u, id, fp);
            break;
        }
        default:
            printf("Choix invalide, veuillez réessayer...\n");
            break;
        }
    } while (choix != 0);

    return 0;
}
