#ifndef PHP_GIT2_TAG
#define PHP_GIT2_TAG
#include <php.h>
#include <git2/tag.h>
#include <zend_interfaces.h>

#include "tag_arginfo.h"

extern zend_class_entry *tag_class_entry;
extern zend_object_handlers tag_object_handlers;

typedef struct tag_t {
	git_tag *tag;
	zend_object std;
} tag_t;

inline tag_t *php_git2_tag_from_obj(zend_object *obj) {
	return ((tag_t *)((char *)(obj) - XtOffsetOf(tag_t, std)));
}
#define Z_TAG_P(zv) php_git2_tag_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_tag_new(zend_class_entry *ce);
extern void php_git2_tag_free(zend_object *obj);


// #define le_git_tag_name "Git Rev-Walker"
// extern int le_git_tag;

// extern void php_git2_tag_free(zend_resource *rsrc);


#elif defined REGISTER_RESOURCE // PHP_GIT2_TAG
	// REGISTER_RESOURCE(le_git_tag, php_git2_tag_free, le_git_tag_name)
	zend_class_entry ce_tag;
	INIT_CLASS_ENTRY(ce_tag, "Tag", class_git_Tag_methods)
	tag_class_entry = zend_register_internal_class(&ce_tag);
	tag_class_entry->create_object = php_git2_tag_new;

	memcpy(&tag_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	tag_object_handlers.free_obj = php_git2_tag_free;
	tag_object_handlers.offset = XtOffsetOf(tag_t, std);
#elif defined REGISTER_CONVERT
	case GIT_OBJECT_TAG: { 
		zend_object *__ret = php_git2_tag_new(tag_class_entry);
		php_git2_tag_from_obj(__ret)->tag = (git_tag *) obj;
		return __ret;
	}
#endif
