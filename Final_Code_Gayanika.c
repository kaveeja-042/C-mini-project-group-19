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

void display_menu() {
    printf("\n===== Flood Monitoring System =====\n");
    printf("1. Monitor Water Level (Manual Input)\n");
    printf("2. Predict Flood Risk (Rainfall Analysis)\n");
    printf("3. Control Water Pump\n");
    printf("4. Log Water Level Data\n");
    printf("5. Send SMS Alert\n");
    printf("6. Simulate Flood (Time-Based Pattern)\n");
    printf("7. Manual Input Simulation\n");
    printf("8. Log Simulation Data\n");
    printf("0. Exit\n");
}

void monitor_water_level() {
    int water_level;
    printf("\n==== Water Level Monitoring ====\n");
    printf("Enter current water level (cm): ");
    scanf("%d", &water_level);

    if (water_level >= FLOOD_THRESHOLD) {
        printf("\n\aALERT! Flood risk detected!\n");
    } else {
        printf("\nWater level normal.\n");
    }
}

void predict_flood_risk() {
    float last_24h_rainfall;
    printf("\n==== Flood Risk Prediction ====\n");
    printf("Enter rainfall in last 24 hours (mm): ");
    scanf("%f", &last_24h_rainfall);

    if (last_24h_rainfall > RAINFALL_THRESHOLD_HIGH) {
        printf("Warning: High flood risk!\n");
    } else if (last_24h_rainfall > RAINFALL_THRESHOLD_MODERATE) {
        printf("Moderate risk. Monitor water levels.\n");
    } else {
        printf("Low risk.\n");
    }
}

void control_water_pump() {
    int water_level;
    printf("\n==== Water Pump Controller ====\n");
    printf("Enter current water level (cm): ");
    scanf("%d", &water_level);

    if (water_level > PUMP_THRESHOLD) {
        printf("Pump ON: Draining water...\n");
    } else {
        printf("Pump OFF.\n");
    }
}

void log_water_level() {
    int level;
    printf("\n==== Data Logging ====\n");
    printf("Enter current water level: ");
    scanf("%d", &level);

    FILE *f = fopen(LOG_FILE, "a");
    if (f == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    time_t now = time(NULL);
    fprintf(f, "%s | Water level: %d cm\n", ctime(&now), level);
    fclose(f);

    printf("Data logged successfully.\n");
}

void send_sms_alert() {
    int level;
    printf("\n==== SMS Alert System ====\n");
    printf("Enter water level: ");
    scanf("%d", &level);

    if (level > FLOOD_THRESHOLD) {
        printf("SMS Sent: FLOOD ALERT! Evacuate immediately!\n");
    } else {
        printf("No alert sent - water level normal.\n");
    }
}

void simulate_flood_time_based() {
    signal(SIGINT, handle_signal); // Capture Ctrl+C
    int time_elapsed = 0;
    printf("\n==== Flood Simulation (Time-Based) ====\n");
    printf("Simulation running... Press Ctrl+C to stop.\n");

    for (int x=1;x<6;x++) {
        printf("\a");  // Beep sound before displaying level
        int water_level = 50 + (time_elapsed % 50);
        printf("Level: %d cm\n", water_level);

        if (water_level > FLOOD_THRESHOLD) {
            printf("\aALERT: Flood risk!\n"); // Additional beep for alert
        }

        time_elapsed++;
        sleep(1);
    }

    printf("\nSimulation stopped safely.\n");
}

void manual_input_simulation() {
    printf("\n==== Manual Input Simulation ====\n");
    printf("Enter water levels manually (Ctrl+C to stop)\n");

    for (int x = 1; x < 6; x++) {
        printf("\a"); // Beep before input prompt
        int level;
        printf("Enter water level (cm): ");
        scanf("%d", &level);

        if (level > FLOOD_THRESHOLD) {
            printf("\aFLOOD WARNING!\n"); // Additional beep for alert
        }
    }
}

void log_simulation_data() {
    printf("\n==== Simulation Data Logging ====\n");
    printf("Logging random water levels to file... Press Ctrl+C to stop.\n");

    FILE *log = fopen("simulation_log.txt", "a");
    if (log == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    while (!stop_simulation) {
        int level = rand() % 150;
        time_t now = time(NULL);
        fprintf(log, "%s | Level: %d cm\n\n", ctime(&now), level);
        fflush(log);
        sleep(1);
    }

    fclose(log);
}