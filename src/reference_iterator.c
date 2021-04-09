#include <php.h>
#include <zend_interfaces.h>
#include <git2/refs.h>
#include <git2/errors.h>
#include <git2/repository.h>
#include "reference_iterator.h"
#include "repository.h"
#include "reference.h"
#include "error.h"

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
		git_reference_iterator_glob_new(&iter->obj, repo->obj, ZSTR_VAL(glob));
	else
		git_reference_iterator_new(&iter->obj, repo->obj);

	// git_reference_next(&iter->current, iter->obj); // do it once
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

	RETURN_STRING(git_reference_name(iter->current->obj));
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
	switch (GE(git_reference_next(&iter->current->obj, iter->obj))) {
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
