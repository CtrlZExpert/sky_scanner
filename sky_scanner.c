#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <ctype.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

void format(char *string);
int http_request(char *city);
int parse_json(char *str);
size_t write_data(void *data, size_t size, size_t nmeb, void *userdata);


int main(int argc, char *argv[]) {
    printf("----------SkyScanner----------\n");
    if (argc <  2 ) {
        printf("In valid syntax. Please enter a city name...\n");
    }
    char *city = argv[1];

    format(city);

    http_request(city);

    return 0;
}

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

int http_request(char *city) {

    CURL *curl;
    CURLcode result;
    char api[256];
    snprintf(api, sizeof(api), "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=8922a17c2def2f06a0c818c9d46c8f29&units=imperial", city);

    printf("API URL: %s\n", api);

    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -1;
    }

    response_t response;
    response.string = malloc(sizeof(char));
    response.size = 0;

    curl_easy_setopt(curl, CURLOPT_URL, api);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_data );
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

    result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Error: %s\n",  curl_easy_strerror(result));
        return -1;
    }

    //printf("%s\n", response.string);

    curl_easy_cleanup(curl);
    parse_json(response.string);

    free(response.string);

    return 0;
}

size_t write_data(void *data, size_t size, size_t nmeb, void *userdata) {
    size_t real_size = size * nmeb;

   response_t *response = (response_t *) userdata;

  char *ptr = realloc(response->string, response->size + real_size +1);
  if (ptr == NULL){
      return CURL_WRITEFUNC_ERROR;
  }
  response->string = ptr;
  memcpy(&(response->string[response->size]), data, real_size);
  response->size += real_size;
  response->string[response->size] = '\0';

    return real_size;
}

int parse_json(char *str) {
    cJSON *name = NULL;
    cJSON *weather = NULL;
    cJSON *main = NULL;
    cJSON *item = NULL;


    cJSON *json = cJSON_Parse(str);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
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
    printf("City: %s\n", name->valuestring);
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
        printf("Weather: %s\n", description->valuestring);
    }

    cJSON *temp = cJSON_GetObjectItemCaseSensitive(main, "temp");
    if (temp == NULL) {
        printf("Error: 'temp' field not found\n");
        return 1;
    }
    printf("Tempature: %lf\n", temp->valuedouble);
    cJSON *humidity = cJSON_GetObjectItemCaseSensitive(main, "humidity");
    if (humidity == NULL) {
        printf("Error: 'humidity' field not found\n");
        return 1;
    }
    printf("Humidity: %d\n", humidity->valueint);

    cJSON_Delete(json);
    return 0;
}
