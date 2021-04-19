#include <git2/object.h>
#include <zend_types.h>
#include "types.h"
#include "error.h"

#define XO(name, NAME, Name) \
ZEND_METHOD(git_##Name, short_id) { \
	ZEND_PARSE_PARAMETERS_NONE(); \
\
	name##_t *this = Z_##NAME##_P(ZEND_THIS); \
\
	git_buf buf = {0}; \
	if GE(git_object_short_id(&buf, (git_object *)O(this))) \
		RETURN_THROWS(); \
\
	RETVAL_STRINGL(buf.ptr, buf.size); \
	git_buf_dispose(&buf); \
}
#include "types.h"
#undef XO

int php_git2_object_instanceof(zend_class_entry *interface, zend_class_entry *implementor) {
	return SUCCESS;
}
