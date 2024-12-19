#include <stdio.h>

// Struct definition for Resistors
struct Resistors {
    float resistance;
};

// Function declarations
void Input_ValueResistance(int numResistors, struct Resistors Resistor[]);
void Print_Values(int numResistors, struct Resistors Resistor[]);
float Choice_SeriesConnections(int numResistors, struct Resistors Resistor[]);
float Choice_ParallelConnections(int numResistors, struct Resistors Resistor[]);

int main() {
    int numResistors;
   
    // Input number of resistors
    printf("Enter the number of resistors: ");
    scanf("%d", &numResistors);
    
    // Create an array of struct Resistors
    struct Resistors Resistor[numResistors];
    
    // Call functions
    Input_ValueResistance(numResistors, Resistor);
    Print_Values(numResistors, Resistor);
    float totalResistance = Choice_SeriesConnections(numResistors, Resistor)+Choice_ParallelConnections(numResistors,Resistor);
    printf("Total resistance offered by circuit : %.2f Ohms\n", totalResistance);
    
    return 0;
}

// Function to input resistance values
void Input_ValueResistance(int numResistors, struct Resistors Resistor[]) {
    for (int i = 0; i < numResistors; i++) {
        printf("Enter the resistance (in Ohms) of resistor %d: ", i + 1);
        scanf("%f", &Resistor[i].resistance);
    }
}

// Function to print the entered resistance values
void Print_Values(int numResistors, struct Resistors Resistor[]) {
    printf("The resistance values entered are:\n");
    for (int i = 0; i < numResistors; i++) {
        printf("Resistor %d: %.2f Ohms\n", i + 1, Resistor[i].resistance);
    }
}

// Function to calculate total resistance in series based on user choice
float Choice_SeriesConnections(int numResistors, struct Resistors Resistor[]) {
    printf("Enter the indices of resistors to connect in series (1 to %d), or -1 to stop:\n", numResistors);
    float totalSeries = 0;
    int choice;
    while (1) {// Always true condition only by entering -1 makes u out of loop 

        scanf("%d", &choice);
        if (choice == -1) {
            break; // Exit the loop when the user enters -1
        }
        if (choice >= 1 && choice <= numResistors) {
            totalSeries += Resistor[choice - 1].resistance; // Adjust for 0-based index
        } else {
            printf("Invalid choice. Please enter a valid resistor index.\n");
        }
    }
    return totalSeries;
}
// Function to calculate total resistance in parallel based on user choice
float Choice_ParallelConnections(int numResistors, struct Resistors Resistor[]) {
    printf("Enter the indices of resistors to connect in series (1 to %d), or -1 to stop:\n", numResistors);
    float totalParallel = 0;
    int choice;
    while (1) {// Always true condition only by entering -1 makes u out of loop 

        scanf("%d", &choice);
        if (choice == -1) {
            break; // Exit the loop when the user enters -1
        }
        if (choice >= 1 && choice <= numResistors) {
            totalParallel += 1/(Resistor[choice - 1].resistance); // Adjust for 0-based index
        } else {
            printf("Invalid choice. Please enter a valid resistor index.\n");
        }
    }
    return totalParallel;
}
