#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct User {
    int id;
    char titre[200];
    char description[300];
    char Due_date[16];
    char priority[10]; 
};

void create(struct User *u, int id) {
    u->id = id;
    printf("\n______________________________\n");
    printf("Enter the title: ");
    scanf("%s", u->titre);

    printf("Enter the description: ");
    scanf("%s", u->description);

    printf("Enter the due date (MM/DD/YYYY): ");
    scanf("%s", u->Due_date);

    while (strcmp(u->priority, "high") != 0 && strcmp(u->priority, "low") != 0) {
        printf("Enter the priority (high/low): ");
        scanf("%s", u->priority);

        if (strcmp(u->priority, "high") == 0) {
            printf("Priority is high.\n");
        } else if (strcmp(u->priority, "low") == 0) {
            printf("Priority is low.\n");
        } else {
            printf("Invalid input.\n");
            strcpy(u->priority, "");  
        }
    }
    printf("\n______________________________\n");
}

void display(struct User u) {
    if (u.id != 0) {
        printf("Your task information:\n");
        printf("Title: %s\nDescription: %s\nDue date: %s\nPriority: %s\n",
               u.titre, u.description, u.Due_date, u.priority);
    } else {
        printf("No task available.\n");
    }
}

void update(struct User *u, int field, char nv[]) {
    printf("Modify a task: ");
    printf("1. Description\n2. Due date\n3. Priority\n0. Exit\n");

    switch (field) {
        case 0:
            printf("Exiting update...\n");
            break;
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
            printf("Invalid choice.\n");
            break;
    }
}

void delete(struct User *u) {
    u->id = 0;
    strcpy(u->titre, "");
    strcpy(u->description, "");
    strcpy(u->Due_date, "");
    strcpy(u->priority, "");
    printf("Task deleted successfully.\n");
}

void filtered(struct User *u) {
    // This function is currently empty.
}

int main() {
    struct User u[MAX] = {0};
    int id = 0;
    int choix;

    do {
        printf("\n<<  Menu  >>\n1. Add\n2. Display\n3. Update\n4. Delete\n5. Filter\n0. Exit\n");
        scanf("%d", &choix);
        printf("\n___________________________________________________________________________\n");

        switch (choix) {
            case 1:
                if (id < MAX) {
                    create(&u[id], id + 1);
                    id++;
                } else {
                    printf("Maximum task limit reached.\n");
                }
                break;

            case 2:
                for (int i = 0; i < id; i++) {
                    display(u[i]);
                }
                break;

            case 3: {
                int update_id, field;
                char nv[200];

                printf("Enter the task ID to update: ");
                scanf("%d", &update_id);

                if (id < update_id || update_id < 1) {
                    printf("Invalid task ID.\n");
                } else {
                    printf("<< Select the field you want to modify >>\n");
                    printf("1. Description\n2. Due date\n3. Priority\n");
                    scanf("%d", &field);
                    printf("Enter the new value: ");
                    scanf("%s", nv);

                    update(&u[update_id - 1], field, nv);
                }
                break;
            }

            case 4: {
                int delete_id;
                printf("Enter the task ID to delete: ");
                scanf("%d", &delete_id);

                if (delete_id < 1 || delete_id > id) {
                    printf("Invalid task ID.\n");
                } else {
                    delete(&u[delete_id - 1]);
                }
                break;
            }

            case 5:
                filtered(u);
                break;

            default:
                break;
        }
    } while (choix != 0);

    return 0;
}
