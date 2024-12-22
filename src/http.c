#include <stdio.h>
#include "http.h"


int http_request(char *city) {

    CURL *curl;
    CURLcode result;
    char api[256];
    snprintf(api, sizeof(api), "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=8922a17c2def2f06a0c818c9d46c8f29&units=imperial", city);

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
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
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
