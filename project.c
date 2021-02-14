//ROOMS FOR RENT 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 256

typedef struct os
{
    char tenant_name[MAX]; //FULL NAME of tenant
    char first_name[MAX];
    char last_name[MAX];
    char mobile_number[12];
    struct os * down;   //forward
    struct os * up;     //backward

} occupant;

typedef struct ut
{
    char unit_name[MAX];
    int max_occupants;
    int num_occupants; //current number of occupants.
    struct ut * next;
    struct ut * prev;
    struct os * members_list;

} unit;

//STRING MANIPULATION FUNCTIONS
void lowercase_string(char * string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
}

void uppercase_string(char * string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = toupper(string[i]);
    }  
}

//DEBUG FUNCTIONS
void print_all_units(unit * head)
{
    unit * temp = head;
    char uppercase_unit[MAX];
    while (temp->next != head) 
    { 
        strcpy(uppercase_unit, temp->unit_name);
        uppercase_string(uppercase_unit);
        printf("Unit Name: %s\n", uppercase_unit); 
        printf("Number of Occupants: %d\n", temp->num_occupants);
        printf("\n");
        temp = temp->next; 
    } 
    strcpy(uppercase_unit, temp->unit_name);
    uppercase_string(uppercase_unit);
    printf("Unit Name: %s\n", uppercase_unit); 
    printf("Number of Occupants: %d\n", temp->num_occupants);
    printf("\n");
}

void print_all_tenants(unit * head)
{
    char uppercase_unit[MAX];
    char uppercase_tenant[MAX];

    unit * temp = head; 
    occupant * ocpt_head = temp->members_list;   
  
    while (temp->next != head) 
    { 
        strcpy(uppercase_unit, temp->unit_name);
        uppercase_string(uppercase_unit);
        printf("Unit Name: %s\n", uppercase_unit);
        printf("Number of Occupants: %d\n", temp->num_occupants);

        if(ocpt_head != NULL)
        {
            while(ocpt_head->down != temp->members_list)
            {
                strcpy(uppercase_tenant, ocpt_head->tenant_name);
                uppercase_string(uppercase_tenant);
                printf("\tTenant: %s \tMobile Number: %s\n",uppercase_tenant, ocpt_head->mobile_number);
                ocpt_head = ocpt_head->down;
            }

            strcpy(uppercase_tenant, ocpt_head->tenant_name);
            uppercase_string(uppercase_tenant);
            printf("\tTenant: %s \tMobile Number: %s\n",uppercase_tenant, ocpt_head->mobile_number);  
        }
        else
        {
            printf("\tNo tenants!\n");
        }

        temp = temp->next;
        ocpt_head = temp->members_list; 
        printf("\n");
    } 

    strcpy(uppercase_unit, temp->unit_name);
    uppercase_string(uppercase_unit);
    printf("Unit Name: %s\n", uppercase_unit);
    printf("Number of Occupants: %d\n", temp->num_occupants);

    if(ocpt_head != NULL)
    {
        while(ocpt_head->down != temp->members_list)
        {
            strcpy(uppercase_tenant, ocpt_head->tenant_name);
            uppercase_string(uppercase_tenant);
            printf("\tTenant: %s \tMobile Number: %s\n",uppercase_tenant, ocpt_head->mobile_number);
            ocpt_head = ocpt_head->down;
        }
         
        strcpy(uppercase_tenant, ocpt_head->tenant_name);
        uppercase_string(uppercase_tenant);
        printf("\tTenant: %s \tMobile Number: %s\n",uppercase_tenant, ocpt_head->mobile_number);
    }
    
    else
    {
        printf("\tNo tenants!\n");
    } 

    printf("\n");
}

int check_if_atleast_one_tenant_exists(unit ** head)
{
    unit * temp = (*head); 
    occupant * ocpt_head = temp->members_list;   
  
    while (temp->next != (*head)) 
    { 
        if(ocpt_head != NULL)
        {
            return 1;
        }

        temp = temp -> next;
        ocpt_head = temp->members_list;

    } 

    if(ocpt_head != NULL)
    {
        return 1;
    }

    return 0;

}

//MENU FUNCTIONS
void menu()
{
	printf("\n[1] Add Unit\n");
	printf("[2] Add Tenant\n");
	printf("[3] Search Tenant\n");
	printf("[4] Move Tenant\n");
	printf("[5] Remove Tenant\n");
	printf("[6] Edit Tenant\n");
	printf("[7] Print Master List Of Occupants\n");
	printf("[8] Print List Of Occupants Per Unit\n");
	printf("[9] Remove Unit\n");
	printf("[0] Exit\n\n");
}

int choose_option(int option)
{
	printf("Enter choice: ");
	scanf("%d", &option);
    printf("\n");
	return option;
}

//SUB FUNCTIONS
void enter_mobile_number(occupant ** new_occupant)
{
    int validmobilenumber = 1;
    
    //Ask for mobile number
    char tempmobilenumber[12];
    printf("Enter mobile number: ");
    scanf("%s", tempmobilenumber);
    
    //Check if the input is exclusively numeric characters
    for(int i = 0; i < strlen(tempmobilenumber); i++)
    {
        if(isdigit(tempmobilenumber[i])==0)
        {
            validmobilenumber = 0;
        }
    }

    //Check if the number is exactly size 11
    if(strlen(tempmobilenumber)<11)
    {
        validmobilenumber = 0;
    }

    if(validmobilenumber == 1)
    {
        strcpy((*new_occupant)->mobile_number,tempmobilenumber);
    }

    else
    {
        printf("Not a valid mobile number\n\n");
        enter_mobile_number(new_occupant);
    }
}

void check_if_duplicate_unit(unit ** current_unit, char * lowercase_new_unit_name, char * lowercase_old_unit_name, int * duplicate_unit_name)
{
    strcpy(lowercase_old_unit_name, (*current_unit)->unit_name);
    printf("%s lower_case_old_unit_name :: %s lowercase_new_unit_name\n",lowercase_old_unit_name, lowercase_new_unit_name);

    if(strcmp(lowercase_new_unit_name, lowercase_old_unit_name)== 0)
    {
        (*duplicate_unit_name) = 1;
        printf("The unit name already exists!\n");
    }
}

void check_if_duplicate_tenant(occupant ** current_tenant, char * lowercase_new_tenant_name, char * lowercase_old_tenant_name, int * duplicate_tenant_name)
{
    strcpy(lowercase_old_tenant_name, (*current_tenant)->tenant_name);
    printf("%s is your lowercase_old_tenant_name.\n",lowercase_old_tenant_name);
    printf("%s is your lowercase_new_tenant_name.\n",lowercase_new_tenant_name);

    if(strcmp(lowercase_new_tenant_name, lowercase_old_tenant_name)== 0)
    {
        (*duplicate_tenant_name) = 1;
        printf("The tenant name already exists!\n");
    }
}

unit * find_unit(unit ** head, unit ** forward, unit ** backward)
{
    char unit_name_to_search[MAX];
    char lowercase_old_unit_name[MAX];

    (*forward) = (*head);
    printf("%s :: forward->unit_name\n", (*forward)->unit_name);
    (*backward) = (*head)->prev;
    printf("%s :: backward->unit_name\n", (*backward)->unit_name);

    //Specifiy the unit_name by asking the user and convert it to lowercase form
    printf("Enter desired unit name: ");
    scanf(" %[^\n]s", unit_name_to_search);
    lowercase_string(unit_name_to_search);

    //Traverse the list
    //Case 1 
    strcpy(lowercase_old_unit_name, (*backward)->unit_name); 
    lowercase_string(lowercase_old_unit_name);

    if(strcmp(lowercase_old_unit_name, unit_name_to_search) == 0)
    {
        (*forward) = (*backward);
        (*backward) = NULL;
        return (*forward);
    }
    else
    {   
        //Case 2
        while((*forward)->next != (*head))
        {
            strcpy(lowercase_old_unit_name, (*forward)->unit_name);
            lowercase_string(lowercase_old_unit_name);

            if(strcmp(lowercase_old_unit_name, unit_name_to_search) == 0)
            {
                (*backward) = NULL;
                return (*forward);
                break;
            }

            (*forward) = (*forward)->next;
        }
    }
    return NULL;
}

