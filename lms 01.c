#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USER_NAME 30
#define MAX_PASSWORD 20
#define MAX_NAME_LENGTH 100
#define MAX_CONTACT_INFO 50
#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 50
#define MAX_AUTHOR_LENGTH 50
#define MAX_DATE_LENGTH 11
#define MAX_STUDENTS 100
#define MAX_HISTORY 500

int is_logged_in = 0;
int book_count = 0;
int borrowed_book_count = 0;
int borrow_history_count = 0;
int student_count = 0;

// Structure to represent a book
struct Book {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char issue_date[MAX_DATE_LENGTH];  // Issue date for borrowed books
    int is_borrowed;
    int is_reserved;
    char reserved_by[MAX_USER_NAME]; // User who reserved the book
};

// Structure for borrow history
struct BorrowHistory {
    char username[MAX_USER_NAME];
    char book_title[MAX_TITLE_LENGTH];
    char issue_date[MAX_DATE_LENGTH];
};

// Structure for student
struct Student {
    char name[MAX_NAME_LENGTH];
    char username[MAX_USER_NAME];
    char password[MAX_PASSWORD];
};

struct Book books[MAX_BOOKS];
struct BorrowHistory borrow_history[MAX_HISTORY];
struct Student students[MAX_STUDENTS];

char librarian_username[MAX_USER_NAME] = "l12";
char librarian_password[MAX_PASSWORD] = "l12";
char librarian_contact[MAX_CONTACT_INFO] = "librarian@library.com";  // Example contact for librarian

char teacher_username[MAX_USER_NAME] = "t12";
char teacher_password[MAX_PASSWORD] = "t12";
char teacher_contact[MAX_CONTACT_INFO] = "teacher@library.com";  // Example contact for teacher

char student_username[MAX_USER_NAME] = "s12";
char student_password[MAX_PASSWORD] = "s12";
char student_contact[MAX_CONTACT_INFO];  // Corrected duplicate declaration


void headMessage(const char *message)
{
    system("cls");  // Clear the screen (on Windows)

    // Print the heading message
    printf("\t\t********************************************************************\n");
    printf("\t\t********************************************************************\n");
    printf("\t\t********                                                    ********\n");
    printf("\t\t********        Library Management System                   ********\n");
    printf("\t\t********                                                    ********\n");
    printf("\t\t********************************************************************\n");
    printf("\t\t********************************************************************\n");

    // Optionally print the provided message (if any)
    if (message != NULL) {
        printf("\n\t\t\t\t%s\n", message);
    }
}

void welcomeMessage()
{
    headMessage(" ");


    printf("\n\n\n\n\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 LIBRARY                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  \n");
    printf("\n\n\n\t\t\t Select Enter key to continue.....\n");

    getchar();

}




int login(int choice) {
    char username[MAX_USER_NAME], password[MAX_PASSWORD];

    // Get username and password from user
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    // Check login based on role
    if (choice == 1) { // Librarian
        if (strcmp(username, librarian_username) == 0 && strcmp(password, librarian_password) == 0) {
            printf("Login successful as Librarian!\n");
            return 1;  // Success
        } else {
            printf("Invalid username or password for Librarian.\n");
            return 0;  // Failure
        }
    } else if (choice == 2) { // Teacher
        if (strcmp(username, teacher_username) == 0 && strcmp(password, teacher_password) == 0) {
            printf("Login successful as Teacher!\n");
            return 1;  // Success
        } else {
            printf("Invalid username or password for Teacher.\n");
            return 0;  // Failure
        }
    } else if (choice == 3) { // Student
        if (strcmp(username, student_username) == 0 && strcmp(password, student_password) == 0) {
            printf("Login successful as Student!\n");
            return 1;  // Success
        } else {
            printf("Invalid username or password for Student.\n");
            return 0;  // Failure
        }
    } else {
        printf("Invalid selection.\n");
        return 0;  // Failure
    }
}


// Function to register user
void registerUser(int choice) {
    char username[MAX_USER_NAME], password[MAX_PASSWORD], contact[MAX_CONTACT_INFO];
    char contact_type;

    // Ask for username and password
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    // Ask whether the user wants to provide an email or phone number
    printf("Do you want to enter an email (e) or phone number (p)? ");
    scanf(" %c", &contact_type);  // Note the space before %c to avoid the newline from the previous input

    if (contact_type == 'e' || contact_type == 'E') {
        printf("Enter Email: ");
    } else if (contact_type == 'p' || contact_type == 'P') {
        printf("Enter Phone Number: ");
    } else {
        printf("Invalid option. Contact info will not be saved.\n");
        contact[0] = '\0';  // Set an empty string if neither email nor phone is provided
        return;
    }

    // Get the contact info (email or phone number)
    scanf(" %[^\n]s", contact);  // This will allow spaces in the contact information

    // Register based on the selected role
    if (choice == 1) {  // Librarian
        strcpy(librarian_username, username);
        strcpy(librarian_password, password);
        strcpy(librarian_contact, contact);
        printf("Librarian registered successfully!\n");
    } else if (choice == 2) {  // Teacher
        strcpy(teacher_username, username);
        strcpy(teacher_password, password);
        strcpy(teacher_contact, contact);
        printf("Teacher registered successfully!\n");
    } else if (choice == 3) {  // Student
        strcpy(student_username, username);
        strcpy(student_password, password);
        strcpy(student_contact, contact);
        printf("Student registered successfully!\n");
    } else {
        printf("Invalid selection.\n");
    }
}


