#include <stdio.h>
#include <curl/curl.h>

int http_request(void) {

    CURL *curl;
    CURLcode result;

    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL,"https://www.google.com");

    result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Error: %s\n",  curl_easy_strerror(result));
        return -1;
    }

    curl_easy_cleanup(curl);


    return 0;
}
int main(int argc, char *argv[]) {
    printf("----------SkyScanner----------\n");
    if (argc <  2 ) {
        printf("In valid syntax. Please enter a city name...\n");
    }
    char *city = argv[1];
    printf("You entered: %s",city );

    http_request();


    return 0;
}
