#include <php.h>
#include <zend_interfaces.h>
#include <git2/refs.h>
#include <git2/errors.h>
#include <git2/repository.h>
#include "reference_iterator.h"
#include "repository.h"
#include "reference.h"
#include "error.h"

zend_class_entry *reference_iterator_class_entry = NULL;
zend_object_handlers reference_iterator_object_handlers;

zend_object *php_git2_reference_iterator_new(zend_class_entry *ce) {
	reference_iterator_t *iter = zend_object_alloc(sizeof(reference_iterator_t), ce);
	zend_object_std_init(&iter->std, ce);
	object_properties_init(&iter->std, ce);
	iter->std.handlers = &reference_iterator_object_handlers;
	return &iter->std;
}

void php_git2_reference_iterator_free(zend_object *obj) {
	reference_iterator_t *iter = php_git2_reference_iterator_from_obj(obj);

	if (iter->reference_iterator) {
		git_reference_iterator_free(iter->reference_iterator);
	}
	zend_object_std_dtor(&iter->std);
}


ZEND_METHOD(git_Repository, references) {
	zend_string *glob = NULL;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(glob)
	ZEND_PARSE_PARAMETERS_END();


	object_init_ex(return_value, reference_iterator_class_entry);
	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(return_value);

	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);

	if (glob)
		git_reference_iterator_glob_new(&iter->reference_iterator, repo->obj, ZSTR_VAL(glob));
	else
		git_reference_iterator_new(&iter->reference_iterator, repo->obj);

	// git_reference_next(&iter->current, iter->reference_iterator); // do it once
	zend_call_method_with_0_params(Z_OBJ_P(return_value), Z_OBJCE_P(return_value), NULL, "next", NULL);
}

ZEND_METHOD(git_ReferenceIterator, current) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	if (!iter->current)
		RETURN_NULL();

	RETURN_OBJ(&iter->current->std);
}

ZEND_METHOD(git_ReferenceIterator, key) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	if (!iter->current)
		RETURN_NULL();

	RETURN_STRING(git_reference_name(iter->current->reference));
}

ZEND_METHOD(git_ReferenceIterator, next) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	// if (iter->current) {
	// 	zval __old;
	// 	ZVAL_OBJ(&__old, &iter->current->std);

	// 	if (!Z_ISUNDEF(__old)) {
	// 		zval_ptr_dtor(&__old);
	// 		ZVAL_UNDEF(&__old);
	// 	}
	// }

	zval new;
	object_init_ex(&new, reference_class_entry);
	iter->current = Z_REFERENCE_P(&new);
	switch (GE(git_reference_next(&iter->current->reference, iter->reference_iterator))) {
		case 0:
			break;
		case GIT_ITEROVER:
			iter->current = NULL;
			break;
		default:
			RETURN_THROWS();
	}
}

ZEND_METHOD(git_ReferenceIterator, rewind) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);
	// nothing
}
ZEND_METHOD(git_ReferenceIterator, valid) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	RETURN_BOOL(iter->current != NULL);
}