void logout() {
    is_logged_in = 0;
    printf("You have logged out.\n");
}



void addBook() {
    if (book_count < MAX_BOOKS) {
        // Ask for book title
        printf("Enter Book Title: ");
        getchar();  // To consume the newline left by previous scanf
        fgets(books[book_count].title, MAX_TITLE_LENGTH, stdin);
        books[book_count].title[strcspn(books[book_count].title, "\n")] = '\0';  // Remove the newline character

        // Ask for author name
        printf("Enter Author Name: ");
        fgets(books[book_count].author, MAX_AUTHOR_LENGTH, stdin);
        books[book_count].author[strcspn(books[book_count].author, "\n")] = '\0';  // Remove newline

         books[book_count].is_borrowed = 0;
        book_count++;

        printf("Book added successfully!\n");
    } else {
        printf("Library is full, cannot add more books.\n");
    }

}
void reserveBook() {
    int book_index;

    if (book_count == 0) {
        printf("No books available to reserve.\n");
        return;
    }

    // Ask the user to select a book number to reserve
    printf("\nEnter the book number to reserve: ");
    scanf("%d", &book_index);

    // Validate the input
    if (book_index < 1 || book_index > book_count) {
        printf("Invalid book number. Please select a valid book number from the list.\n");
        return;
    }
    book_index--;  // Adjust for 0-based index

    // Check if the book is borrowed and not reserved yet
    if (books[book_index].is_borrowed == 0) {
        printf("The book '%s' by '%s' is available and can be borrowed but not reserved.\n", books[book_index].title, books[book_index].author);
        return;
    }

    // Check if the book is already reserved
    if (books[book_index].is_reserved == 1) {
        printf("The book '%s' by '%s' is already reserved.\n", books[book_index].title, books[book_index].author);
        return;
    }

    // Reserve the book
    books[book_index].is_reserved = 1;

    // Ask for the username of the person reserving the book
    char username[MAX_USER_NAME];
    printf("Enter your username to reserve the book: ");
    scanf("%s", username);

    strcpy(books[book_index].reserved_by, username);  // Store the user who reserved the book

    printf("\nYou have successfully reserved the book '%s' by '%s'.\n", books[book_index].title, books[book_index].author);
}





void findBook() {
    char search_term[MAX_TITLE_LENGTH];
    printf("Enter book title or author to search: ");
    getchar();
    fgets(search_term, MAX_TITLE_LENGTH, stdin);
    search_term[strcspn(search_term, "\n")] = '\0';

    int found = 0;
    printf("\nSearch results:\n");

    for (int i = 0; i < book_count; i++) {
        if (strstr(books[i].title, search_term) != NULL || strstr(books[i].author, search_term) != NULL) {
            printf("%d. Title: %s, Author: %s, Status: %s\n", i + 1, books[i].title, books[i].author, books[i].is_borrowed == 0 ? "Available" : "Borrowed");
            if (books[i].is_borrowed == 1) {
                printf("   Issue Date: %s\n", books[i].issue_date);
            }
            found = 1;
        }
    }

    if (!found) {
        printf("No books found matching the search term.\n");
    }
}
// Function to display books
void displayBooks() {
    printf("\nBooks in Library:\n");

    if (book_count == 0) {
        printf("No books available.\n");
    } else {
        for (int i = 0; i < book_count; i++) {
            printf("%d. Title: %s, Author: %s, Status: ", i + 1, books[i].title, books[i].author);
            if (books[i].is_borrowed == 0) {
                printf("Available\n");
            } else {
                printf("Borrowed, Issue Date: %s\n", books[i].issue_date);
            }
        }
    }
}
void borrowBook() {
    if (book_count == 0) {
        printf("No books available to borrow.\n");
        return;
    }

    int book_index;
    displayBooks();  // Assuming this function shows the list of available books

    printf("\nEnter the book number to borrow: ");
    scanf("%d", &book_index);

    if (book_index < 1 || book_index > book_count) {
        printf("Invalid book number.\n");
        return;
    }

    book_index--;  // Adjust for 0-based index

    if (books[book_index].is_borrowed == 1) {
        printf("The book is already borrowed.\n");
        return;
    }

    // Get issue date and user details
    char issue_date[MAX_DATE_LENGTH];
    printf("Enter the issue date (dd/mm/yyyy): ");
    scanf("%s", issue_date);

    // Mark the book as borrowed and set the issue date
    books[book_index].is_borrowed = 1;
    strcpy(books[book_index].issue_date, issue_date);

    // Record borrow history
    struct BorrowHistory new_history;
    printf("Enter your username: ");
    char username[MAX_USER_NAME];
    scanf("%s", username);

    strcpy(new_history.username, username);
    strcpy(new_history.book_title, books[book_index].title);
    strcpy(new_history.issue_date, issue_date);

    borrow_history[borrow_history_count++] = new_history;

    printf("\nYou have borrowed the book '%s' by '%s'. Issue date: %s\n", books[book_index].title, books[book_index].author, issue_date);
}