occupant * find_tenant(unit ** head, int * duplicate_occupant_name, occupant ** new_occupant)
{
    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];

    unit * forward_unit = NULL;
    occupant * ocpt_head = NULL;
    occupant * forward_down = NULL;
    forward_unit = (*head);

    //lower_new_unit_name is the string to check if it is a duplicate
    strcpy(lowercase_new_tenant_name, (*new_occupant)->tenant_name);

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //if there is only a single unit
    if(forward_unit->prev == (*head) && forward_unit->prev->members_list != NULL)
    {
        if(forward_down->down == ocpt_head) //only single tenant
        {
            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
            if((*duplicate_occupant_name) == 1)
            {
                printf("BOOMBAYAH.\n");
                printf("Tenant already exists.\n");
                return ocpt_head;
            }    
        }
        
        else //multiple tenants
        {
            while(forward_down->down != ocpt_head)
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);

                if(forward_down->down == ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
                    if((*duplicate_occupant_name) == 1)
                    {
                        printf("BOOMBAYAH1.\n");
                        printf("Tenant already exists.\n");
                        return ocpt_head;
                        break;
                    }
                }

                if((*duplicate_occupant_name) == 1)
                {
                    printf("BOOMBAYAH3.\n");
                    printf("Tenant already exists.\n");
                    return forward_down;
                    break;
                }

                forward_down = forward_down->down;
            }

            check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);

            if((*duplicate_occupant_name) == 1)
            {
                printf("BOOMBAYAH11.\n");
                printf("Tenant already exists.\n");
                return forward_down;
            }

        } 
    }

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    while(forward_unit->next != (*head)) //multiple units
    {
        if(forward_unit->members_list != NULL)
        {
            if(forward_down->down == ocpt_head)//single tenant
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
                if((*duplicate_occupant_name) == 1)
                {
                    printf("BOOMBAYAH4.\n");
                    printf("Tenant already exists.\n");
                    return ocpt_head;
                    break;
                }    
            }
            
            else //multiple tenants
            {
                while(forward_down->down != ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);

                    if(forward_down->down == ocpt_head)
                    {
                        check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
                        if((*duplicate_occupant_name) == 1)
                        {
                            printf("BOOMBAYAH5.\n");
                            printf("Tenant already exists.\n");
                            return ocpt_head;
                            break;
                        }
                    }

                    if((*duplicate_occupant_name) == 1)
                    {
                        printf("BOOMBAYAH6.\n");
                        printf("Tenant already exists.\n");
                        return forward_down;
                        break;
                    }

                    forward_down = forward_down->down;
                }

                    check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
                    
                    if((*duplicate_occupant_name) == 1)
                    {
                        printf("BOOMBAYAH7.\n");
                        printf("Tenant already exists.\n");
                        return forward_down;
                    }               
            }
        }
        forward_unit = forward_unit->next;
        ocpt_head = forward_unit->members_list;
        forward_down = ocpt_head;
    }

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //Check forward_unit->prev or the tail of the unit list 
    if(forward_unit->prev->members_list != NULL && (*duplicate_occupant_name)!= 1)
    {
        ocpt_head = forward_unit->prev->members_list;
        forward_down = ocpt_head;

        if(forward_down->down == ocpt_head) //only single tenant
        {
            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
            if((*duplicate_occupant_name) == 1)
            {
                printf("BOOMBAYAH20.\n");
                printf("Tenant already exists.\n");
                return ocpt_head;
            }    
        }
        
        else //multiple tenants
        {
            while(forward_down->down != ocpt_head)
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);

                if(forward_down->down == ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);
                    if((*duplicate_occupant_name) == 1)
                    {
                        printf("BOOMBAYAH21.\n");
                        printf("Tenant already exists.\n");
                        return ocpt_head;
                        break;
                    }
                }

                if((*duplicate_occupant_name) == 1)
                {
                    printf("BOOMBAYAH23.\n");
                    printf("Tenant already exists.\n");
                    return forward_down;
                    break;
                }

                forward_down = forward_down->down;
            }

            check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, duplicate_occupant_name);

            if((*duplicate_occupant_name) == 1)
            {
                printf("BOOMBAYAH24.\n");
                printf("Tenant already exists.\n");
                return forward_down;
            }

        }
    }

    return NULL;
}

void create_new_unit(unit ** new_unit)
{
    //Create new node
    (*new_unit) = (unit*)malloc(sizeof(unit));

    //Initialize new_unit members
    (*new_unit)->max_occupants = 0;
    (*new_unit)->num_occupants = 0;
    (*new_unit)->members_list = NULL;

    //Ask for the unit name
    printf("Enter unit name: ");
    scanf(" %[^\n]s", (*new_unit)->unit_name);
    lowercase_string((*new_unit)->unit_name);

    //Ask for maximum occupants
    printf("Enter maximum occupants: ");
    scanf("%d", &((*new_unit)->max_occupants));
}

void create_new_occupant(occupant ** new_occupant)
{
    //Create new node
    (*new_occupant) = (occupant*)malloc(sizeof(occupant));

    //Initialize new_occupant members
    (*new_occupant)-> down = NULL;
    (*new_occupant)-> up = NULL;

    //Ask for the first and last name
    printf("Enter first name of the new tenant: ");
    scanf(" %[^\n]s", (*new_occupant)->first_name);
    lowercase_string((*new_occupant)->first_name);
    printf("Enter the last name of the new tenant: ");
    scanf(" %[^\n]s", (*new_occupant)->last_name);
    lowercase_string((*new_occupant)->last_name);

    //Ask for mobile number
    enter_mobile_number(new_occupant);

    //Combine last name and first name to get tenant_name
    strcpy((*new_occupant)-> tenant_name, (*new_occupant)-> last_name);
    strcat((*new_occupant)-> tenant_name," ");
    strcat((*new_occupant)-> tenant_name, (*new_occupant)-> first_name);
}

void create_new_occupant_remove_version(occupant ** new_occupant)
{
    //Create new node
    (*new_occupant) = (occupant*)malloc(sizeof(occupant));

    //Initialize new_occupant members
    (*new_occupant)-> down = NULL;
    (*new_occupant)-> up = NULL;

    //Ask for the first and last name
    printf("Enter first name of the new tenant: ");
    scanf(" %[^\n]s", (*new_occupant)->first_name);
    lowercase_string((*new_occupant)->first_name);
    printf("Enter the last name of the new tenant: ");
    scanf(" %[^\n]s", (*new_occupant)->last_name);
    lowercase_string((*new_occupant)->last_name);

    //Combine last name and first name to get tenant_name
    strcpy((*new_occupant)-> tenant_name, (*new_occupant)-> last_name);
    strcat((*new_occupant)-> tenant_name," ");
    strcat((*new_occupant)-> tenant_name, (*new_occupant)-> first_name);
}


