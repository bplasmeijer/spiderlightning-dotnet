#ifndef __BINDINGS_HTTP_TYPES_H
#define __BINDINGS_HTTP_TYPES_H
#ifdef __cplusplus
extern "C"
{
  #endif
  
  #include <stdint.h>
  #include <stdbool.h>
  
  typedef struct {
    char *ptr;
    size_t len;
  } http_types_string_t;
  
  void http_types_string_set(http_types_string_t *ret, const char *s);
  void http_types_string_dup(http_types_string_t *ret, const char *s);
  void http_types_string_free(http_types_string_t *ret);
  // The HTTP status code.
  typedef uint16_t http_types_http_status_t;
  // The HTTP body.
  typedef struct {
    uint8_t *ptr;
    size_t len;
  } http_types_body_t;
  void http_types_body_free(http_types_body_t *ptr);
  typedef struct {
    http_types_string_t f0;
    http_types_string_t f1;
  } http_types_tuple2_string_string_t;
  void http_types_tuple2_string_string_free(http_types_tuple2_string_string_t *ptr);
  // The HTTP headers represented as a list of (name, value) pairs.
  typedef struct {
    http_types_tuple2_string_string_t *ptr;
    size_t len;
  } http_types_headers_t;
  void http_types_headers_free(http_types_headers_t *ptr);
  // The HTTP parameter queries, represented as a list of (name, value) pairs.
  typedef struct {
    http_types_tuple2_string_string_t *ptr;
    size_t len;
  } http_types_params_t;
  void http_types_params_free(http_types_params_t *ptr);
  // The HTTP URI of the current request.
  typedef http_types_string_t http_types_uri_t;
  void http_types_uri_free(http_types_uri_t *ptr);
  // The HTTP method.
  typedef uint8_t http_types_method_t;
  #define HTTP_TYPES_METHOD_GET 0
  #define HTTP_TYPES_METHOD_POST 1
  #define HTTP_TYPES_METHOD_PUT 2
  #define HTTP_TYPES_METHOD_DELETE 3
  #define HTTP_TYPES_METHOD_PATCH 4
  #define HTTP_TYPES_METHOD_HEAD 5
  #define HTTP_TYPES_METHOD_OPTIONS 6
  typedef struct {
    bool is_some;
    http_types_body_t val;
  } http_types_option_body_t;
  void http_types_option_body_free(http_types_option_body_t *ptr);
  // An HTTP request.
  typedef struct {
    http_types_method_t method;
    http_types_uri_t uri;
    http_types_headers_t headers;
    http_types_params_t params;
    http_types_option_body_t body;
  } http_types_request_t;
  void http_types_request_free(http_types_request_t *ptr);
  typedef struct {
    bool is_some;
    http_types_headers_t val;
  } http_types_option_headers_t;
  void http_types_option_headers_free(http_types_option_headers_t *ptr);
  // An HTTP response.
  typedef struct {
    http_types_http_status_t status;
    http_types_option_headers_t headers;
    http_types_option_body_t body;
  } http_types_response_t;
  void http_types_response_free(http_types_response_t *ptr);
  // HTTP errors returned by the runtime.
  typedef struct {
    uint8_t tag;
    union {
      http_types_string_t invalid_url;
      http_types_string_t timeout_error;
      http_types_string_t protocol_error;
      uint16_t status_error;
      http_types_string_t unexpected_error;
    } val;
  } http_types_http_error_t;
  #define HTTP_TYPES_HTTP_ERROR_INVALID_URL 0
  #define HTTP_TYPES_HTTP_ERROR_TIMEOUT_ERROR 1
  #define HTTP_TYPES_HTTP_ERROR_PROTOCOL_ERROR 2
  #define HTTP_TYPES_HTTP_ERROR_STATUS_ERROR 3
  #define HTTP_TYPES_HTTP_ERROR_UNEXPECTED_ERROR 4
  void http_types_http_error_free(http_types_http_error_t *ptr);
  // HTTP errors returned by the runtime.
  typedef struct {
    uint8_t tag;
    union {
      http_types_string_t invalid_url;
      http_types_string_t timeout_error;
      http_types_string_t protocol_error;
      http_types_http_status_t status_error;
      http_types_string_t unexpected_error;
    } val;
  } http_types_http_router_error_t;
  #define HTTP_TYPES_HTTP_ROUTER_ERROR_INVALID_URL 0
  #define HTTP_TYPES_HTTP_ROUTER_ERROR_TIMEOUT_ERROR 1
  #define HTTP_TYPES_HTTP_ROUTER_ERROR_PROTOCOL_ERROR 2
  #define HTTP_TYPES_HTTP_ROUTER_ERROR_STATUS_ERROR 3
  #define HTTP_TYPES_HTTP_ROUTER_ERROR_UNEXPECTED_ERROR 4
  void http_types_http_router_error_free(http_types_http_router_error_t *ptr);
  #ifdef __cplusplus
}
#endif
#endif
