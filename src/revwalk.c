#include <php.h>
#include <git2/revwalk.h>
#include <git2/repository.h>
#include "revwalk.h"
#include "repository.h"
#include "oid.h"
#include "error.h"

zend_class_entry *revwalk_class_entry = NULL;
zend_object_handlers revwalk_object_handlers;

zend_object *php_git2_revwalk_new(zend_class_entry *ce) {
	revwalk_t *repo = zend_object_alloc(sizeof(revwalk_t), ce);
	zend_object_std_init(&repo->std, ce);
	repo->std.handlers = &revwalk_object_handlers;
	return &repo->std;
}

void php_git2_revwalk_free(zend_object *obj) {
	revwalk_t *revwalk = php_git2_revwalk_from_obj(obj);

	if (revwalk->revwalk) {
		git_revwalk_free(revwalk->revwalk);
	}
	zend_object_std_dtor(&revwalk->std);
}

ZEND_METHOD(git_Revwalk, __construct) {
	zval *repo_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
	ZEND_PARSE_PARAMETERS_END();
	repository_t *repo = Z_REPOSITORY_P(repo_dp);



	revwalk_t *walker = Z_REVWALK_P(ZEND_THIS);
	if (git_revwalk_new(&walker->revwalk, repo->repo))
		RETURN_GITERROR();
}

ZEND_METHOD(git_Revwalk, push_range) {
	zend_string *range;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(range);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (git_revwalk_push_range(revwalk->revwalk, ZSTR_VAL(range)))
		RETURN_GITERROR();

	RETURN_NULL();
}

ZEND_METHOD(git_Revwalk, push_head) {
	ZEND_PARSE_PARAMETERS_NONE();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (git_revwalk_push_head(revwalk->revwalk))
		RETURN_GITERROR();
}

// begin iterator hell

typedef struct {
	revwalk_t *revwalk;
	zval current;
	bool more;
	zend_object_iterator iter;
} php_git2_revwalk_iterator;

#define Z_REVWALK_ITER_P(obj) ((php_git2_revwalk_iterator *)((char *)(obj) - XtOffsetOf(php_git2_revwalk_iterator, iter)));

static void php_git2_revwalk_iterator_dtor(zend_object_iterator *iter) {
	php_git2_revwalk_iterator *riter = Z_REVWALK_ITER_P(iter);
	zval_ptr_dtor(&riter->iter.data);
	efree(riter);
}

static int php_git2_revwalk_iterator_valid(zend_object_iterator *iter) {
	php_git2_revwalk_iterator *riter = Z_REVWALK_ITER_P(iter);
	return riter->more ? SUCCESS : FAILURE;
}

static zval *php_git2_revwalk_iterator_current_data(zend_object_iterator *iter) {
	php_git2_revwalk_iterator *riter = Z_REVWALK_ITER_P(iter);
	return &riter->current;
}

static void php_git2_revwalk_iterator_move_forward(zend_object_iterator *iter) {
	php_git2_revwalk_iterator *riter = Z_REVWALK_ITER_P(iter);
	git_oid *oid = php_git2_oid_alloc();
	// here!
	if (git_revwalk_next(oid, riter->revwalk->revwalk))
		riter->more = false;
	else
		riter->more = true;

	ZVAL_RES(&riter->current, zend_register_resource(oid, le_git_oid));
}

const zend_object_iterator_funcs php_git2_revwalk_iterator_funcs = {
	php_git2_revwalk_iterator_dtor,
	php_git2_revwalk_iterator_valid,
	php_git2_revwalk_iterator_current_data,
	NULL, /* current_key */
	php_git2_revwalk_iterator_move_forward,
	NULL, /* rewind */
	NULL, /* ? */
	NULL, /* get_gc */
};

zend_object_iterator *php_git2_revwalk_get_iterator(zend_class_entry *ce, zval *object, int by_ref) {
	php_git2_revwalk_iterator *riter = emalloc(sizeof(php_git2_revwalk_iterator));
	zend_iterator_init(&riter->iter);

	ZVAL_OBJ_COPY(&riter->iter.data, Z_OBJ_P(object));
	riter->iter.funcs = &php_git2_revwalk_iterator_funcs;
	riter->revwalk = Z_REVWALK_P(object);
	php_git2_revwalk_iterator_move_forward(&riter->iter); // do it once
	return &riter->iter;
}
