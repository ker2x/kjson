#ifndef __KJSON_H_
#define __KJSON_H_

/**
 * KJSON assume that a valid json follow theses specification : 
 * ------------------------------------------------------------
 *
 * object :
 * -------- 
 * an oject begin with { and end with }
 * zero or more set of "string : value" separated by a comma
 * eg : {} (empty object) or { string : value } or { string : value, string : value, ... }
 * 
 * value :
 * ------- 
 * can be a string, number, object, array, true, false, null
 *
 * array :
 * -------
 * an array begin with [ and end with ]
 * zero or more value separated by a comma
 * eg : [] (empty array), [ value ] , [ value, value, ... ]
 * note : a object is a valid value, an array is also a valid value
 *        so we can have array of array or array of object
 * 
 * string :
 * --------
 * a string is a sequence of zero or more unicode char wrapped in "double quote"
 * except : double quote
 *          or \ 
 *          or control character (code <= 32)
 * valid escaped character :
 * \" \\ \/ \b \n \f \r \t 
 * \u + 4 hax digit (unicode)
 *
 * number : 
 * --------
 * A number is very much like a C or Java number, 
 * except that the octal and hexadecimal formats are not used.
 * it include exponent notation : 3e4, 2.1e-5, 1.2E5, 4E8, ...   
 *
 */


/* *MUST* be strictly inferior than UINT_MAX */
#define BUF_SIZE 65535
#define MAX_TOKEN 256




/* declare json value type */
typedef enum {
	KJSON__NULL_T,		/* the null type */
	KJSON__TRUE_T,		/* the true type */
	KJSON__FALSE_T,		/* the false type */
	KJSON_NUMERIC_T,	/* integer, float, ... */
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
static kjson_err_t kjson_parse_primitive(kjson_parser* parser, const char* json, kjson_token_t* token, unsigned int num_token);

#endif /* __KJSON_H_ */ 
