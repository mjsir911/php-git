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
	if (iter->current) {
		git_reference_free(iter->current);
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
		git_reference_iterator_glob_new(&iter->reference_iterator, repo->repo, ZSTR_VAL(glob));
	else
		git_reference_iterator_new(&iter->reference_iterator, repo->repo);

	// git_reference_next(&iter->current, iter->reference_iterator); // do it once
	zend_call_method_with_0_params(Z_OBJ_P(return_value), Z_OBJCE_P(return_value), NULL, "next", NULL);
}

ZEND_METHOD(git_ReferenceIterator, current) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	object_init_ex(return_value, reference_class_entry);
	reference_t *ref = Z_REFERENCE_P(return_value);

	git_reference_dup(&ref->reference, iter->current);
	RETURN_OBJ(&ref->std);
}

ZEND_METHOD(git_ReferenceIterator, key) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	RETURN_STRING(git_reference_name(iter->current));
}

ZEND_METHOD(git_ReferenceIterator, next) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_iterator_t *iter = Z_REFERENCE_ITERATOR_P(ZEND_THIS);

	int err = git_reference_next(&iter->current, iter->reference_iterator);
	if (err == GIT_ITEROVER)
		iter->current = NULL;
	else if (err)
		RETURN_GITERROR();
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