void insert_tenant(unit ** forward, occupant ** new_tenant)
{
    //up is backward or left //Change perspective, rotate the linked list
    //down is forward or right
    occupant * occhead = (*forward)->members_list;
    occupant * occforward = occhead;
    // occupant * occbackward = occforward->up; bakit nagsesegfault pag nakaenable yung line na to
    occupant * occtemp = NULL;

    if(occhead == NULL) //If it is an empty list
    {
        (*forward)->members_list = (*new_tenant);
        occhead = (*forward)->members_list;

        (*new_tenant)-> up = (*new_tenant);
        (*new_tenant)-> down = (*new_tenant);

        printf("Tenant: %s is added.\n", occhead->tenant_name);

        (*new_tenant) = NULL;
        free((*new_tenant));
    }

    else
    {
        occtemp = occhead;
        if(occtemp->down == occhead) //If there is only one entry in the list
        {

            if(strcmp((*new_tenant)->tenant_name, occtemp->tenant_name) > -1) //If (*new_tenant)->tenant_name proceeds occtemp->tenant_name, insert (*new_tenant)->tenant_name at the tail.
            {
                (*new_tenant)->down = occhead;
                (*new_tenant)->up = occhead;
                occhead->down = (*new_tenant);
                occhead->up = (*new_tenant);

                printf("Tenant: %s is added.\n", (*new_tenant)->tenant_name);

                (*new_tenant) = NULL;
                free((*new_tenant));
            }

            else //If (*new_tenant)->tenant_name PRECEDES occtemp->tenant_name, insert (*new_tenant)->tenant_name at the occhead.
            {

                (*new_tenant)->down = occhead;
                (*new_tenant)->up = occhead;
                occhead->down = (*new_tenant);
                occhead->up = (*new_tenant);
                (*forward)->members_list = (*new_tenant); //Key difference. The occhead is adjusted.

                printf("Tenant: %s is added.\n", occhead ->tenant_name);

                (*new_tenant) = NULL;
                free((*new_tenant));
            }      
        }   
        
        else //If there is more than one entries in the list
        {
            while(occtemp->down != occhead) //Traverse the list using the occtemp pointer until it reaches occhead
            {
                if(strcmp((*forward)->members_list->tenant_name, (*new_tenant)->tenant_name)>0)  //Case1, if occhead->tenant_name proceeds (*new_tenant)->tenant_name, insert at occhead
                {

                    (*new_tenant)->down = occhead;
                    (*new_tenant)->up = occhead->up;
                    (*new_tenant)->down->up = (*new_tenant);
                    (*forward)->members_list->up = (*new_tenant);
                    (*new_tenant)->up->down = (*new_tenant);

                    (*forward)->members_list = (*new_tenant);

                    printf("Tenant: %s is added.\n", occhead->tenant_name);

                    (*new_tenant) = NULL;
                    occtemp = NULL;
                    free((*new_tenant));
                    free(occtemp);
                    break;
                }

                else if(strcmp(occtemp->down->tenant_name, (*new_tenant)->tenant_name)>0)  //Case2, if occtemp->down proceeds (*new_tenant)->tenant_name, insert at middle
                {

                    (*new_tenant)->down = occtemp->down;
                    (*new_tenant)->up = occtemp;
                    occtemp->down = (*new_tenant);
                    occtemp->down->down->up = (*new_tenant);

                    printf("Tenant: %s is added.\n", (*new_tenant)->tenant_name);

                    (*new_tenant) = NULL;
                    occtemp = NULL;
                    free((*new_tenant));
                    free(occtemp);
                    break;
                } 

                else if(occtemp->down->down == occhead && strcmp(occtemp->down->down->tenant_name, (*new_tenant)->tenant_name)<0) //Case3, if (*new_tenant)->tenant_name proceeds everyone on the list, insert at tail
                {

                    occtemp = occhead->up;
                    (*new_tenant)->down = occhead;
                    (*new_tenant)->up = occtemp;
                    occtemp->down = (*new_tenant);
                    (*forward)->members_list->up = (*new_tenant);

                    printf("Tenant: %s is added.\n", (*new_tenant)->tenant_name);

                    (*new_tenant) = NULL;
                    occtemp = NULL;
                    free((*new_tenant));
                    free(occtemp);
                    break;
                }
                occtemp = occtemp->down;
            }
        }
    }
}

//MAIN FUNCTIONS
void add_unit(unit ** head)
{
    int duplicate_unit_name = -1;
    char lowercase_old_unit_name[MAX];
    char lowercase_new_unit_name[MAX];

    unit * temp = NULL;
    temp = (*head);

    //Create a new node
    unit * new_unit = NULL;
    create_new_unit(&new_unit); 
    strcpy(lowercase_new_unit_name, new_unit->unit_name);

    if((*head)==NULL) //If the list is empty, no units yet.
    {
        (*head) = new_unit;
        (*head)->next = (*head);
        (*head)->prev = (*head);

        (*head) = new_unit;
        new_unit-> prev = new_unit;
        new_unit-> next = new_unit;

        printf("Unit: %s has been added.\n", new_unit->unit_name);

        new_unit = NULL;
        free(new_unit);
    }
    else
    {
        if(temp->next == (*head)) //If there is only one entry in the list
        {
            //Check if the single entry in the list is a duplicate of the new_unit
            check_if_duplicate_unit(head, lowercase_new_unit_name, lowercase_old_unit_name, &duplicate_unit_name);

            if(duplicate_unit_name != 1)
            {
                //Implement sorted insertion
                if(strcmp(new_unit->unit_name, temp->unit_name) > -1) //If new_unit->unit_name proceeds temp->unit_name, insert new_unit->unit_name at the tail.
                {
                    new_unit->next = (*head);
                    new_unit->prev = (*head);
                    (*head)->next = new_unit;
                    (*head)->prev = new_unit;

                    printf("Unit: %s has been added.\n", new_unit->unit_name);

                    new_unit = NULL;
                    free(new_unit);
                }

                else //If new_unit->unit_name PRECEDES temp->unit_name, insert new_unit->unit_name at the head.
                {
                    new_unit->next = (*head);
                    new_unit->prev = (*head);
                    (*head)->next = new_unit;
                    (*head)->prev = new_unit;
                    (*head) = new_unit; //Key difference. The head is adjusted.

                    printf("Unit: %s has been added.\n", new_unit->unit_name);

                    new_unit = NULL;
                    free(new_unit);
                }
            }
        }
        else //If there are more than one entry in the list
        {
            temp = (*head);
            //Check if the entries in the list is a duplicate of the new_unit
            while(temp->next!=(*head) && duplicate_unit_name != 1)
            {
                check_if_duplicate_unit(&temp, lowercase_new_unit_name, lowercase_old_unit_name, &duplicate_unit_name);
                temp = temp->next;
            }

            temp = (*head);
            printf("WEYOPUNATONOMGASHINA.\n");
            check_if_duplicate_unit(&(temp->prev), lowercase_new_unit_name, lowercase_old_unit_name, &duplicate_unit_name);

            if(duplicate_unit_name != 1) //Kung hindi duplicate yung new tenant name
            {
                if(temp->next == (*head)) //If there is only one entry in the list
                {
                    if(strcmp(new_unit->unit_name, temp->unit_name) > -1) //If new_unit->unit_name proceeds temp->unit_name, insert new_unit->unit_name at the tail.
                    {
                        new_unit->next = (*head);
                        new_unit->prev = (*head);
                        (*head)->next = new_unit;
                        (*head)->prev = new_unit;

                        new_unit = NULL;
                        free(new_unit);
                    }

                    else //If new_unit->unit_name PRECEDES temp->unit_name, insert new_unit->unit_name at the head.
                    {
                        new_unit->next = (*head);
                        new_unit->prev = (*head);
                        (*head)->next = new_unit;
                        (*head)->prev = new_unit;
                        (*head) = new_unit; //Key difference. The head is adjusted.

                        new_unit = NULL;
                        free(new_unit);
                    }
                }

                else //If there is more than one entries in the list
                {
                    while(temp->next != (*head)) //Traverse the list using the temp pointer until it reaches (*head)
                    {
                        if(strcmp((*head)->unit_name, new_unit->unit_name)>0)  //Case1, if (*head)->unit_name proceeds new_unit->unit_name, insert at head
                        {
                            new_unit->next = (*head);
                            new_unit->prev = (*head)->prev;
                            new_unit->next->prev = new_unit;
                            (*head)->prev = new_unit;
                            new_unit->prev->next = new_unit;
                            (*head) = new_unit;

                            new_unit = NULL;
                            temp = NULL;
                            free(new_unit);
                            free(temp);
                            break;
                        }

                        else if(strcmp(temp->next->unit_name, new_unit->unit_name)>0)  //Case2, if temp->next proceeds new_unit->unit_name, insert at middle
                        {
                            new_unit->next = temp->next;
                            new_unit->prev = temp;
                            temp->next = new_unit;
                            temp->next->next->prev = new_unit;

                            new_unit = NULL;
                            temp = NULL;
                            free(new_unit);
                            free(temp);
                            break;
                        } 

                        else if(temp->next->next == (*head) && strcmp(temp->next->next->unit_name, new_unit->unit_name)<0) //Case3, if new_unit->unit_name proceeds everyone on the list, insert at tail
                        {
                            temp = (*head)->prev;
                            new_unit->next = (*head);
                            new_unit->prev = temp;
                            temp->next = new_unit;
                            (*head)->prev = new_unit;

                            new_unit = NULL;
                            temp = NULL;
                            free(new_unit);
                            free(temp);
                            break;
                        }
                        temp = temp->next;
                    }
                }
            }  
        }
    } 
}

