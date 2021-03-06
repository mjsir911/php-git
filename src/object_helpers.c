#include <git2/object.h>
#include <zend_types.h>
#include "types.h"
#include "error.h"

#define XO(name, NAME, Name) case GIT_OBJECT_##NAME: { \
		zend_object *__ret = php_git2_##name##_new(name##_class_entry); \
		O(php_git2_##name##_from_obj(__ret)) = (git_##name *) obj; \
		return __ret; \
	}
zend_object *php_git2_object_dispatch_new(git_object *obj) {
	#define REGISTER_CONVERT
	switch (git_object_type(obj)) {
		#include "types.h"
	};
	printf("not found type: %s\n", git_object_type2string(git_object_type(obj)));
	return NULL;
	#undef REGISTER_CONVERT
	#undef XO
}

char *php_git2_object_dispatch_typename(git_object_t type) {
	#define XO(name, NAME, Name) case GIT_OBJECT_##NAME: return #Name;
	switch (type) {
		#include "types.h"
	}
	printf("not found type: %s\n", git_object_type2string(type));
	#undef XO
	return "";
}

