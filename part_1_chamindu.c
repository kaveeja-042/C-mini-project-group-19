//part 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>

// Threshold Definitions
#define FLOOD_THRESHOLD 100
#define RAINFALL_THRESHOLD_HIGH 50.0
#define RAINFALL_THRESHOLD_MODERATE 30.0
#define LOG_FILE "flood_log.txt"
#define PUMP_THRESHOLD 80

// Global signal flag
volatile sig_atomic_t stop_simulation = 0;

// Signal handler function
void handle_signal(int sig) {
    stop_simulation = 1;
}
