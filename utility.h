#include <stdio.h>

typedef struct Response response_t;

typedef struct Response{
    char *string;
    size_t size;
} response_t;

int http_request(char *city);
