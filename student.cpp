#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<ctype.h>

// Student Structure
typedef struct student{
	char name[30];
	int age;
	int marks[6];
    int total_marks;
    float percentage;
	char blood_group[5];
	char mobile_number[20];
	char username[20];
	int id;
	char password[20];
	
}stu;

// function prototypes 
void teacher_menu();
void student_menu(char username[]);
void add_student();
void update_student();
void delete_student();
void view_student(char username[]);
void view_all_students();
int login(char *username, char *password, char *role);
int isValidMobileNumber(char mobile_number[]);
int isValidBloodGroup(char blood_group[]);

// main function
int main(){
	char username[20],password[20],role[10];
	printf("Welcome to the Student Management System\n");
    printf("Please login to continue.\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
//Determine if the user is student or teacher
    if (login(username, password, role)) {
        if (strcmp(role, "teacher") == 0) {
            teacher_menu();
        }
		 else if (strcmp(role, "student") == 0) {
            student_menu(username);
        }
    } else {
        printf("Invalid username or password!\n");
    }
	return 0;
}

// Login function
int login(char *username, char *password, char *role) {
	
    if (strcmp(username, "kaushik") == 0 && strcmp(password, "k123") == 0) {
        strcpy(role, "teacher");
        return 1;
    } else if (strcmp(username, "student") == 0 && strcmp(password, "s123") == 0) {
        strcpy(role, "student");
        return 1;
    }
    return 0;
}
// Function to check if the mobile number is valid
int isValidMobileNumber(char mobile_number[]) {
    // Check if length is 10 digits
    if (strlen(mobile_number)!= 10) {
        return 0;  // Invalid length
    }
    
    // Check if all characters are digits
    for (int i = 0; i < 10; i++) {
        if (!isdigit(mobile_number[i])) {
            return 0;  // Contains non-digit characters
        }
    }

    // Check if the first digit is between 6 and 9
    if (mobile_number[0] >= '6' && mobile_number[0] <= '9') {
        return 1;  // Valid mobile number
    }

    return 0;  // Invalid starting digit
}
// ToUppercase Converter
void toUpperCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

// Blood Group 
int isValidBloodGroup(char blood_group[]) {
    const char *validBloodGroups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

    // Convert input to uppercase for case-sensitive comparison
    toUpperCase(blood_group);

    for (int i = 0; i < 8; i++) {
        if (strcmp(blood_group, validBloodGroups[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

// Teacher's Menu
void teacher_menu(){
	int choice;
    do {
        printf("\nTeacher Menu\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_student();
                break;
            case 2:
                update_student();
                break;
            case 3:
                delete_student();
                break;
            case 4:
                view_all_students();
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
}

// Student menu (student can only view their own info)
void student_menu(char username[]) {
    printf("\nStudent Menu\n");
    view_student(username);
}

// Add a new student
void add_student() {
    stu s;
    FILE *file = fopen("student.txt","a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    else{
    	    // Auto-generate ID
    FILE *file_read = fopen("student.txt", "r");
    int last_id = 0;
    if (file_read != NULL) {
        stu temp;
        while (fread(&temp, sizeof(stu), 1, file_read)) {
            last_id = temp.id;  // Track the last student's ID
        }
        fclose(file_read);
    }
    s.id = last_id + 1;  // New student's ID is last_id + 1
    
   printf("Enter Student's Name:");
   scanf("%s",s.name);
   printf("Enter Student's Age:");
   scanf("%d",&s.age);
   printf("Enter Marks of the student's (for 7 subjects):\n");
   int i=0, total_marks=0;
   float percentage;
   for(i=0;i<7;i++){
    printf("Marks of Subject %d=",i+1);
    scanf("%d",&s.marks[i]);
    total_marks+=s.marks[i];
   }
    percentage = (total_marks / 700.0) * 100;;
   s.total_marks=total_marks;
   s.percentage=percentage;
//Mobile Number Validation
   char mobile[20];
    while (1) {
        printf("Enter the student's mobile number: ");
        scanf("%s", mobile);

        if (isValidMobileNumber(mobile)) {
            // If the mobile number is valid, store it in the structure
            strcpy(s.mobile_number, mobile);
            break;  // Exit the loop
        } 
        else {
            // If invalid, prompt the user to input again
            printf("Invalid mobile number! Please try again.\n");
        }
    }
// Blood Group Validation
    char blood[20];
    while (1) {
        printf("Enter the student's Blood Group: ");
        scanf("%s", blood);

        if (isValidBloodGroup(blood)) {
            // If the Blood Group is valid, store it in the structure
            strcpy(s.blood_group, blood);
            break;  // Exit the loop
        } 
        else {
            // If invalid, prompt the user to input again
            printf("Invalid mobile number! Please try again.\n");
        }
    }
    printf("\nEnter Student's User Name:");
   scanf("%s",s.username);
   printf("\nEnter Student's User Id:");
   scanf("%d",&s.id);
   printf("\nEnter Student's Password:");
   scanf("%s",s.password);

    fwrite(&s, sizeof(s), 1, file);
    fclose(file);

    printf("\nStudent added successfully!\n");
}
}

// Update student information
void update_student() {
    stu s;
    FILE *file = fopen("student.txt", "r+");
    int id, found = 0;

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(stu), 1, file)) {
        if (s.id == id) {
            found = 1;
   printf("\nEnter New Name:");
   scanf("%s",s.name);
   printf("\nEnter New  Age:");
   scanf("%d",&s.age);
    printf("\nEnter New Marks for the student (7 subjects):\n");
   int i=0, total_marks=0;
   float percentage;
   for(i=0;i<7;i++){
    printf("Marks of Subject %d=",i+1);
    scanf("%d",&s.marks[i]);
    total_marks+=s.marks[i];
   }
   percentage=((total_marks/700)*100);
   s.total_marks=total_marks;
   s.percentage=percentage;
//Mobile Number Validation
   char mobile[20];
    while (1) {
        printf("\nEnter the New  mobile number: ");
        scanf("%s", mobile);

        if (isValidMobileNumber(mobile)) {
            // If the mobile number is valid, store it in the structure
            strcpy(s.mobile_number, mobile);
            break;  // Exit the loop
        } 
        else {
            // If invalid, prompt the user to input again
            printf("Invalid mobile number! Please try again.\n");
        }
    }
//Blood Group Validation
    char blood[20];
    while (1) {
        printf("Enter the New Blood Group: ");
        scanf("%s", blood);

        if (isValidBloodGroup(blood)) {
            // If the Blood Group is valid, store it in the structure
            strcpy(s.blood_group, blood);
            break;  // Exit the loop
        } 
        else {
            // If invalid, prompt the user to input again
            printf("Invalid mobile number! Please try again.\n");
        }
    }
    printf("Enter Student's User Name:");
   scanf("%s",s.username);
   printf("Enter Student's User Id:");
   scanf("%d",&s.id);
   printf("Enter Student's Password:");
   scanf("%s",s.password);


            fseek(file,-sizeof(stu), SEEK_CUR);
            fwrite(&s, sizeof(stu), 1, file);
             printf("Student updated successfully with ID %d!\n", s.id);
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found!\n",s.id);
    }
    fclose(file);
}

// Delete a student
void delete_student() {
    stu s;
    FILE *file = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int id, found = 0;

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(stu), 1, file)) {
        if (s.id!=id) {
            fwrite(&s, sizeof(stu), 1, temp);
        } 
        else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student with ID %d not found!\n",id);
    }
}

// View all students (Teacher only)
void view_all_students() {
    stu s;
    FILE *file = fopen("student.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

  printf("\nAll Students:\n");
  
printf("\n%-5s %-15s %-20s %-5s %-15s %-12s %-12s %-10s", 
       "ID", "UserName", "Name", "Age", "Mobile Number", "Total Marks", "Percentage", "Blood Group");
printf("\n----- --------------- -------------------- ----- --------------- ------------ ------------ -----------\n");

while (fread(&s, sizeof(stu), 1, file)) {
    // Print student information in a properly aligned tabular format
    
    printf("%-5d %-15s %-20s %-5d %-15s %-12d %-12.2f %-10s\n",
           s.id, s.username, s.name, s.age, s.mobile_number, s.total_marks, s.percentage, s.blood_group);
}

    fclose(file);
}

// View specific student information (Student only)
void view_student(char username[]) {
    stu s;
    FILE *file = fopen("student.txt", "r");
    int found = 0;

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(stu), 1, file)) {
        if (strcmp(s.username, username) == 0) {
        printf("\n%-5s %-15s %-20s %-5s %-15s %-12s %-12s %-10s", 
       "ID", "UserName", "Name", "Age", "Mobile Number", "Total Marks", "Percentage", "Blood Group");
printf("\n----- --------------- -------------------- ----- --------------- ------------ ------------ -----------\n");
printf("%-5d %-15s %-20s %-5d %-15s %-12d %-12.2f %-10s\n",
           s.id, s.username, s.name, s.age, s.mobile_number, s.total_marks, s.percentage, s.blood_group);
    }
            found = 1;
            break;
        }
        
    if (!found) {
        printf("Student with username %s not found!\n", username);
    }
    fclose(file);
}
