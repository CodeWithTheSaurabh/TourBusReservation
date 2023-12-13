#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TourBus {
    int bid;
    char destination[200];
    char time[50];
    int max_seats;
    int booked;
    int fare;
};

struct Ticket {
    char name[50];
    struct TourBus bus;
};

void input(struct TourBus *b) {
    printf("Enter bus id: ");
    scanf("%d", &(b->bid));
    printf("Enter bus destination: ");
    scanf(" %[^\n]", b->destination);
    printf("Enter time of bus: ");
    scanf("%s", b->time);
    printf("Enter fare of the bus: ");
    scanf("%d", &(b->fare));
}

void displayTourBus(struct TourBus *b) {
    printf("%d\t%s\t%s\t%d\t%d\t%d\n", b->bid, b->destination, b->time, b->max_seats, b->booked, b->fare);
}

void showTourBus(struct TourBus *b) {
    printf("Bus Id: %d\n", b->bid);
    printf("Destination: %s\n", b->destination);
    printf("Time: %s\n", b->time);
    printf("No. of seats remaining: %d\n", b->max_seats - b->booked);
}

void writeToFile(struct TourBus *b) {
    FILE *file = fopen("tour.dat", "ab");
    if (file == NULL) {
        printf("Can't open file\n");
        return;
    }

    input(b);
    fwrite(b, sizeof(struct TourBus), 1, file);

    fclose(file);
    printf("Bus added Successfully\n");
    getchar(); // Ignore the newline character left in the buffer
    getchar(); // Wait for user input
    system("clear"); // Use system("clear") for clearing the console
}

void displayAllBuses() {
    FILE *file = fopen("tour.dat", "rb");
    if (file == NULL) {
        printf("Can't open file\n");
        return;
    }

    struct TourBus bus;
    while (fread(&bus, sizeof(struct TourBus), 1, file) == 1) {
        displayTourBus(&bus);
    }

    fclose(file);
    printf("Press a key to continue\n");
    getchar(); // Ignore the newline character left in the buffer
    getchar(); // Wait for user input
    system("clear"); // Use system("clear") for clearing the console
}

void deleteBus(int id) {
    int found = 0;
    FILE *inFile = fopen("tour.dat", "rb");
    FILE *outFile = fopen("temp.dat", "wb");

    if (inFile == NULL || outFile == NULL) {
        printf("Can't open file\n");
        return;
    }

    struct TourBus bus;
    while (fread(&bus, sizeof(struct TourBus), 1, inFile) == 1) {
        if (bus.bid != id) {
            fwrite(&bus, sizeof(struct TourBus), 1, outFile);
        } else {
            showTourBus(&bus);
            found = 1;
        }
    }

    if (found == 0) {
        printf("Bus not found\n");
    } else {
        printf("Bus deleted\n");
    }

    fclose(inFile);
    fclose(outFile);

    remove("tour.dat");
    rename("temp.dat", "tour.dat");
}

int main() {
    int choice;
    struct TourBus b;

    do {
        system("clear"); // Use system("clear") for clearing the console

        printf("Press 1 - Add a New Tour Bus\n");
        printf("Press 2 - Show Selected Bus\n");
        printf("Press 3 - Display All Buses\n");
        printf("Press 4 - Delete a Bus\n");
        printf("Press 5 - Book a ticket\n");
        printf("Press 6 - Display Booked Tickets\n");
        printf("Press 7 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                writeToFile(&b);
                break;
            case 3:
                displayAllBuses();
                break;
            case 4: {
    int idToDelete;
    printf("Enter the bus id to be deleted: ");
    scanf("%d", &idToDelete);
    deleteBus(idToDelete);
    break;
}

            // ... (remaining cases)
        }
        
    } while (choice != 7);

    return 0;
}