void add_tenant(unit ** head)
{
    int duplicate_occupant_name = -1;
    unit * forward = NULL;
    unit * backward = NULL;

    //Find the unit_name in which the new tenant will be placed
    find_unit(head, &forward, &backward);
    printf("%s :: backward->unit_name\n", backward->unit_name);

    if(backward != NULL) //If unit_name is not found
    {
        printf("Entered unit name is not found.\n\n");
    }
    else
    {
        printf("[%s] is found.\n\n", forward->unit_name);
        printf("Checking if at maximum capacity...\n\n");
        printf("...\n\n");
        printf("...\n\n");
        printf("...\n\n");

        //Check if specified unit is already at max capacity
        if(forward->max_occupants == forward->num_occupants)
        {
            printf("Can no longer add more tenants, maximum capacity reached.\n\n");
        }

        else
        {
            //Create a new occupant
            occupant * new_occupant = NULL;
            create_new_occupant(&new_occupant);

            //Search if the person is already on the specified unit or another unit
            find_tenant(head, &duplicate_occupant_name, &new_occupant);

            //Sorted insertion of new occupant
            if(duplicate_occupant_name != 1)
            {
                insert_tenant(&forward, &new_occupant);
                forward->num_occupants++; //increase # of occupants
            }
        }

    }   
}

void remove_tenant(unit ** head)
{
    int duplicate_occupant_name = -1;
    int allowremoval = -1;
    char removalchoice[2];
    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];

    unit * forward_unit = NULL;
    occupant * ocpt_head = NULL;
    occupant * forward_down = NULL;

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    
    //Create the tenant to be removed
    occupant * new_occupant = NULL;
    create_new_occupant_remove_version(&new_occupant);

    //lower_new_unit_name is the string to check if it is a duplicate
    strcpy(lowercase_new_tenant_name, new_occupant->tenant_name);


    //find tenant
    //Pag hindi na kita, invalid input ni user
    printf("Are you sure you want to delete this tenant?.\n");
    printf("Yes (Y) | No (N) : ");
    scanf("%s", removalchoice); 
    lowercase_string(removalchoice);

    if(strcmp("y", removalchoice) == 0)
    {
        allowremoval = 1;
    }

    else if (strcmp("n", removalchoice) == 0)
    {
        allowremoval = 0;
    }

    else
    {
        printf("Invalid input!.\n");
    }

    allowremoval = check_if_atleast_one_tenant_exists(head);

    if(allowremoval == 1)
    {
        if(forward_unit->prev == (*head) && forward_unit->members_list != NULL) //if single unit only
        {
            forward_unit = forward_unit->prev;
            ocpt_head = forward_unit->members_list;
            forward_down = ocpt_head;
            printf("%s is forward_down\n",forward_down->tenant_name);

            //if single tenant
            if(forward_down->up == ocpt_head)
            {
                check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1) //remove at head
                {
                    printf("GASHINA!\n");
                    printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                    forward_unit->num_occupants = 0;
                    free(ocpt_head);
                    (*head)->members_list = NULL;
                }
            }

            else
            {
                printf("%s is forward_down\n",forward_down->tenant_name);

                //Check forward_down->up or the tail
                check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1) //delete at tail
                {
                    printf("Tenant %s removed.\n",forward_down->up->tenant_name);
                    (forward_unit->num_occupants)--;
                    forward_down = forward_down -> up;
                    forward_unit->members_list->up = forward_down->up;
                    forward_down->up->down = forward_down->down;
                    forward_down->up = NULL;
                    forward_down->down = NULL;
                    free(forward_down);
                }

                while(forward_down->down != ocpt_head && duplicate_occupant_name != 1)//Since you are finished checking tail, check the rest of the occupant list of the tail of the unit list
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                    if(duplicate_occupant_name == 1)
                    {
                        //remove at head
                        if(forward_down == ocpt_head)
                        {
                            printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                            (forward_unit->num_occupants)--;

                            forward_down->up->down = forward_down->down;
                            forward_down->down->up = forward_down->up;
                            forward_unit->members_list = forward_down->down;

                            forward_down->up = NULL;
                            forward_down->down = NULL;
                            free(forward_down);
                            break;
                        }

                        //remove at middle
                        else
                        {
                            (forward_unit->num_occupants)--;
                            printf("Tenant %s removed.\n",forward_down->tenant_name);

                            forward_down->up->down = forward_down->down;
                            forward_down->down->up = forward_down->up;

                            forward_down->up = NULL;
                            forward_down->down = NULL;
                            free(forward_down);
                            break;
                        }
                        break;
                    }
                    forward_down = forward_down -> down;
                }
            }

        }

        if(duplicate_occupant_name != 1) //if multiple units are present
        {
            forward_unit = forward_unit->prev; //Check first forward_unit-prev
            ocpt_head = forward_unit->members_list;
            forward_down = ocpt_head;

            //if single tenant
            if(forward_down->up == ocpt_head && forward_unit->members_list != NULL)
            {
                check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1) //remove at head
                {
                    printf("GASHINA!\n");
                    printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                    forward_unit->num_occupants = 0;
                    free(ocpt_head);
                    forward_unit->members_list = NULL;
                }
            }

            else
            {
                if(forward_unit->members_list!=NULL)
                {
                    //Check forward_down->up or the tail
                    check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                    if(duplicate_occupant_name == 1) //delete at tail
                    {
                        printf("Tenant %s removed.\n",forward_down->up->tenant_name);
                        (forward_unit->num_occupants)--;
                        forward_down = forward_down -> up;
                        forward_unit->members_list->up = forward_down->up;
                        forward_down->up->down = forward_down->down;
                        forward_down->up = NULL;
                        forward_down->down = NULL;
                        free(forward_down);
                    }
                
                    while(forward_down->down != ocpt_head && duplicate_occupant_name != 1 && forward_unit->members_list != NULL)
                    {
                        check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        if(duplicate_occupant_name == 1)
                        {
                            //remove at head
                            if(forward_down == ocpt_head)
                            {
                                printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                                (forward_unit->num_occupants)--;

                                forward_down->up->down = forward_down->down;
                                forward_down->down->up = forward_down->up;
                                forward_unit->members_list = forward_down->down;

                                forward_down->up = NULL;
                                forward_down->down = NULL;
                                free(forward_down);
                                break;
                            }

                            //remove at middle
                            else
                            {
                                (forward_unit->num_occupants)--;
                                printf("Tenant %s removed.\n",forward_down->tenant_name);

                                forward_down->up->down = forward_down->down;
                                forward_down->down->up = forward_down->up;

                                forward_down->up = NULL;
                                forward_down->down = NULL;
                                free(forward_down);
                                break;
                            }
                            break;
                        }
                        forward_down = forward_down -> down;
                    }
                }

                if(duplicate_occupant_name != 1) //after checking the forward_unit->prev or the tail of the unit list, check the rest of the unit list
                {
                    forward_unit = (*head);
                    ocpt_head = forward_unit->members_list;
                    forward_down = ocpt_head;

                    while(forward_unit->next != (*head) && forward_unit->members_list != NULL)
                    {
                        //if single tenant
                        if(forward_down->up == ocpt_head)
                        {
                            check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                            if(duplicate_occupant_name == 1) //remove at head
                            {
                                printf("GASHINA!\n");
                                printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                                forward_unit->num_occupants = 0;
                                free(ocpt_head);
                                forward_unit->members_list = NULL;
                                break;
                            }
                        }

                        else //if there are multiple tenants
                        {
                            //Check forward_down->up or the tail
                            check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                            if(duplicate_occupant_name == 1) //delete at tail
                            {
                                printf("Tenant %s removed.\n",forward_down->up->tenant_name);
                                (forward_unit->num_occupants)--;
                                forward_down = forward_down -> up;
                                forward_unit->members_list->up = forward_down->up;
                                forward_down->up->down = forward_down->down;
                                forward_down->up = NULL;
                                forward_down->down = NULL;
                                free(forward_down);
                                break;
                            }

                            while(forward_down->down != ocpt_head && duplicate_occupant_name != 1)
                            {
                                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                                if(duplicate_occupant_name == 1)
                                {
                                    //remove at head
                                    if(forward_down == ocpt_head)
                                    {
                                        printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                                        (forward_unit->num_occupants)--;

                                        forward_down->up->down = forward_down->down;
                                        forward_down->down->up = forward_down->up;
                                        forward_unit->members_list = forward_down->down;

                                        forward_down->up = NULL;
                                        forward_down->down = NULL;
                                        free(forward_down);
                                        break;
                                    }

                                    //remove at middle
                                    else
                                    {
                                        (forward_unit->num_occupants)--;
                                        printf("Tenant %s removed.\n",forward_down->tenant_name);

                                        forward_down->up->down = forward_down->down;
                                        forward_down->down->up = forward_down->up;

                                        forward_down->up = NULL;
                                        forward_down->down = NULL;
                                        free(forward_down);
                                        break;
                                    }
                                }
                                
                                forward_down = forward_down -> down;
                            }
                        }

                        forward_unit = forward_unit->next;
                        ocpt_head = forward_unit->members_list;
                        forward_down = ocpt_head;
                    }
                }
            }
        }
    }  

    if(duplicate_occupant_name != 1)
    {
        printf("Occupant name not found.\n");
    }

    //ask kung sure na ba yung user kung tatanggalin niya yung tenant
    //point up and down to NULL
    //point prev down to next
    //bawasan num_occupants by 1
}