// Function to view borrow history (for librarian: all, for teacher/student: own)
void viewBorrowHistory() {
    if (borrow_history_count == 0) {
        printf("No borrow history available.\n");
        return;
    }

    printf("\nBorrow History:\n");

    char username[MAX_USER_NAME];
    printf("Enter your username: ");
    scanf("%s", username);

    int found = 0;
    for (int i = 0; i < borrow_history_count; i++) {
        if (strcmp(borrow_history[i].username, username) == 0) {
            printf("Book: %s, Issue Date: %s\n",
                   borrow_history[i].book_title,
                   borrow_history[i].issue_date);
            found = 1;
        }
    }

    if (!found) {
        printf("No borrow history found for user: %s\n", username);
    }
}

// Function to return a borrowed book
void returnBook() {
    char username[MAX_USER_NAME];
    char book_title[MAX_TITLE_LENGTH];
    int found = 0;

    // Ask for the title of the book to return
    printf("Enter the title of the book you want to return: ");
    getchar();  // Consume any leftover newline character
    fgets(book_title, MAX_TITLE_LENGTH, stdin);
    book_title[strcspn(book_title, "\n")] = '\0';  // Remove newline character if any

    // Ask for the username of the user who is returning the book
    printf("Enter your username: ");
    scanf("%s", username);

    // Search the borrow history for the book borrowed by the user
    for (int i = 0; i < borrow_history_count; i++) {
        if (strcmp(borrow_history[i].username, username) == 0 &&
            strcmp(borrow_history[i].book_title, book_title) == 0) {
            // If found, mark the book as available
            for (int j = 0; j < book_count; j++) {
                if (strcmp(books[j].title, book_title) == 0) {
                    books[j].is_borrowed = 0;  // Book is now available
                    books[j].issue_date[0] = '\0';  // Clear the issue date

                    printf("You have successfully returned the book '%s' by '%s'.\n",
                           books[j].title, books[j].author);
                    found = 1;

                    // Remove the book from borrow history (by shifting)
                    for (int k = i; k < borrow_history_count - 1; k++) {
                        borrow_history[k] = borrow_history[k + 1];  // Shift left
                    }
                    borrow_history_count--;  // Decrease the borrow history count
                    break;
                }
            }
            break;  // Exit the loop if the book is found in the borrow history
        }
    }


    // If no matching borrow history is found
    if (!found) {
        printf("Sorry, the book titled '%s' is not found in your borrowed list.\n", book_title);
    }
}

// Function to manage students
void manageStudent() {
    int choice;

    printf("\nManage Students:\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Remove Student\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            if (student_count < MAX_STUDENTS) {
                char name[MAX_NAME_LENGTH], username[MAX_USER_NAME], password[MAX_PASSWORD];

                printf("Enter Student Name: ");
                getchar();  // To consume any leftover newline
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character

                printf("Enter Student Username: ");
                scanf("%s", username);

                printf("Enter Student Password: ");
                scanf("%s", password);

                // Store the student information correctly
                strcpy(students[student_count].name, name);
                strcpy(students[student_count].username, username);
                strcpy(students[student_count].password, password);
                student_count++;  // Increment the student count

                printf("Student added successfully!\n");
            } else {
                printf("Student database is full, cannot add more students.\n");
            }
            break;
        }
        case 2: {
            printf("Students List:\n");
            if (student_count == 0) {
                printf("No students available.\n");
            } else {
                for (int i = 0; i < student_count; i++) {
                    printf("Student %d: %s (Username: %s)\n", i + 1, students[i].name, students[i].username);
                }
            }
            break;
        }
        case 3: {
            char username[MAX_USER_NAME];
            printf("Enter the username of the student to remove: ");
            scanf("%s", username);

            int found = 0;
            for (int i = 0; i < student_count; i++) {
                if (strcmp(students[i].username, username) == 0) {
                    found = 1;
                    for (int j = i; j < student_count - 1; j++) {
                        students[j] = students[j + 1]; // Shift students left
                    }
                    student_count--;
                    printf("Student '%s' has been removed successfully.\n", username);
                    break;
                }
            }

            if (!found) {
                printf("Student with username '%s' not found.\n", username);
            }
            break;
        }
        case 4:
            return; // Exit the function
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}

