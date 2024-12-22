#include "utility.h"

void format(char *string){
    int length = strlen(string);
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (!isspace(string[i])) {
            string[j] = string[i];
           j++;
        }
        if (isspace(string[i])) {
            string[j] = '+';
            j++;
        }
    }
    string[j] = '\0';
}
