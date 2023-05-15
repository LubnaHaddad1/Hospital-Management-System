// Lubna Haddad 

/* This project is a hospital management system that reads patients info from a certain file.
 It allows user to perform some processes as inserting, updating, listing, searching, sorting and deleting on the patients. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// System Functions
void preMenuScreen();
void menuScreen();
int NumberOfPatients(char[]);
void insertAllPatients();
void insertPatient(FILE *);
void insertPatientFromUser();
void updatePatient();
void listScreen();
void ListPatients();
void ListIllness();
void ListCity();
void listDischarged();
void searchScreen();
void searchName();
void searchBirthDay();
void deletePatient();
void exportXML();
void savePatients();

struct node    // Creates Linked List
{
    char Name [50];
    char Gender;
    int Add_Date;
    int Bir_Date;
    char Illness [30];
    char City [30];
    char Blood_Type [5];
    int flag; // when it is 1: the patient is discharged
    struct node *next;
}*head; // head node

int NumberOfPatients(char fileName[30]) // Takes number of patients in a given file name
{
    FILE *File = fopen(fileName, "r"); // opens patients file
    int i = 0;
    char line[100];
    int A = fgets(line, 100, File);
    while(A) // while A in not EOF
    {
        A = fgets(line, 100, File);
        i++; // counter of lines
    }
    return i; // return number of lines (patients) in the file
}

void insertAllPatients() // Reads All patients from file
{
    int n = NumberOfPatients("patients.txt"); // let n = number of patients in file
    FILE *patientsFile = fopen("patients.txt","r");
    for(int i=0; i<n; i++) // as long as it is not the EOF
    {
        insertPatient(patientsFile); // insert from file
    }
    return;
}

void insertPatient(FILE *patientsFile) // Inserts one patient from file
{
    if (head == NULL)
    {
        head = (struct node *)malloc(sizeof(struct node));
        if(head != NULL)
        {
            fscanf(patientsFile, "%[^#]#", &head->Name);
            fscanf(patientsFile, "%[^#]#", &head->Gender);
            fscanf(patientsFile, "%d%*c",  &head->Add_Date);
            fscanf(patientsFile, "%d%*c",  &head->Bir_Date);
            fscanf(patientsFile, "%[^#]#", &head->Illness);
            fscanf(patientsFile, "%[^#]#", &head->City);
            fscanf(patientsFile, "%[^\n]\n", &head->Blood_Type);
            head->next = NULL;
        }
        else
            printf("The system is out of memory!\n");
    }
    else  // if it's not the first patient in the list
    {
        struct node *newPatient= (struct node *)malloc(sizeof(struct node));
        if(newPatient != NULL)
        {
            fscanf(patientsFile, "%[^#]#",  &newPatient->Name);
            fscanf(patientsFile, "%[^#]#",  &newPatient->Gender);
            fscanf(patientsFile, "%d%*c",   &newPatient->Add_Date);
            fscanf(patientsFile, "%d%*c",   &newPatient->Bir_Date);
            fscanf(patientsFile, "%[^#]#",  &newPatient->Illness);
            fscanf(patientsFile, "%[^#]#",  &newPatient->City);
            fscanf(patientsFile, "%[^\n]\n", &newPatient->Blood_Type);
            newPatient->next = head;
            head = newPatient;
        }
        else
            printf("The system is out of memory!\n");
    }
}

void insertPatientFromUser() // Adds new patient
{
    system("cls");
    char name [30];
    printf("Please enter the new patient's Name: \n");
    scanf(" %30[^\n]", &name);
    if (head == NULL) // if it's the first patient in the list
    {
        head =(struct node*)malloc(sizeof(struct node));
        if(head != NULL)
        {
            strcpy(head->Name, name);
            printf("Please enter the patient's gender: \n");
            scanf(" %c", &head->Gender);
            printf("please enter the patients's admission date: \n");
            scanf(" %d", &head->Add_Date);
            printf("Please enter the patients's date of birth: \n");
            scanf(" %d", &head->Bir_Date);
            printf("Please enter the patient's illness: \n");
            scanf(" %30[^\n]", &head->Illness);
            printf("Please enter the patient's city: \n");
            scanf(" %30[^\n]", &head->City);
            printf("Please enter the patient's blood type: \n");
            scanf(" %5[^\n]", &head->Blood_Type);
            head->next = NULL;
        }
        else
            printf("The system is out of memory!\n");
    }
    else // if it's not the first patient in the list
    {
        struct node *newPatient = (struct node*)malloc(sizeof(struct node));
        if(newPatient!= NULL)
        {
            strcpy(newPatient->Name, name);
            printf("Please enter the patient's gender: \n");
            scanf(" %c", &newPatient->Gender);
            printf("please enter the patients's admission date: \n");
            scanf(" %d", &newPatient->Add_Date);
            printf("Please enter the patients's date of birth: \n");
            scanf(" %d", &newPatient->Bir_Date);
            printf("Please enter the patient's illness: \n");
            scanf(" %30[^\n]", &newPatient->Illness);
            printf("Please enter the patient's city: \n");
            scanf(" %30[^\n]", &newPatient->City);
            printf("Please enter the patient's blood type: \n");
            scanf(" %5[^\n]", &newPatient->Blood_Type);
            newPatient->next = head;
            head = newPatient;
        }
        else
            printf("The system is out of memory!\n");
    }
}

void updatePatient() // Updates patient's information
{
    system("cls");
    int choice;
    int b;
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head; // starts from the first patient
    printf("Please enter patient's date of birth: \n");
    scanf(" %d", &b);
    while(temp != NULL)
    {
        if(temp->Bir_Date == b) // if birth date matches
            break;
        if(temp->next == NULL && temp->Bir_Date != b) // if birth date does not match
        {
            printf("Patient not found!\n");
            return;
        }
        temp = temp->next; // moves to the next patient
    }
    while(1)
    {
        // show updating menu
        printf("Please select the field to be updated:\n");
        printf("1- Name.\n2- Gender.\n3- Date Of Admission.\n4- Date of Birth.\n5- Illness. \n6- City. \n7- Blood Type. \n8- Cancel.\n");
        scanf(" %d", &choice);
        switch(choice)
        {
        case 1: // enters name
            printf("Please enter the patient's new name: \n");
            scanf(" %30[^\n]", &temp->Name);
            printf("DONE!\n");
            break;
        case 2: // enters gender
            printf("Please enter the patient's new gender: \n");
            scanf(" %c", &temp->Gender);
            printf("DONE!\n");
            break;
        case 3: // enters admission date
            printf("Please enter the patient's new date of admission: \n");
            scanf(" %d", &temp->Add_Date);
            printf("DONE!\n");
            break;
        case 4: // enters birth date
            printf("Please enter the patient's new date of birth: \n");
            scanf(" %d", &temp->Bir_Date);
            printf("DONE!\n");
            break;
        case 5: // enters illness
            printf("Please enter the patient's new Illness: \n");
            scanf(" %30[^\n]", temp->Illness);
            printf("DONE!\n");
            break;
        case 6: // enters city
            printf("Please enter the patient's new city: \n");
            scanf(" %30[^\n]", temp->City);
            printf("DONE!\n");
            break;
        case 7: // enters blood type
            printf("Please enter the patient's new blood type: \n");
            scanf(" %5[^\n]", temp->Blood_Type);
            printf("DONE!\n");
            break;
        case 8: // ends updating
            return;
        }

    }
}

void ListPatients() // Displays all patients
{
    system("cls");
    struct node *temp =(struct node *)malloc(sizeof(struct node));
    temp = head; // starts from the first patient
    while(temp != NULL)
    {
        if (temp->flag != 1) // if the patient is not discharged.
        {
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Patient~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Name: %s, Gender: %c, Date Of Admission: %d, Date Of Birth: %d, Illness: %s, City: %s, Blood Type: %s\n", temp->Name, temp->Gender, temp->Add_Date, temp->Bir_Date, temp->Illness, temp->City, temp->Blood_Type);
            temp = temp->next;
        }
        else if (temp->flag == 1) // if the patient is not discharged: DON'T DISPLAY HIS INFO.
        {
            temp = temp->next;
        }

    }

}

void ListIllness() // Displays Illnesses
{
    system("cls");
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;  // starts from the first patient
    while(temp != NULL)
    {
        if (temp->flag != 1) // if the patient is not discharged
        {
            printf("%s \n", temp->Illness);
            temp = temp->next;
        }
        else if (temp->flag == 1) // if the patient is discharged: DON'T DISPLAY HIS ILLNESS.
        {
            temp = temp->next;
        }
    }
}

void ListCity() // Displays the cities
{
    system("cls");
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;  // starts from the first patient
    while(temp != NULL)
    {
        if (temp->flag != 1) // if the patient is not discharged.
        {
            printf("%s \n", temp->Name);
            temp = temp->next;
        }
        else if (temp->flag == 1) // if the patient is discharged: DON'T DISPLAY HIS CITY.
        {
            temp = temp->next;
        }
    }
}

void listDischarged() // Displays the discharged patients
{
    system("cls");
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;
    while (temp != NULL)
    {
        if (temp->flag == 1) // if the patient is discharged: DISPLAY HIS INFO.
        {
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Patient~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Name: %s, Gender: %c, Date Of Admission: %d, Date Of Birth: %d, Illness: %s, City: %s, Blood Type: %s\n", temp->Name, temp->Gender, temp->Add_Date, temp->Bir_Date, temp->Illness, temp->City, temp->Blood_Type);
            temp = temp->next;
        }
        else if (temp->flag != 1) // if the patient in not discharged: DON'T DISPLAY HIS INFO.
        {
            temp = temp->next;
        }
    }
}

void searchName() // Searches for a patient by entering his name
{
    system("cls");
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr = head;
    char name [30];
    printf("Enter the name of patient: \n");
    scanf(" %30[^\n]", name);
    while(ptr!= NULL && strcasecmp(name, ptr->Name)) // if the name does not match
    {
        ptr = ptr->next;
    }
    if(ptr == NULL) // if all patients were checked and no name matched
    {
        printf("The patient is not found \n");
    }
    else // if the name matches
    {
        printf("The patient was found: \nName: %s\nGender: %c\nAdmission Date: %d\nBirthday Date: %d\nIllness: %s\nCity: %s\nBlood Type: %s\n", ptr->Name, ptr->Gender, ptr->Add_Date, ptr->Bir_Date, ptr->Illness, ptr->City, ptr->Blood_Type);
    }
}

void searchBirthDay() // Searching for a patient by entering his birth date
{
    system("cls");
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr = head;
    int B;
    printf("Enter the patient's birth date: \n");
    scanf(" %d", &B);
    while((ptr != NULL) && (ptr->Bir_Date != B)) // if the birth date does not match
    {
        ptr = ptr->next; // move to the next patient
    }
    if(ptr == NULL) // if all patients was checked and no date matched
    {
        printf("The patient is not found\n");
    }
    else // if the birth date matches
    {
        printf("The patient was found: \nName: %s\nGender: %c\nAdmission Date: %d\nBirthday Date: %d\nIllness: %s\nCity: %s\nBlood Type: %s\n", ptr->Name, ptr->Gender, ptr->Add_Date, ptr->Bir_Date, ptr->Illness, ptr->City, ptr->Blood_Type);
    }
}

void savePatients() // Saves changes to the list
{
    FILE *out = fopen("patients.txt", "w"); // writes on file
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;
    while(temp != NULL)
    {
        fprintf(out, "%s#%c#%d#%d#%s#%s#%s\n", temp->Name, temp->Gender, temp->Add_Date,temp->Bir_Date, temp->Illness, temp->City, temp->Blood_Type);
        temp = temp->next;
    }
}

void deletePatient() // Deletes a patient (soft delete)
{
    int B;
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;
    printf("Please enter the patient's birth date: \n");
    scanf(" %d", &B);
    while(temp != NULL)
    {
        if(temp->Bir_Date == B && temp != head) // if it is not the first patient in list
        {
            temp->flag = 1;
            printf("Patient successfully deleted\n");
        }
        else if(temp->Bir_Date == B && temp == head) // if it is the first patient in list
        {
            temp = head->next;
            temp->flag = 1;
            printf("Patient successfully deleted\n");
        }
        temp = temp->next;
    }
}

void exportXML() // Exports XML report
{
    FILE *report = fopen("Report.xml", "w"); // writes on file
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;
    while(temp != NULL)
    {
        fprintf(report, "<patient>\n");
        fprintf(report, "\t<name>%s</name>\n", temp->Name);
        fprintf(report, "\t<gender>%c</gender>\n", temp->Gender);
        fprintf(report, "\t<admissionDate value ='%d' />\n", temp->Add_Date);
        fprintf(report, "\t<BirthDate value ='%d' />\n", temp->Bir_Date);
        fprintf(report, "\t<diagnosis>%s</diagnosis>\n", temp->Illness);
        fprintf(report, "\t<city>%s</city>\n", temp->City);
        fprintf(report, "\t<bloodType>%s</bloodType>\n", temp->Blood_Type);
        fprintf(report, "</patient>\n");
        temp = temp->next;
    }
    fclose(report);
}

void preMenuScreen() // Starts menu
{
    menuScreen();
    system("cls");
    exit(0);
}

void menuScreen() // Screen of options
{
    printf("\t\t\t\t\tWELCOME TO THE HOSPITAL MANAGMENT SYSTEM !!!\n");
    char x;
    do
    {
        // Menu Options
        printf("Please enter a choice:\n");
        printf("1- READ & CREATE  - Read file and create linked list \n");
        printf("2- INSERT  - Insert a new Patient \n");
        printf("3- UPDATE  - Update patient's Information \n");
        printf("4- LIST    - List Patients \n");
        printf("5- SEARCH  - Search for a patient \n");
        printf("6- SORT    - Sort based on names \n");
        printf("7- DELETE  - Delete a patient \n");
        printf("8- XML     - Export XML report \n");
        printf("9- EXIT    - Save and exit \n");
        scanf(" %c", &x);
        switch (x)
        {
        case '1': // reads file of patients & creates linked list
            insertAllPatients();
            printf("DONE!\n");
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '2': // adds new patients to the list from user
            insertPatientFromUser();
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '3': // updates any info in the list
            updatePatient();
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '4': // displays info from the list
            listScreen();
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '5': // searches for a person & displays his info
            searchScreen();
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '6': // sorts the names using RADIX SORT
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '7': // deletes a patient: without removing from list
            deletePatient();
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '8':
            exportXML();
            printf("Data was exported successfully.\n");
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        case '9': // exits and save changes
            savePatients();
            system("cls");
            return;
            break;
        default: // if the user entered invalid option
            printf("Please enter a valid choice\n");
            printf("\nEnter anything to continue\n");
            scanf(" %s");
            system("cls");
            break;
        }
    }
    while(1);
}

void listScreen() // List options
{
    int x;
    printf("Please choose an option: \n");
    printf("1- LIST ALL PATIENTS\n2- LIST ILLNESSES\n3- LIST CITIES\n4- LIST DISCHARGED PATIENTS\n");
    scanf(" %d", &x);
    if(x == 1)
        ListPatients();
    else if(x == 2)
        ListIllness();
    else if(x == 3)
        ListCity();
    else if(x == 4)
        listDischarged();
}

void searchScreen() // Search options
{
    int x;
    system("cls");
    printf("Please choose an option: \n");
    printf("1- SEARCH BY NAMES\n2- SEARCH BY BIRTHDAY DATES\n");
    scanf("%d", &x);
    if(x == 1)
        searchName();
    if(x == 2)
        searchBirthDay();
}

int main()
{
    preMenuScreen();  // Displays menu
    return 0;
}


