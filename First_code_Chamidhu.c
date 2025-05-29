#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>

#define FLOOD_THRESHOLD 100  // Flood threshold in cm
#define RAINFALL_THRESHOLD_HIGH 50.0  // High risk threshold in mm
#define RAINFALL_THRESHOLD_MODERATE 30.0  // Moderate risk threshold in mm
#define LOG_FILE "flood_log.txt"
#define PUMP_THRESHOLD 80  // Threshold to activate water pump

// Function prototypes
void monitor_water_level();
void predict_flood_risk();
void control_water_pump();
void log_water_level();
void send_sms_alert();
void simulate_flood_time_based();
void manual_input_simulation();
void log_simulation_data();
void display_menu();

// Signal handler for stopping simulation safely
volatile sig_atomic_t stop_simulation = 0;

void handle_signal(int sig) {
    stop_simulation = 1;
}

int main() {
    srand(time(0)); // Initialize random seed

    int choice;
    char c;

    do {
        display_menu();
        printf("Enter your choice (1-8, 0 to exit): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: monitor_water_level(); break;
            case 2: predict_flood_risk(); break;
            case 3: control_water_pump(); break;
            case 4: log_water_level(); break;
            case 5: send_sms_alert(); break;
            case 6: simulate_flood_time_based(); break;
            case 7: manual_input_simulation(); break;
            case 8: log_simulation_data(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while ((c = getchar()) != '\n' && c != EOF);
            getchar();
        }

    } while (choice != 0);

    return 0;
}