void remove_tenant_specific(unit ** head, occupant ** occupant_to_remove)
{
    int duplicate_occupant_name = -1;
    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];

    unit * forward_unit = NULL;
    occupant * ocpt_head = NULL;
    occupant * forward_down = NULL;

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;
    
    //Create the tenant to be removed
    occupant * new_occupant = (*occupant_to_remove);

    //lower_new_unit_name is the string to check if it is a duplicate
    strcpy(lowercase_new_tenant_name, new_occupant->tenant_name);

    if(forward_unit->prev == (*head) && forward_unit->members_list != NULL) //if single unit only
    {
        forward_unit = forward_unit->prev;
        ocpt_head = forward_unit->members_list;
        forward_down = ocpt_head;
        printf("%s is forward_down\n",forward_down->tenant_name);

        //if single tenant
        if(forward_down->up == ocpt_head)
        {
            check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1) //remove at head
            {
                printf("GASHINA!\n");
                printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                forward_unit->num_occupants = 0;
                free(ocpt_head);
                (*head)->members_list = NULL;
            }
        }

        else
        {
            printf("%s is forward_down\n",forward_down->tenant_name);

            //Check forward_down->up or the tail
            check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1) //delete at tail
            {
                printf("Tenant %s removed.\n",forward_down->up->tenant_name);
                (forward_unit->num_occupants)--;
                forward_down = forward_down -> up;
                forward_unit->members_list->up = forward_down->up;
                forward_down->up->down = forward_down->down;
                forward_down->up = NULL;
                forward_down->down = NULL;
                free(forward_down);
            }

            while(forward_down->down != ocpt_head && duplicate_occupant_name != 1)//Since you are finished checking tail, check the rest of the occupant list of the tail of the unit list
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1)
                {
                    //remove at head
                    if(forward_down == ocpt_head)
                    {
                        printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                        (forward_unit->num_occupants)--;

                        forward_down->up->down = forward_down->down;
                        forward_down->down->up = forward_down->up;
                        forward_unit->members_list = forward_down->down;

                        forward_down->up = NULL;
                        forward_down->down = NULL;
                        free(forward_down);
                        break;
                    }

                    //remove at middle
                    else
                    {
                        (forward_unit->num_occupants)--;
                        printf("Tenant %s removed.\n",forward_down->tenant_name);

                        forward_down->up->down = forward_down->down;
                        forward_down->down->up = forward_down->up;

                        forward_down->up = NULL;
                        forward_down->down = NULL;
                        free(forward_down);
                        break;
                    }
                    break;
                }
                forward_down = forward_down -> down;
            }
        }

    }

    if(duplicate_occupant_name != 1) //if multiple units are present
    {
        forward_unit = forward_unit->prev; //Check first forward_unit-prev
        ocpt_head = forward_unit->members_list;
        forward_down = ocpt_head;

        //if single tenant
        if(forward_down->up == ocpt_head && forward_unit->members_list != NULL)
        {
            check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1) //remove at head
            {
                printf("GASHINA!\n");
                printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                forward_unit->num_occupants = 0;
                free(ocpt_head);
                forward_unit->members_list = NULL;
            }
        }

        else
        {
            if(forward_unit->members_list!=NULL)
            {
                //Check forward_down->up or the tail
                check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1) //delete at tail
                {
                    printf("Tenant %s removed.\n",forward_down->up->tenant_name);
                    (forward_unit->num_occupants)--;
                    forward_down = forward_down -> up;
                    forward_unit->members_list->up = forward_down->up;
                    forward_down->up->down = forward_down->down;
                    forward_down->up = NULL;
                    forward_down->down = NULL;
                    free(forward_down);
                }
            
                while(forward_down->down != ocpt_head && duplicate_occupant_name != 1 && forward_unit->members_list != NULL)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                    if(duplicate_occupant_name == 1)
                    {
                        //remove at head
                        if(forward_down == ocpt_head)
                        {
                            printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                            (forward_unit->num_occupants)--;

                            forward_down->up->down = forward_down->down;
                            forward_down->down->up = forward_down->up;
                            forward_unit->members_list = forward_down->down;

                            forward_down->up = NULL;
                            forward_down->down = NULL;
                            free(forward_down);
                            break;
                        }

                        //remove at middle
                        else
                        {
                            (forward_unit->num_occupants)--;
                            printf("Tenant %s removed.\n",forward_down->tenant_name);

                            forward_down->up->down = forward_down->down;
                            forward_down->down->up = forward_down->up;

                            forward_down->up = NULL;
                            forward_down->down = NULL;
                            free(forward_down);
                            break;
                        }
                        break;
                    }
                    forward_down = forward_down -> down;
                }
            }

            if(duplicate_occupant_name != 1) //after checking the forward_unit->prev or the tail of the unit list, check the rest of the unit list
            {
                forward_unit = (*head);
                ocpt_head = forward_unit->members_list;
                forward_down = ocpt_head;

                while(forward_unit->next != (*head) && forward_unit->members_list != NULL)
                {
                    //if single tenant
                    if(forward_down->up == ocpt_head)
                    {
                        check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        if(duplicate_occupant_name == 1) //remove at head
                        {
                            printf("GASHINA!\n");
                            printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                            forward_unit->num_occupants = 0;
                            free(ocpt_head);
                            forward_unit->members_list = NULL;
                            break;
                        }
                    }

                    else //if there are multiple tenants
                    {
                        //Check forward_down->up or the tail
                        check_if_duplicate_tenant(&(forward_down->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        if(duplicate_occupant_name == 1) //delete at tail
                        {
                            printf("Tenant %s removed.\n",forward_down->up->tenant_name);
                            (forward_unit->num_occupants)--;
                            forward_down = forward_down -> up;
                            forward_unit->members_list->up = forward_down->up;
                            forward_down->up->down = forward_down->down;
                            forward_down->up = NULL;
                            forward_down->down = NULL;
                            free(forward_down);
                            break;
                        }

                        while(forward_down->down != ocpt_head && duplicate_occupant_name != 1)
                        {
                            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                            if(duplicate_occupant_name == 1)
                            {
                                //remove at head
                                if(forward_down == ocpt_head)
                                {
                                    printf("Tenant %s removed.\n",ocpt_head->tenant_name);
                                    (forward_unit->num_occupants)--;

                                    forward_down->up->down = forward_down->down;
                                    forward_down->down->up = forward_down->up;
                                    forward_unit->members_list = forward_down->down;

                                    forward_down->up = NULL;
                                    forward_down->down = NULL;
                                    free(forward_down);
                                    break;
                                }

                                //remove at middle
                                else
                                {
                                    (forward_unit->num_occupants)--;
                                    printf("Tenant %s removed.\n",forward_down->tenant_name);

                                    forward_down->up->down = forward_down->down;
                                    forward_down->down->up = forward_down->up;

                                    forward_down->up = NULL;
                                    forward_down->down = NULL;
                                    free(forward_down);
                                    break;
                                }
                            }
                            
                            forward_down = forward_down -> down;
                        }
                    }

                    forward_unit = forward_unit->next;
                    ocpt_head = forward_unit->members_list;
                    forward_down = ocpt_head;
                }
            }
        }
    }

    if(duplicate_occupant_name != 1)
    {
        printf("Occupant name not found.\n");
    }

    //ask kung sure na ba yung user kung tatanggalin niya yung tenant
    //point up and down to NULL
    //point prev down to next
    //bawasan num_occupants by 1
}


