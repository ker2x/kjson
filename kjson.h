#ifndef __KJSON_H_
#define __KJSON_H_

/* *MUST* be strictly inferior than UINT_MAX */
#define BUF_SIZE 65535
#define MAX_TOKEN 256



/* declare json value type */
typedef enum {
	KJSON__NULL_T,		/* the null type */
	KJSON_PRIMITIVE_T,	/* numeric, bool */
	KJSON_OBJECT_T,		/* a json object { ... } */
	KJSON_ARRAY_T,		/* an array [ ... ] */
	KJSON_STRING_T		/* a string "foo" */
} kjson_type_t;

/* declare error code returned by parser */
typedef enum {
	KJSON_SUCCESS_E,	/* no error */
	KJSON_OOM_E,		/* out of memory */
	KJSON_INVALID_E,	/* invalid json format */
	KJSON_EOF_E		/* unexpected end of file : more byte expected / incomplete json */
} kjson_err_t;



/* token structure */
typedef struc {
	kjson_type_t,		/* type of the token */
	signed int start,	/* start position in json string */
	signed int end,		/* end position in json */
	signed int size,	/* number of child token */
	signed int parent	/* parent token */
} kjson_token_t;

/* parser structure */
typedef struct {
	signed int offset,
	signed int next,
	signed int parent
} kjson_parser_t;


void kjson_init(kjson_parser_t* parser);
kjson_err_t kjson_parse(kjson_parser_t* parser, const char* string, kjson_token_t* token, size_t num_tokens);
signed int kjson_get_string_size(kjson_token_t token);
char* kjson_get_string(kjson_token_t token, char* json, char* buf);


#endif /* __KJSON_H_ */ 
