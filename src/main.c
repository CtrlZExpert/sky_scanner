#include <stdio.h>
#include "color.h"
#include "utility.h"
#include "http.h"
#include "json_parser.h"
#include "display.h"

int main(int argc, char *argv[]) {
    printf(CYAN"----------SkyScanner----------\n"RESET);
    if (argc <  2 ) {
        printf("In valid syntax. Please enter a city name...\n");
    }
    char *city = argv[1];

    format(city);

    http_request(city);

    return 0;
}