void remove_unit(unit ** head)
{
    int duplicate_unit_name = -1;
    int allowremoval = -1;
    char removalchoice[2];

    char lowercase_new_unit_name[MAX];
    char lowercase_old_unit_name[MAX];

    unit * forward_unit = NULL;
    occupant * ocpt_head = NULL;
    occupant * forward_down = NULL;

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //Ask the user for the unit name
    printf("Enter unit name: ");
    scanf(" %[^\n]s", lowercase_new_unit_name);
    lowercase_string(lowercase_new_unit_name);

    printf("Are you sure you want to delete this unit?.\n");
    printf("Yes (Y) | No (N) : ");
    scanf("%s", removalchoice); 
    lowercase_string(removalchoice);

    if(strcmp("y", removalchoice) == 0)
    {
        allowremoval = 1;
    }

    else if (strcmp("n", removalchoice) == 0)
    {
        allowremoval = 0;
    }

    else
    {
        printf("Invalid input!.\n");
    }

    if(allowremoval == 1)
    {
        //if only single unit exists
        if(forward_unit->prev == (*head))
        {
            check_if_duplicate_unit(&(forward_unit->prev), lowercase_new_unit_name, lowercase_old_unit_name, &duplicate_unit_name);
            if(duplicate_unit_name == 1)
            {
                forward_unit = forward_unit->prev;
                ocpt_head = forward_unit->members_list;
                forward_down = ocpt_head;

                //Check if the specified unit to remove has no tenants
                if(ocpt_head == NULL)
                {
                    printf("Unit %s removed.\n", forward_unit->unit_name);
                    free((*head));
                    (*head) = NULL;
                }

                else
                {
                    printf("Unit %s removed.\n", forward_unit->unit_name);
                    while(forward_down != ocpt_head)
                    {
                        forward_down = forward_down->down;
                        free(ocpt_head);
                        ocpt_head = forward_down;
                    }
                    free(ocpt_head);
                    free((*head));
                    (*head) = NULL;
                }
            }       
        }

        else //if multiple units exists
        {
            //check first the tail
            check_if_duplicate_unit(&(forward_unit->prev), lowercase_new_unit_name, lowercase_old_unit_name, &duplicate_unit_name);
            if(duplicate_unit_name == 1)
            {
                printf("BOOMBAYAH.\n");
                forward_unit = forward_unit->prev;
                ocpt_head = forward_unit->members_list;
                forward_down = ocpt_head;

                //Check if the specified unit to be removed has no tenants
                if(ocpt_head == NULL)
                {
                    printf("BOGOSHIPO.\n");
                    printf("Unit %s removed.\n", forward_unit->unit_name);

                    forward_unit->prev->next = (*head);
                    (*head)->prev = forward_unit->prev;
                    forward_unit->next = NULL;
                    forward_unit->prev = NULL;
                    free(forward_unit);
                }

                else //remove at tail
                {
                    printf("NIGGA.\n");
                    printf("Unit %s removed.\n", forward_unit->unit_name);
                    while(forward_down != ocpt_head)
                    {
                        forward_down = forward_down->down;
                        free(ocpt_head);
                        ocpt_head = forward_down;
                    }
                    free(ocpt_head);

                    forward_unit->prev->next = (*head);
                    (*head)->prev = forward_unit->prev;
                    forward_unit->next = NULL;
                    forward_unit->prev = NULL;
                    free(forward_unit);
                }    
            }
            printf("%d :: duplicate_unit_name\n", duplicate_unit_name);

            while(forward_unit->next != (*head) && duplicate_unit_name != 1)
            {
                check_if_duplicate_unit(&forward_unit, lowercase_new_unit_name, lowercase_old_unit_name, &duplicate_unit_name);

                if(duplicate_unit_name == 1)
                {
                    //Remove at head
                    if(forward_unit == (*head))
                    {
                        //Check if the specified unit to be removed has no tenants
                        if(forward_unit->members_list == NULL)
                        {
                            printf("Unit %s removed.\n", forward_unit->unit_name);
                            forward_unit->prev->next = forward_unit->next;
                            forward_unit->next->prev = forward_unit->prev;
                            (*head) = forward_unit->next;
                            forward_unit->next = NULL;
                            forward_unit->prev = NULL;
                            free(forward_unit);
                            break;
                        }
                        
                        else
                        {
                            printf("Unit %s removed.\n", forward_unit->unit_name);
                            while(forward_down != ocpt_head)
                            {
                                forward_down = forward_down->down;
                                free(ocpt_head);
                                ocpt_head = forward_down;
                            }
                            free(ocpt_head);

                            forward_unit->prev->next = forward_unit->next;
                            forward_unit->next->prev = forward_unit->prev;
                            (*head) = forward_unit->next;
                            forward_unit->next = NULL;
                            forward_unit->prev = NULL;
                            free(forward_unit);
                            break;
                        }
                    }

                    //Remove at middle
                    else 
                    {
                        //Check if the specified unit to be removed has no tenants
                        if(forward_unit->members_list == NULL)
                        {
                            printf("Unit %s removed.\n", forward_unit->unit_name);
                            forward_unit->prev->next = forward_unit->next;
                            forward_unit->next->prev = forward_unit->prev;
                            forward_unit->next = NULL;
                            forward_unit->prev = NULL;
                            free(forward_unit);
                            break;
                        }

                        else
                        {
                            printf("Unit %s removed.\n", forward_unit->unit_name);
                            while(forward_down != ocpt_head)
                            {
                                forward_down = forward_down->down;
                                free(ocpt_head);
                                ocpt_head = forward_down;
                            }
                            free(ocpt_head);

                            forward_unit->prev->next = forward_unit->next;
                            forward_unit->next->prev = forward_unit->prev;
                            forward_unit->next = NULL;
                            forward_unit->prev = NULL;
                            free(forward_unit);
                            break;
                        }
                    }
                }

                forward_unit = forward_unit->next;
                ocpt_head = forward_unit->members_list;
                forward_down = ocpt_head;
            }
        }
    }

    if(duplicate_unit_name != 1)
    {
        printf("Unit not found.\n");
    }

    //Traverse the list and find the specific unit


    //cases
        //if only single unit exists
        //unit does not exist
        //no tenants in a specific unit
        //no tenants in every unit
        //remove at head
        //remove at tail
        //remove at middle
    //steps
        //traverse the list and find the specific unit
        //traverse the unit occupants and free all tenants
        //free the specific unit
        //adjust pointers

}

void edit_tenant(unit ** head)
{
    //ask the user for the last name and first name of the tenant
    //traverse the linked list and point to the tenant
    //Ask the user for the new mobile #

    //Cases
        //No tenant for every unit
        //No units
        //Edit at tail
        //tenant was not found   

    int duplicate_occupant_name = -1;
    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];
    
    occupant * temp = NULL;

    //Create the tenant to be edited
    occupant * new_occupant = NULL;
    create_new_occupant_remove_version(&new_occupant);

    //lower_new_unit_name is the string to check if it is a duplicate
    strcpy(lowercase_new_tenant_name, new_occupant->tenant_name);

    temp = find_tenant(head, &duplicate_occupant_name, &new_occupant);
    printf("%s :: temp->tenant_name\n", temp->tenant_name);

    if(temp == NULL)
    {
        printf("Tenant not found.\n");
    }

    else
    {
        enter_mobile_number(&temp);
        printf("Mobile number changed successfully.\n");       
    }

}

