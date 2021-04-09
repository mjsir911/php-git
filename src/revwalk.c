#include <php.h>
#include <zend_interfaces.h>
#include <git2/revwalk.h>
#include <git2/repository.h>
#include "revwalk.h"
#include "repository.h"
#include "oid.h"
#include "error.h"

zend_class_entry *revwalk_class_entry = NULL;
zend_object_handlers revwalk_object_handlers;

zend_object *php_git2_revwalk_new(zend_class_entry *ce) {
	revwalk_t *revwalk = zend_object_alloc(sizeof(revwalk_t), ce);
	zend_object_std_init(&revwalk->std, ce);
	object_properties_init(&revwalk->std, ce);
	revwalk->std.handlers = &revwalk_object_handlers;
	return &revwalk->std;
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
	if (GE(git_revwalk_new(&walker->revwalk, repo->obj)))
		RETURN_THROWS();


}

ZEND_METHOD(git_Revwalk, push_range) {
	zend_string *range;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(range);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_range(revwalk->revwalk, ZSTR_VAL(range))))
		RETURN_THROWS();

	RETURN_NULL();
}

ZEND_METHOD(git_Revwalk, push_head) {
	ZEND_PARSE_PARAMETERS_NONE();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_head(revwalk->revwalk)))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, push_ref) {
	zend_string *ref;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(ref);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_ref(revwalk->revwalk, ZSTR_VAL(ref))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, push_glob) {
	zend_string *glob;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(glob);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_glob(revwalk->revwalk, ZSTR_VAL(glob))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, hide) {
	zval *oid_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *oid = Z_OID_P(oid_dp);
	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_hide(revwalk->revwalk, oid->oid)))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, hide_glob) {
	zend_string *glob;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(glob);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_hide_glob(revwalk->revwalk, ZSTR_VAL(glob))))
		RETURN_THROWS();
}


// begin iterator hell

#include "commit.h"
ZEND_METHOD(git_Revwalk, current) {
	ZEND_PARSE_PARAMETERS_NONE();

	revwalk_t *this = Z_REVWALK_P(ZEND_THIS);

	if (!this->oid)
		RETURN_NULL();

	RETURN_OBJ(&this->oid->std);
}

ZEND_METHOD(git_Revwalk, key) {
	ZEND_PARSE_PARAMETERS_NONE();
}
#include <git2/errors.h>
ZEND_METHOD(git_Revwalk, next) {
	ZEND_PARSE_PARAMETERS_NONE();
	revwalk_t *this = Z_REVWALK_P(ZEND_THIS);

	// if (this->oid) {
	// 	zval __old;
	// 	ZVAL_OBJ(&__old, &this->oid->std);

	// 	if (!Z_ISUNDEF(__old)) {
	// 		zval_ptr_dtor(&__old);
	// 		ZVAL_UNDEF(&__old);
	// 	}
	// }

	zval new_oid;
	object_init_ex(&new_oid, oid_class_entry);
	this->oid = Z_OID_P(&new_oid);
	switch (git_revwalk_next(this->oid->oid, this->revwalk)) {
		case 0:
			break;
		case GIT_ITEROVER:
		default:
			this->oid = NULL;
	}
}

ZEND_METHOD(git_Revwalk, rewind) {
	ZEND_PARSE_PARAMETERS_NONE();
	// do it once
	zim_git_Revwalk_next(execute_data, return_value);
}
ZEND_METHOD(git_Revwalk, valid) {
	ZEND_PARSE_PARAMETERS_NONE();

	revwalk_t *this = Z_REVWALK_P(ZEND_THIS);

	RETURN_BOOL(this->oid);
}
