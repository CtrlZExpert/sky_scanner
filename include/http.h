#pragma once

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "json_parser.h"
#include "color.h"

typedef struct Response response_t;

typedef struct Response{
    char *string;
    size_t size;
} response_t;

int http_request(char *city);

size_t write_data(void *data, size_t size, size_t nmeb, void *userdata);