void search_tenant(unit ** head)
{
    int duplicate_occupant_name = -1;

    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];

    unit * forward_unit = NULL;
    occupant * ocpt_head = NULL;
    occupant * forward_down = NULL;
    occupant * new_occupant = NULL;

    //lower_new_unit_name is the string to check if it is a duplicate
    create_new_occupant_remove_version(&new_occupant);
    strcpy(lowercase_new_tenant_name, new_occupant->tenant_name);

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //if there is only a single unit
    if(forward_unit->prev == (*head) && forward_unit->prev->members_list != NULL)
    {
        if(forward_down->down == ocpt_head) //only single tenant
        {
            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1)
            {
                printf("BOOMBAYAH.\n");
                printf("Tenant name: %s\n",forward_down->tenant_name);
                printf("Mobile number: %s\n",forward_down->mobile_number);
                printf("Current unit assigned to: %s\n",forward_unit->unit_name);
            }    
        }
        
        else //multiple tenants
        {
            while(forward_down->down != ocpt_head)
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(forward_down->down == ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                    if(duplicate_occupant_name == 1)
                    {
                        printf("BOOMBAYAH1.\n");
                        printf("Tenant name: %s\n",forward_down->tenant_name);
                        printf("Mobile number: %s\n",forward_down->mobile_number);
                        printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        break;
                    }
                }

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH3.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                    break;
                }

                forward_down = forward_down->down;
            }

            if(duplicate_occupant_name != 1)
            {
                check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH11.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                }       
            }
        } 
    }

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    while(forward_unit->next != (*head)) //multiple units
    {
        if(forward_unit->members_list != NULL)
        {
            if(forward_down->down == ocpt_head)//single tenant
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH4.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                    break;
                }    
            }
            
            else //multiple tenants
            {
                while(forward_down->down != ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                    if(forward_down->down == ocpt_head)
                    {
                        check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        if(duplicate_occupant_name == 1)
                        {
                            printf("BOOMBAYAH5.\n");
                            printf("Tenant name: %s\n",forward_down->tenant_name);
                            printf("Mobile number: %s\n",forward_down->mobile_number);
                            printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                            break;
                        }
                    }

                    if(duplicate_occupant_name == 1)
                    {
                        printf("BOOMBAYAH6.\n");
                        printf("Tenant name: %s\n",forward_down->tenant_name);
                        printf("Mobile number: %s\n",forward_down->mobile_number);
                        printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        break;
                    }

                    forward_down = forward_down->down;
                }

                    if(duplicate_occupant_name != 1)
                    {
                        check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        
                        if(duplicate_occupant_name == 1)
                        {
                            printf("BOOMBAYAH7.\n");
                            printf("Tenant name: %s\n",forward_down->tenant_name);
                            printf("Mobile number: %s\n",forward_down->mobile_number);
                            printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        }                        
                    }
            }
        }
        forward_unit = forward_unit->next;
        ocpt_head = forward_unit->members_list;
        forward_down = ocpt_head;
    }

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //Check forward_unit->prev or the tail of the unit list 
    if(forward_unit->prev->members_list != NULL && duplicate_occupant_name!= 1)
    {
        ocpt_head = forward_unit->prev->members_list;
        forward_down = ocpt_head;

        if(forward_down->down == ocpt_head) //only single tenant
        {
            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1)
            {
                printf("BOOMBAYAH20.\n");
                printf("Tenant name: %s\n",forward_down->tenant_name);
                printf("Mobile number: %s\n",forward_down->mobile_number);
                printf("Current unit assigned to: %s\n",forward_unit->unit_name);
            }    
        }
        
        else //multiple tenants
        {
            while(forward_down->down != ocpt_head)
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(forward_down->down == ocpt_head)
                {
                    if(duplicate_occupant_name == 1)
                    {
                        printf("BOOMBAYAH21.\n");
                        printf("Tenant name: %s\n",forward_down->tenant_name);
                        printf("Mobile number: %s\n",forward_down->mobile_number);
                        printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        break;
                    }
                }

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH23.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                    break;
                }

                forward_down = forward_down->down;
            }

            if(duplicate_occupant_name != 1)
            {
                check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH24.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                }               
            }
        }
    }

    if(duplicate_occupant_name != 1)
    {
        printf("Tenant not found.\n");
    }
}

void search_tenant_specific_unit(unit ** head)
{
    int duplicate_occupant_name = -1;

    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];

    unit * forward_unit = NULL;
    occupant * ocpt_head = NULL;
    occupant * forward_down = NULL;
    occupant * new_occupant = NULL;

    //lower_new_unit_name is the string to check if it is a duplicate
    create_new_occupant_remove_version(&new_occupant);
    strcpy(lowercase_new_tenant_name, new_occupant->tenant_name);

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //if there is only a single unit
    if(forward_unit->prev == (*head) && forward_unit->prev->members_list != NULL)
    {
        if(forward_down->down == ocpt_head) //only single tenant
        {
            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1)
            {
                printf("BOOMBAYAH.\n");
                printf("Tenant name: %s\n",forward_down->tenant_name);
                printf("Mobile number: %s\n",forward_down->mobile_number);
                printf("Current unit assigned to: %s\n",forward_unit->unit_name);
            }    
        }
        
        else //multiple tenants
        {
            while(forward_down->down != ocpt_head)
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(forward_down->down == ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                    if(duplicate_occupant_name == 1)
                    {
                        printf("BOOMBAYAH1.\n");
                        printf("Tenant name: %s\n",forward_down->tenant_name);
                        printf("Mobile number: %s\n",forward_down->mobile_number);
                        printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        break;
                    }
                }

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH3.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                    break;
                }

                forward_down = forward_down->down;
            }

            if(duplicate_occupant_name != 1)
            {
                check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH11.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                }       
            }
        } 
    }

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    while(forward_unit->next != (*head)) //multiple units
    {
        if(forward_unit->members_list != NULL)
        {
            if(forward_down->down == ocpt_head)//single tenant
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH4.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                    break;
                }    
            }
            
            else //multiple tenants
            {
                while(forward_down->down != ocpt_head)
                {
                    check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                    if(forward_down->down == ocpt_head)
                    {
                        check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        if(duplicate_occupant_name == 1)
                        {
                            printf("BOOMBAYAH5.\n");
                            printf("Tenant name: %s\n",forward_down->tenant_name);
                            printf("Mobile number: %s\n",forward_down->mobile_number);
                            printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                            break;
                        }
                    }

                    if(duplicate_occupant_name == 1)
                    {
                        printf("BOOMBAYAH6.\n");
                        printf("Tenant name: %s\n",forward_down->tenant_name);
                        printf("Mobile number: %s\n",forward_down->mobile_number);
                        printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        break;
                    }

                    forward_down = forward_down->down;
                }

                    if(duplicate_occupant_name != 1)
                    {
                        check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                        
                        if(duplicate_occupant_name == 1)
                        {
                            printf("BOOMBAYAH7.\n");
                            printf("Tenant name: %s\n",forward_down->tenant_name);
                            printf("Mobile number: %s\n",forward_down->mobile_number);
                            printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        }                        
                    }
            }
        }
        forward_unit = forward_unit->next;
        ocpt_head = forward_unit->members_list;
        forward_down = ocpt_head;
    }

    forward_unit = (*head);
    ocpt_head = forward_unit->members_list;
    forward_down = ocpt_head;

    //Check forward_unit->prev or the tail of the unit list 
    if(forward_unit->prev->members_list != NULL && duplicate_occupant_name!= 1)
    {
        ocpt_head = forward_unit->prev->members_list;
        forward_down = ocpt_head;

        if(forward_down->down == ocpt_head) //only single tenant
        {
            check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
            if(duplicate_occupant_name == 1)
            {
                printf("BOOMBAYAH20.\n");
                printf("Tenant name: %s\n",forward_down->tenant_name);
                printf("Mobile number: %s\n",forward_down->mobile_number);
                printf("Current unit assigned to: %s\n",forward_unit->unit_name);
            }    
        }
        
        else //multiple tenants
        {
            while(forward_down->down != ocpt_head)
            {
                check_if_duplicate_tenant(&forward_down, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(forward_down->down == ocpt_head)
                {
                    if(duplicate_occupant_name == 1)
                    {
                        printf("BOOMBAYAH21.\n");
                        printf("Tenant name: %s\n",forward_down->tenant_name);
                        printf("Mobile number: %s\n",forward_down->mobile_number);
                        printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                        break;
                    }
                }

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH23.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                    break;
                }

                forward_down = forward_down->down;
            }

            if(duplicate_occupant_name != 1)
            {
                check_if_duplicate_tenant(&(forward_down), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

                if(duplicate_occupant_name == 1)
                {
                    printf("BOOMBAYAH24.\n");
                    printf("Tenant name: %s\n",forward_down->tenant_name);
                    printf("Mobile number: %s\n",forward_down->mobile_number);
                    printf("Current unit assigned to: %s\n",forward_unit->unit_name);
                }               
            }
        }
    }

    if(duplicate_occupant_name != 1)
    {
        printf("Tenant not found.\n");
    }
}