int main() {
    int choice;
    int login_success;
    int next_step;

    welcomeMessage();

    // Main loop
    do {
        if (!is_logged_in) {  // Only show the main menu when the user is not logged in
            printf("\n\xB2\xB2   Main Menu:  \xB2\xB2\n");
            printf("1. Librarian\n");
            printf("2. Teacher\n");
            printf("3. Student\n");
            printf("4. Exit\n");
            printf("Choose an option: ");
            scanf("%d", &choice);

            if (choice == 4) {
                printf("Exiting the program...\n");
                break;
            }
        }

        // Show user type based on selection
        printf("\nYou selected ");
        if (choice == 1) printf("Librarian.\n");
        else if (choice == 2) printf("Teacher.\n");
        else if (choice == 3) printf("Student.\n");

        // Ask if they want to log in or exit
        printf("Want to log in or exit?\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &next_step);

        if (next_step == 3) {
            printf("Exiting the program...\n");
            break;
        }

        // Handle login
        if (next_step == 1) {
            login_success = login(choice);  // Call the login function

            if (login_success) {
                is_logged_in = 1;
                int logged_in_choice;

                // Start the logged-in menu
                do {
                    printf("\nLogged In Menu:\n");

                    if (choice == 1) {  // Librarian menu
                         printf("1. Add a New Book\n");
                        printf("2. Find a Book\n");
                        printf("3. Display Books\n");

                        printf("4. Borrow a Book\n");
                         printf("5. Return a Book\n");
                        printf("6. Reserve a Book\n");
                        printf("7. View Borrowing History (All)\n");
                        printf("8. Manage Students\n");
                        printf("9. Logout\n");
                    }
                     else if (choice == 2 || choice == 3) {  // Teacher or Student menu
                        printf("1. Add a New Book\n");
                        printf("2. Find a Book\n");
                        printf("3. Display Books\n");

                        printf("4. Borrow a Book\n");
                         printf("5. Return a Book\n");
                        printf("6. Reserve a Book\n");
                        printf("7. View Borrowing History (Own)\n");
                        printf("8. Manage Students\n");
                        printf("9. Logout\n");
                    }

                    // Get the user's choice
                    printf("Choose an option: ");
                    scanf("%d", &logged_in_choice);

                    // Check what the user wants to do based on the choice
                    switch (logged_in_choice) {
                        case 1:
                            addBook();  // Add a new book for everyone
                            break;
                        case 2:
                            findBook();  // Everyone can find a book
                            break;
                        case 3:
                            displayBooks();  // Everyone can display books
                            break;
                        case 4:
                            // Option 4: Borrow a Book
                            if (choice == 1) {
                                printf("Librarians cannot borrow books.\n");
                            } else {
                                borrowBook();  // Teacher/Student borrows a book
                            }
                            break;
                        case 5:
                            // Option 5: Return a Book
                            if (choice == 1) {
                                printf("Librarians cannot return books.\n");
                            } else {
                                returnBook();  // Teacher/Student returns a book
                            }
                            break;
                        case 6:
                            // Option 6: Reserve a Book
                            if (choice == 1) {
                                printf("Librarians cannot reserve books.\n");
                            } else {
                                reserveBook();  // Teacher/Student reserves a book
                            }
                            break;
                        case 7:
                            // Option 7: View Borrowing History (All or Own)
                            if (choice == 1) {
                                viewBorrowHistory(1);  // Librarian views all borrowing history
                            } else {
                                viewBorrowHistory(0);  // Teacher/Student views their own borrowing history
                            }
                            case 8:
                                if (choice == 1) {
                                        manageStudent();  // Only Librarians can manage students
                                } else {
                                 printf("Invalid choice. Only Librarians can manage students.\n");
                                 }
                                 break;
                                 case 9:
                                     // Option 9: Logout (Teacher/Student only)
                                     logout();  // Teacher/Student logs out
                                     is_logged_in = 0;  // Mark as logged out
                                     break;
                                     default:
                                         printf("Invalid choice, please try again.\n");
                                         break;
                                         }
                                         } while (is_logged_in);
                                         printf("\nLogging out... Goodbye!\n");
                                         }
        }




        else if (next_step == 2) {
            registerUser(choice);  // Pass the selected role (Librarian/Teacher/Student)

        }

    } while (1);  // Main menu continues indefinitely until exit

    // Exit the program
    printf("Thank you for using the Library Management System!\n");
    return 0;
}
