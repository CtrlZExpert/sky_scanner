#include <stdio.h>
#include "json_parser.h"
#include "display.h"


int parse_json(char *str) {
    cJSON *name = NULL;
    cJSON *weather = NULL;
    cJSON *main = NULL;
    cJSON *item = NULL;


    cJSON *json = cJSON_Parse(str);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n",  error_ptr);
        }
        cJSON_Delete(json);
        return 1;
    }
    name = cJSON_GetObjectItemCaseSensitive(json, "name");
    weather = cJSON_GetObjectItemCaseSensitive(json, "weather");
    main = cJSON_GetObjectItemCaseSensitive(json,"main");
    if (name == NULL) {
        printf("Error: 'name' field not found\n");
        return 1;
    }
    display_city(name->valuestring);
    if (weather == NULL) {
        printf("Error: 'weather' field not found\n");
        return 1;
    }
    cJSON_ArrayForEach(item, weather){
        cJSON *description = cJSON_GetObjectItemCaseSensitive(item, "description");
        if (description == NULL) {
            printf("Error: 'description' field not found\n");
            return 1;
        }
        display_condition(description->valuestring);
    }

    cJSON *temp = cJSON_GetObjectItemCaseSensitive(main, "temp");
    if (temp == NULL) {
        printf("Error: 'temp' field not found\n");
        return 1;
    }
    display_tempature(temp->valuedouble);
    cJSON *humidity = cJSON_GetObjectItemCaseSensitive(main, "humidity");
    if (humidity == NULL) {
        printf("Error: 'humidity' field not found\n");
        return 1;
    }
    display_humidity(humidity->valueint);
    cJSON_Delete(json);
    return 0;
}