void print_all_tenants_specific_unit(unit ** head)
{
    char uppercase_unit[MAX];
    char uppercase_tenant[MAX];

    unit * forward = NULL;
    unit * backward = NULL;
    unit * temp = NULL;

    occupant * ocpt_head = NULL;

    temp = find_unit(head, &forward, &backward);

    if(temp == NULL)
    {
        printf("Unit not found.\n");
    }

    else
    {
        ocpt_head = temp->members_list;
    }

    if(ocpt_head == NULL && temp != NULL)
    {
        strcpy(uppercase_unit, temp->unit_name);
        uppercase_string(uppercase_unit);
        printf("Unit Name: %s\n", uppercase_unit);
        printf("Number of Occupants: %d\n", temp->num_occupants);
        printf("\tNo tenants!\n");
    }

    else if (ocpt_head != NULL && temp != NULL)     
    {
        strcpy(uppercase_unit, temp->unit_name);
        uppercase_string(uppercase_unit);
        printf("Unit Name: %s\n", uppercase_unit);
        printf("Number of Occupants: %d\n", temp->num_occupants);

        while(ocpt_head->down != temp->members_list)
        {
            strcpy(uppercase_tenant, ocpt_head->tenant_name);
            uppercase_string(uppercase_tenant);
            printf("\tTenant: %s \tMobile Number: %s\n",uppercase_tenant, ocpt_head->mobile_number);
            ocpt_head = ocpt_head->down;
        }
         
        strcpy(uppercase_tenant, ocpt_head->tenant_name);
        uppercase_string(uppercase_tenant);
        printf("\tTenant: %s \tMobile Number: %s\n",uppercase_tenant, ocpt_head->mobile_number);
    }
}

void move_tenant(unit ** head)
{
    
    //Ask user which tenant to migrate
    //traverse the list and list available tenants for migration (tenants with num_occupants<max_occupants)
    //Ask the user which available tenants will he choose 
    //make a copy of the tenant
    //remove the tenant
    //-1 for num_occupants 
    //migrate the tenant to the specified unit
    //sorted insert
    //+1 for num_occupants

    //cases
        //no units
        //no tenants for a specified unit
        //tenant not found.

    //ask the user for the last name and first name of the tenant
    //traverse the linked list and point to the tenant
    //Ask the user for the new mobile #

    //Cases
        //No tenant for every unit
        //No units
        //Edit at tail
        //tenant was not found   

    int duplicate_occupant_name = -1;
    char lowercase_new_tenant_name[MAX];
    char lowercase_old_tenant_name[MAX];
 
    unit * migrate_to_this_unit = NULL;
    occupant * temp = NULL;

    unit * unit_ptr_forward = NULL;
    unit * unit_ptr_backward = NULL;
    unit_ptr_forward = (*head);

    //Create the tenant to be moved
    occupant * new_occupant = NULL;
    create_new_occupant_remove_version(&new_occupant);

    //lower_new_unit_name is the string to check if it is a duplicate
    strcpy(lowercase_new_tenant_name, new_occupant->tenant_name);

    temp = find_tenant(head, &duplicate_occupant_name, &new_occupant);
    printf("%s :: temp->tenant_name\n", temp->tenant_name);
    strcpy(new_occupant->mobile_number, temp->mobile_number);

    if(temp == NULL)
    {
        printf("Tenant not found.\n");
    }

    else
    {
        //print available tenants
        printf("\n\nUnits with available slots.\n\n");
        if(unit_ptr_forward->prev->num_occupants != unit_ptr_forward->prev->max_occupants)
        {
            printf("Unit Name: %s \t Number of Occupants: %d \t Maximum Occupants: %d\n", unit_ptr_forward->prev->unit_name, unit_ptr_forward->prev->num_occupants, unit_ptr_forward->prev->max_occupants);
        }

        while(unit_ptr_forward->next != (*head))
        {
            if(unit_ptr_forward->num_occupants != unit_ptr_forward->max_occupants)
            {
                printf("Unit Name: %s \t Number of Occupants: %d \t Maximum Occupants: %d\n", unit_ptr_forward->unit_name, unit_ptr_forward->num_occupants, unit_ptr_forward->max_occupants);
            }
            unit_ptr_forward = unit_ptr_forward->next;
        }
    }

    if(temp != NULL)
    {
        migrate_to_this_unit = find_unit(head, &migrate_to_this_unit, &unit_ptr_backward);

        unit_ptr_backward = migrate_to_this_unit;
        temp = unit_ptr_backward->members_list;

        check_if_duplicate_tenant(&(temp->up), lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);

        if(duplicate_occupant_name != 1)
        {
            while(temp->down != temp)
            {
                check_if_duplicate_tenant(&temp, lowercase_new_tenant_name, lowercase_old_tenant_name, &duplicate_occupant_name);
                if(duplicate_occupant_name == 1)
                {
                    printf("ACTION NOT POSSIBLE.\n");
                    break;
                }
                temp = temp->down;
            }
        }

        else
        {
            printf("ACTION NOT POSSIBLE.\n");
        }

        if(duplicate_occupant_name != 1)
        {
            if(migrate_to_this_unit == NULL)
            {
                printf("Unit not found.\n");
            }

            else if(migrate_to_this_unit->num_occupants == migrate_to_this_unit->max_occupants)
            {
                printf("That unit is not available.\n");
            }

            else
            {
                //begin removing the selected tenant
                remove_tenant_specific(head, &new_occupant);

                //sorted insert the copy of the removed tenant to the specified unit.
                insert_tenant(&migrate_to_this_unit, &new_occupant);
                migrate_to_this_unit->num_occupants++; 
            }            
        }
    }
}

int main()
{
    unit * head = NULL;
    unit * temp = NULL;
    int menu_choice = 10;
    int atleast_one_unit_exists = 0;

    while(menu_choice != 0)
    {
        menu();
        menu_choice = choose_option(menu_choice);

        switch(menu_choice)
        {
            case 1: //Add Unit
                add_unit(&head);
                printf("\n");
                print_all_units(head);
                break;
            case 2: //Add Tenant
                add_tenant(&head);
                printf("\n");
                print_all_tenants(head);
                break;
            case 3: //Search Tenant
                if(head != NULL)
                {
                    search_tenant(&head);
                    printf("\n");
                }
                else
                {
                    printf("Not possible, empty list.\n");
                }
                //traverse the linked list. Linear search. Find which unit he is in.
                break;
            case 4: //Move Tenant
                move_tenant(&head);
                break;
            case 5: //Remove Tenant
                if(head != NULL)
                {
                    remove_tenant(&head);
                    printf("\n");
                    print_all_tenants(head);
                }
                else
                {
                    printf("Not possible, empty list.\n");
                }
                break;
            case 6: //Edit Tenant
                if(head != NULL)
                {
                    printf("Enter the last name and first name of the tenant that you wish to edit.\n");
                    edit_tenant(&head);
                    print_all_tenants(head);
                }
                else
                {
                    printf("Not possible, empty list.\n");
                }

                //traverse the linked list. Linear search. Find which unit he is in. Edit accordingly.
                break;
            case 7: //Print Master List Of Occupants Per Unit
                if(head != NULL)
                {
                    print_all_tenants(head);
                }
                else
                {
                    printf("Not possible, empty list.\n");
                }
                
                //traverse the linked list, similar to print all songs in all of the playlist
                break;
            case 8: //Print List Of Occupants Per Unit
                if(head != NULL)
                {
                    print_all_tenants_specific_unit(&head);
                }
                else
                {
                    printf("Not possible, empty list.\n");
                }
                    
                break;
            case 9: //Remove Unit
                if(head !=NULL)
                {
                   remove_unit(&head); 
                    if(head != NULL)
                    {
                        printf("\n");
                        print_all_tenants(head);
                    }
                    else
                    {
                        printf("No units.\n");
                    }
                }
                else
                {
                    printf("Not possible, empty list.\n");
                }
                break;
            case 0: //Exit
                break;

            default:
                printf("\nInput invalid, try again!\n");
                break;
        }
    }
    return 0;
}



