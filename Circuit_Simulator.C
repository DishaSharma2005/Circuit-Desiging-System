#include <stdio.h>
#include <stdbool.h> // To use boolean in C

// Struct definition for Resistors
struct Resistors {
    float resistance;
    float current;
};

// Function declarations
void Welcome_Message();
void Input_ValueResistance(int numResistors, struct Resistors Resistor[]);
void Print_Values(int numResistors, struct Resistors Resistor[]);
float Choice_SeriesConnections(int numResistors, struct Resistors Resistor[], bool map[]);
float Choice_ParallelConnections(int numResistors, struct Resistors Resistor[], bool map[]);
void Confirm(int numResistors, struct Resistors Resistor[], bool map[], float totalSeries, float totalParallel, float voltage);
void Calculate_Current(int numResistors, struct Resistors Resistor[], float voltage);
void Calculate_VoltageDrop(int numResistors, struct Resistors Resistor[], float current);
void Reset_Map(int numResistors, bool map[]);

int main() {
    int numResistors;
    float voltage;
    Welcome_Message();

    // Input number of resistors
    printf("Enter the number of resistors: ");
    scanf("%d", &numResistors);

    // Input Voltage 
    printf("Enter the voltage: ");
    scanf("%f", &voltage);

    // Create an array of struct Resistors
    struct Resistors Resistor[numResistors];

    // Create an array map to track if choice is already used or not
    bool map[numResistors];
    Reset_Map(numResistors, map);

    // Call functions
    Input_ValueResistance(numResistors, Resistor);
    Print_Values(numResistors, Resistor);

    float totalSeries = Choice_SeriesConnections(numResistors, Resistor, map);
    float totalParallel = Choice_ParallelConnections(numResistors, Resistor, map);

    Confirm(numResistors, Resistor, map, totalSeries, totalParallel, voltage);

    return 0;
}

// Confirmation function
void Confirm(int numResistors, struct Resistors Resistor[], bool map[], float totalSeries, float totalParallel, float voltage) {
    char confirm;
    printf("Do you confirm the connections? Enter Y/y for Yes, N/n for No: ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        float totalResistance = totalSeries + (totalParallel > 0 ? 1.0 / totalParallel : 0);
        printf("Total resistance offered by circuit: %.2f Ohms\n", totalResistance);

        // Calculate and display current
        float totalCurrent = voltage / totalResistance;
        printf("Total current through the circuit: %.2f A\n", totalCurrent);
        Calculate_Current(numResistors, Resistor, voltage);
        Calculate_VoltageDrop(numResistors, Resistor, totalCurrent);
    } else if (confirm == 'n' || confirm == 'N') {
        printf("Re-enter the connections:\n");
        Reset_Map(numResistors, map);
        float totalSeries = Choice_SeriesConnections(numResistors, Resistor, map);
        float totalParallel = Choice_ParallelConnections(numResistors, Resistor, map);
        Confirm(numResistors, Resistor, map, totalSeries, totalParallel, voltage);
    } else {
        printf("Invalid input. Please try again.\n");
        Confirm(numResistors, Resistor, map, totalSeries, totalParallel, voltage);
    }
}

// Welcome Message 
void Welcome_Message() {
    printf("Hello! This side Disha, Creator of the project\n");
    printf("Let me tell you what my project is about:\n");
    printf("1. Enter the number of resistors\n");
    printf("2. Enter the value of Resistors\n");
    printf("3. Enter the choice of series\n");
    printf("4. Enter the choice of parallel\n");
    printf("5. Confirm after reviewing the connections\n");
    printf("6. Get the total resistance, Current, Resistance at each resistor\n");
    printf("7. Get the circuit design\n");
}

// Function to input resistance values
void Input_ValueResistance(int numResistors, struct Resistors Resistor[]) {
    for (int i = 0; i < numResistors; i++) {
        printf("Enter the resistance (in Ohms) of resistor %d: ", i + 1);
        scanf("%f", &Resistor[i].resistance);
        Resistor[i].current = 0; // Initialize current to 0
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
float Choice_SeriesConnections(int numResistors, struct Resistors Resistor[], bool map[]) {
    printf("Enter the indices of resistors to connect in series (1 to %d), or -1 to stop:\n", numResistors);
    float totalSeries = 0;
    int choice;
    while (1) {
        scanf("%d", &choice);
        if (choice == -1) {
            break; // Exit the loop when the user enters -1
        }
        if (choice >= 1 && choice <= numResistors) {
            if (map[choice - 1]) {
                printf("Choice already used for Resistor %d.\n", choice);
            } else {
                map[choice - 1] = true;
                totalSeries += Resistor[choice - 1].resistance; // Adjust for 0-based index
            }
        } else {
            printf("Invalid choice. Please enter a valid resistor index.\n");
        }
    }
    return totalSeries;
}

// Function to calculate total resistance in parallel based on user choice
float Choice_ParallelConnections(int numResistors, struct Resistors Resistor[], bool map[]) {
    printf("Enter the indices of resistors to connect in parallel (1 to %d), or -1 to stop:\n", numResistors);
    float reciprocalTotalParallel = 0;
    int choice;
    while (1) {
        scanf("%d", &choice);
        if (choice == -1) {
            break; // Exit the loop when the user enters -1
        }
        if (choice >= 1 && choice <= numResistors) {
            if (map[choice - 1]) {
                printf("Choice already used for Resistor %d.\n", choice);
            } else {
                map[choice - 1] = true;
                reciprocalTotalParallel += 1.0 / Resistor[choice - 1].resistance; // Adjust for 0-based index
            }
        } else {
            printf("Invalid choice. Please enter a valid resistor index.\n");
        }
    }
    return reciprocalTotalParallel;
}

// Function to calculate and display current through each resistor
void Calculate_Current(int numResistors, struct Resistors Resistor[], float voltage) {
    printf("Current through each resistor:\n");
    for (int i = 0; i < numResistors; i++) {
        Resistor[i].current = voltage / Resistor[i].resistance;
        printf("Resistor %d: %.2f A\n", i + 1, Resistor[i].current);
    }
}

// Function to calculate and display voltage drop across each resistor
void Calculate_VoltageDrop(int numResistors, struct Resistors Resistor[], float current) {
    printf("\nVoltage Drops across each Resistor:\n");
    for (int i = 0; i < numResistors; i++) {
        float voltageDrop = current * Resistor[i].resistance;
        printf("Resistor %d: %.2f V\n", i + 1, voltageDrop);
    }
}

// Function to reset the map array
void Reset_Map(int numResistors, bool map[]) {
    for (int i = 0; i < numResistors; i++) {
        map[i] = false;
    }
}
