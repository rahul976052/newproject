/* 2. Student: Rahul (Oxford)
Project Title: Vehicle Service Booking System Objective: Manage service bookings for vehicles. Key Features:
Book/modify/cancel service slots
Search by vehicle number
Display upcoming services
Concepts Applied: File handling, structures, date input, conditional checks
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// structure me number and owner ka name and service date booking 
struct Booking {
    char vehicleNumber[20];
    char ownerName[50];
    char serviceDate[15];
};

void bookService() {
    struct Booking b;
    // data store karne ke liye file ka use kare hai
    FILE *fp = fopen("bookings.txt", "a");
  // input ke printf ka use kiye hai
    printf("Enter Vehicle Number: ");
    scanf("%s", b.vehicleNumber);
    getchar(); // to clear newline
    printf("Enter Owner Name:\n ");
    fgets(b.ownerName, sizeof(b.ownerName), stdin);
    strtok(b.ownerName, "\n"); // remove newline
    printf("Enter Service Date (YYYY-MM-DD): ");
    scanf("%s", b.serviceDate);
  // fprintf ka use data ke print karene ke liye kiye hai
    fprintf(fp, "%s,%s,%s\n", b.vehicleNumber, b.ownerName, b.serviceDate);
    fclose(fp);
    printf("Booking Successful!\n");
}
//  display par booking dekhane ke liye fuction use kiye hai
void displayBookings() {
    FILE *fp = fopen("bookings.txt", "r");
    char line[200];
 // printf kane ke liye upcoming ka use kiye ka
    printf("Upcoming Bookings:\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}
 //user ko search kane ke liye fuction ka use kiye hai
void searchBooking() {
    FILE *fp = fopen("bookings.txt", "r");
    char line[200], search[20];
    int found = 0;
    // input serch ke liye 
    printf("Enter Vehicle Number to Search: ");
    scanf("%s", search);
    // vehcle ke number search ke liye loop ka use kiye hai
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, search)) {
            printf("Booking Found: %s", line);
            found = 1;
        }
    }
    // fir conditiion use kiye hai booking found ka
    if (!found) {
        printf("No booking found for %s\n", search);
    }
    fclose(fp);
}
// fir function ka use kiye hai jo cancel ke liye
void cancelBooking() {
    FILE *fp = fopen("bookings.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[200], search[20];
    int found = 0;
    // disolay par printf karne ke liye printf ka use kiye hai
    printf("Enter Vehicle Number to Cancel: ");
    scanf("%s", search);
    // fir loop ka use kiye hai jo ki cancel search ke khogne ke liye
    while (fgets(line, sizeof(line), fp)) {
        if (!strstr(line, search)) {
            fputs(line, temp);
        } else {
            found = 1;
        }
    }
    // fclose use kiye colse kane ke liye 
    fclose(fp);
    fclose(temp);
    // detaile ke remove ka use kiye
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    // condtion ke use booking ke cancel ke liye kiye hai
    if (found) printf("Booking cancelled successfully.\n");
    else printf("Booking not found.\n");
}
// display par print kar ke choice karne ke liye printf kiye hai
void menu() {
    int choice;
    do {
        printf("\n--- Vehicle Service Booking System ---\n");
        printf("1. Book Service\n");
        printf("2. View All Bookings\n");
        printf("3. Search Booking\n");
        printf("4. Cancel Booking\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        // switch case ka use ke choice ke liye kiye hai
        switch(choice) {
            case 1: bookService(); break;
            case 2: displayBookings(); break;
            case 3: searchBooking(); break;
            case 4: cancelBooking(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}
// int main ka use kiye hai sab ko menu data ko print kanwane ke liye
int main() {
    menu();
    return 0;
}

