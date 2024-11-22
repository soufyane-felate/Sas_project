#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#define MAX 100


struct User
{
    int id;
    char titre[200];
    char description[300];
    char Due_date[16];
    char priority[50];
};

void creaet(struct User *u,int id){

    int cp;                             //choix priority
    u->id=id;
    printf("\n______________________________\n");
    printf("entrer le titre : ");
    scanf("%s",u->titre);
    
    printf("entrer la description : ");
    scanf("%s",u->description);
    

   
    printf("entrer la date (MM-DD-YYYY) : ");
    scanf("%s",u->Due_date);
   
   
    while (1) {
        printf("Entrer la the priorite (1. high, 2. low): ");
        scanf("%s", u->priority);

        // Verifiez si la priorite saisie est « low » ou « high »
        if (strcmp(u->priority, "high") == 0 || strcmp(u->priority, "low") == 0) {
            break;                   //Entree valide, quitter la boucle
        } else {
            printf("Invalide entrer, veuillez entrer'high' ou 'low'.\n");
        }
    }
   // scanf("%s",u->priority);
    
    printf("\n________________________________________________________\n");
}

void display(struct User u){
    if (u.id!=0)
    {
    printf("\nVotre information :\n ");
    printf("ID : %d\ntitre : %s\ndescription : %s\ndate d'echeance : %s\npriorite : %s",
    u.id,u.titre,u.description,u.Due_date,u.priority
  );
    printf("\n________________________________________________________\n");
    }else printf("accun");
}
void update(struct User *u,int field,char nv[]){
    printf(" Modifier une Tache : ");
    printf("1.description\n2.la date d'echeance\n3.la priorite\n0.Exist");
    switch (field)
    {
    case 0:
    printf("Fin de programme...");
    break;
    case 1:
        strcpy(u->description,nv);
        break;
    case 2:
        strcpy(u->Due_date,nv);
        break;
    case 3:
         strcpy(u->priority,nv);
         break;
    default:
    printf("votre choix est incorrect\n ");
        break;
    }
}
void delete(struct User *u){
    u->id = 0;
    strcpy(u->titre,"");
    strcpy(u->description,"");
    strcpy(u->Due_date,"");
    strcpy(u->priority,"");
    printf("supprimer le succes");
}

void filtered(struct User u[],char fp[]){
   if (strcmp(u->priority,fp)==0)
   {
     printf("\nVotre information :\n ");
    printf("ID : %d\ntitre : %s\ndescription : %s\ndate d'echeance : %s\npriorite : %s\n",
    u->id,u->titre,u->description,u->Due_date,u->priority);
   }
   else printf("non trouver ...\n");
   
}


int main(){
    struct User u[MAX]={0};
    int id=0;
    int choix,id_deleted;
    char fp[100];

    do
    {
    printf("\n<<  Menu  >>\n1.Ajouter\n2.afficher\n3.modifier\n4.suprimer\n5.filtrer\n0.Exist\n");
    scanf("%d",&choix);
    printf("\n________________________________________________________\n");
        switch (choix)
        {
        case 1:
           if (id<MAX)
           {
                creaet(&u[id],id + 1);
                id++;
            break;
           }else
                printf("Nombre maximum des taches atteint\n");
        break;  
        case 2:
            for (int i = 0; i < id; i++)
            {
                display(u[i]);
            }
        break;
        case 3:
            {
            int update_id,field;
            char nv[200];
            
                printf("Entrer l'ID de la tache pour mise a jour : ");
                scanf("%d",&update_id);

       if (id<update_id||update_id<1)
       {
                printf("votre choix est incorrect ");

       }
       else
       {                 
                printf("<< Saisissez le choix que vous souhaitez modifier>>");
                printf("\n1.description\n2.la date d'echeance\n3.la priorite.");
                scanf("%s",&field);
                printf("Entrer la nouvelle valeur : ");
                scanf("%s",nv);

                update(&u[update_id-1],field,nv);


       }
            }
        break;
        case 4:
        {
            printf("Entrer id que vous voulez suprimer : ");
            scanf("%d",&id_deleted);
            if (id_deleted>1||id>id_deleted)
            {
                delete(&u[id_deleted-1]);
            }else{
                printf("Invalid ID");
            }
            


            break;
        }
        case 5:
          {
            printf("entrer le mot cle : ");
            scanf("%s",&fp);

            for (int i = 0; i < id; i++)
            {
                filtered(&u[i],fp);
             
            }
        break;
        
        

        }
        
        default:
        printf("Choix invalide, veuillez reessayer...");                                 //message si votre choix est incorrect
            break;
        }
    } while (choix!=0);
    return 0;
    

}