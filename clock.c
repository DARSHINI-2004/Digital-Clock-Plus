#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_ALARMS 5

struct Alarm {
    int hour;
    int min;
    int sec;
    int enabled;
};

struct Timer {
    int hour;
    int min;
    int sec;
    int running;
};

struct Stopwatch {
    time_t start_time;
    time_t elapsed_time;
};

struct Alarm alarms[MAX_ALARMS];
struct Timer timer;
struct Stopwatch stopwatch;

void print_time(struct tm* tm) {
    printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void set_alarm(int index) {
    printf("Enter the alarm time (hours, minutes, seconds): ");
    scanf("%d %d %d", &alarms[index].hour, &alarms[index].min, &alarms[index].sec);
    alarms[index].enabled = 1;
}

void disable_alarm(int index) {
    alarms[index].enabled = 0;
}

int check_alarms() {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);

    for (int i = 0; i < MAX_ALARMS; i++) {
        if (alarms[i].enabled && alarms[i].hour == tm->tm_hour && alarms[i].min == tm->tm_min && alarms[i].sec == tm->tm_sec) {
            return i;
        }
    }

    return -1;
}

void print_alarms() {
    printf("Alarms:\n");
    for (int i = 0; i <MAX_ALARMS;i++) {
        printf("%d: %02d:%02d:%02d %s\n", i + 1, alarms[i].hour, alarms[i].min, alarms[i].sec, alarms[i].enabled ? "Enabled" : "Disabled");
    }
}

void start_timer() {
    timer.running = 1;
    timer.hour = 0;
    timer.min = 0;
    timer.sec = 0;
}

void stop_timer() {
    timer.running = 0;
}

void print_timer() {
    if (timer.running) {
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);

        timer.sec++;
        if (timer.sec >= 60) {
            timer.min++;
            timer.sec = 0;
        }
        if (timer.min >= 60) {
            timer.hour++;
            timer.min = 0;
        }
        if (timer.hour >= 24) {
            timer.hour = 0;
        }

        print_time(tm);
        printf("Timer: %02d:%02d:%02d\n", timer.hour, timer.min, timer.sec);
    } else {
        print_time(localtime(&stopwatch.elapsed_time));
        printf("Timer: Stopped\n");
    }
}

void start_stopwatch() {
    stopwatch.start_time = time(NULL);
    stopwatch.elapsed_time = 0;
}

void stop_stopwatch() {
    time_t t = time(NULL);
    stopwatch.elapsed_time += t - stopwatch.start_time;
}

void print_stopwatch() {
    time_t t = time(NULL);
    stopwatch.elapsed_time += t - stopwatch.start_time;

    double elapsed_seconds = difftime(stopwatch.elapsed_time, stopwatch.start_time);
    int h = (int)elapsed_seconds / 3600;
    int m = (int)elapsed_seconds / 60 - h * 60;
    int s = (int)elapsed_seconds - h * 3600 - m * 60;

    print_time(localtime(&stopwatch.elapsed_time));
    printf("Stopwatch: %02d:%02d:%02d\n", h, m, s);
}

int main() {
    int choice;
    int alarm_index;

    for (int i = 0; i < MAX_ALARMS; i++) {
        alarms[i].enabled = 0;
    }

    start_stopwatch();

    while (1) {
        printf("\nDigital Clock\n");
        printf("1. Set Alarm\n");
        printf("2. Disable Alarm\n");
        printf("3. Check Alarms\n");
        printf("4. Print Alarms\n");
        printf("5. Start Timer\n");
        printf("6. Stop Timer\n");
        printf("7. Print Timer\n");
        printf("8. Start Stopwatch\n");
        printf("9. Stop Stopwatch\n");
        printf("10. Print Stopwatch\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the alarm index: ");
                scanf("%d", &alarm_index);
                if (alarm_index < 1 || alarm_index > MAX_ALARMS) {
                    printf("Invalid alarm index\n");
                    break;
                }
                set_alarm(alarm_index - 1);
                break;
            case 2:
                printf("Enter the alarm index: ");
                scanf("%d", &alarm_index);
                if (alarm_index < 1 || alarm_index > MAX_ALARMS) {
                    printf("Invalid alarm index\n");
                    break;
}
                disable_alarm(alarm_index - 1);
                break;
            case 3:
                alarm_index = check_alarms();
                if (alarm_index < 0) {
                    printf("No alarms set\n");
                } else {
                    printf("Alarm %d is ringing\n", alarm_index + 1);
                }
                break;
            case 4:
                print_alarms();
                break;
            case 5:
                start_timer();
                break;
            case 6:
                stop_timer();
                break;
            case 7:
                print_timer();
                break;
            case 8:
                start_stopwatch();
                break;
            case 9:
                stop_stopwatch();
                break;
            case 10:
                print_stopwatch();
                break;
            case 11:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}