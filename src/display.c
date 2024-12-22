#include <stdio.h>
#include "display.h"

char *display_city(char *str){
    printf("Weather "BLUE"in"YELLOW" %s"RESET":\n", str);
    return 0;
}

char *display_condition(char *str) {
    printf(RED"Condition: "RESET"%s\n", str);
    return 0;
}

double display_tempature(double num){
    printf(RED"Temperate: "MAGENTA"%.2f"RESET"°F\n", num);
    return 0;
}

int display_humidity(int num){
    printf(RED"Humidity: "MAGENTA"%d"RESET"%%\n", num);
    return 0;
}
