#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure représentant une tâche
struct User
{
    int id;                 // Identifiant unique de la tâche
    char titre[200];        // Titre de la tâche
    char description[300];  // Description de la tâche
    char Due_date[16];      // Date d'échéance de la tâche (format MM-DD-YYYY)
    char priority[50];      // Priorité de la tâche (high/low)
};

// Fonction pour créer une nouvelle tâche
void create(struct User *u, int id)
{
    int month, day, year;

    u->id = id ;  // Affecte l'ID à la tâche
    printf("\n______________________________\n");
    printf("Entrer le titre : ");
    scanf(" %[^\n]", u->titre);  // Saisie du titre de la tâche
    printf("Entrer la description : ");
    scanf(" %[^\n]", u->description);  // Saisie de la description de la tâche

    // Saisie et validation de la date d'échéance
    while (1)
    {
        printf("Enter the date ([MM-DD-YYYY]): ");
        scanf("%10s", u->Due_date);

        // Vérification du format de la date
        if (sscanf(u->Due_date, "%2d-%2d-%4d", &month, &day, &year) != 3 ||
            month < 1 || month > 12 ||
            day < 1 || day > 31 ||
            year < 2024 || year > 2040)
        {
            printf("\nInvalid format. Please enter the date in MM-DD-YYYY format.\n");
        }
        else break;  // Si la date est valide, on sort de la boucle
    }

    // Saisie et validation de la priorité
    while (1)
    {
        printf("Entrer la priorite (high/low): ");
        scanf("%s", u->priority);

        // Vérification si la priorité est 'high' ou 'low'
        if (strcmp(u->priority, "high") == 0 || strcmp(u->priority, "low") == 0)
        {
            break;  // Si la priorité est valide, on sort de la boucle
        }
        else
        {
            printf("Invalide entrer, veuillez entrer 'high' ou 'low'.\n");
        }
    }

    printf("\n________________________________________________________\n");
}

// Fonction pour afficher les détails d'une tâche
void display(struct User u)
{
    if (u.id != 0)  // Si l'ID est non nul, la tâche existe
    {
        printf("\nVotre information :\n ");
        printf("ID : %d\ntitre : %s\ndescription : %s\ndate d'echeance : %s\npriorite : %s",
               u.id, u.titre, u.description, u.Due_date, u.priority);
        printf("\n________________________________________________________\n");
    }
    else
    {
        printf("Aucune tache\n");  // Si l'ID est nul, il n'y a pas de tâche à afficher
    }
}

// Fonction pour modifier une tâche existante
void update(struct User *u, int field, char nv[])
{
    switch (field)
    {
    case 1:
        strcpy(u->description, nv);  // Modifie la description
        break;
    case 2:
        strcpy(u->Due_date, nv);  // Modifie la date d'échéance
        break;
    case 3:
        strcpy(u->priority, nv);  // Modifie la priorité
        break;
    default:
        printf("votre choix est incorrect\n");  // Si le champ est invalide
        break;
    }
}

// Fonction pour supprimer une tâche
void delete(struct User *u)
{
    u->id = 0;  // Réinitialise l'ID de la tâche à 0 (la tâche est supprimée)
    
    printf("Tache supprimee avec succes\n");
}

// Fonction pour filtrer les tâches en fonction de la priorité (high/low)
void filter(struct User u[], int id, char fp[])
{
    int found = 0;  // Variable pour vérifier si une tâche avec la priorité donnée est trouvée
    for (int i = 0; i < id; i++)
    {
        if (strcmp(u[i].priority, fp) == 0)  // Si la priorité correspond
        {
            display(u[i]);  // Affiche la tâche
            found = 1;  // Indique qu'une tâche a été trouvée
        }
    }
    if (!found)
    {
        printf("Non trouvée ...\n");  // Si aucune tâche avec la priorité donnée n'est trouvée
    }
}

int main()
{
    struct User u[MAX] = {0};  // Tableau pour stocker les tâches
    int id = 0;  // Compteur pour l'ID des tâches
    int choix, id_deleted;
    char fp[100];

    do
    {
        // Menu principal
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
                create(&u[id], id + 1);  // Appel de la fonction pour créer une tâche
                id++;  // Incrémente l'ID pour la prochaine tâche
            }
            else
            {
                printf("Nombre maximum des taches atteint\n");  // Si le nombre de tâches atteint la limite
            }
            break;
        case 2:
            for (int i = 0; i < id; i++)
            {
                display(u[i]);  // Affiche toutes les tâches existantes
            }
            break;
        case 3:
        {
            int update_id, field;
            char nv[200];

            printf("Entrer l'ID de la tache pour mise a jour : ");
            scanf("%d", &update_id);

            if (update_id > id || update_id < 1)
            {
                printf("ID incorrect\n");  // Si l'ID est invalide
            }
            else
            {
                printf("<< Saisissez le choix que vous souhaitez modifier >>");
                printf("\n1.description\n2.la date d'echeance\n3.la priorite.");
                scanf("%d", &field);
                printf("Entrer la nouvelle valeur : ");
                scanf(" %[^\n]", nv);

                update(&u[update_id - 1], field, nv);  // Appel de la fonction pour mettre à jour la tâche
            }
            break;
        }
        case 4:
        {
            printf("Entrer l'ID de la tache à supprimer : ");
            scanf("%d", &id_deleted);
            if (id_deleted <= id && id_deleted >= 1)
            {
                delete(&u[id_deleted - 1]);  // Appel de la fonction pour supprimer la tâche
            }
            else
            {
                printf("ID incorrect\n");  // Si l'ID est invalide
            }
            break;
        }
        case 5:
        {
            printf("Entrer la priorité pour filtrer (high/low) : ");
            scanf("%s", fp);
            filter(u, id, fp);  // Appel de la fonction pour filtrer les tâches par priorité
            break;
        }
        default:
            printf("Choix invalide, veuillez réessayer...\n");  // Si l'option entrée est invalide
            break;
        }
    } while (choix != 0);  // Répète tant que l'utilisateur ne choisit pas de quitter

    return 0;
}
