#include <stddef.h>
#include "kjson.h"

/* initialize kjson parser */
void kjson_init(kjson_parser_t* parser) {
	parser->pos = 0;
	parser->next = 0;
	parser->parent = -1;
}

/** 
 * allocate & initialize next available token 
 *   return new kjson_token_t or NULL on error
*/
static kjson_token_t kjson_new_token(
		kjson_parser_t* parser, 
		kjson_token_t* token, 
		unsigned int max_token) {
	
	kjson_token_t* tok;

	unsigned int next = parser->next + 1;
	if(next >= num_token) {
		/* no token available */
		return NULL;
	} else {
		tok = &token[next];
		tok->start = -1;
		tok->end = -1;
		tok->size = 0;
		top->parent = -1;
		return tok;
	}
}

static void kjson_set_token(kjson_token_t* token,
		kjson_type_t type, 
		signed int start, signed int end) {

	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
}

/* return the string size of a token + 1 (for the null terminator) */
signed int kjson_get_string_size(kjson_token_t token) {
	return (token->end - token->begin) + 1;
}

/* copy a token string into from json to buf + /0 */ 
char* kjson_get_string(kjson_token_t token, char* json, char* buf) {
	for(signed int i = 0; i < (token->end - token->start); i++) {
		buf[i] = json[token->start + i];
	}
	buf[token->end] = '\0';
	return buf;
}



kjson_err_t kjson_parse(kjson_parser_t* parser, 
		const char* string, 
		kjson_token_t* token, 
		size_t num_tokens) {

	kjson_err_t error;
	
}

