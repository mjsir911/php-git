#include <php.h>
#include <zend_interfaces.h>
#include <git2/revwalk.h>
#include <git2/repository.h>
#include "revwalk.h"
#include "repository.h"
#include "oid.h"
#include "error.h"

ZEND_METHOD(git_Revwalk, __construct) {
	zval *repo_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
	ZEND_PARSE_PARAMETERS_END();
	repository_t *repo = Z_REPOSITORY_P(repo_dp);



	revwalk_t *walker = Z_REVWALK_P(ZEND_THIS);
	if (GE(git_revwalk_new(&O(walker), O(repo))))
		RETURN_THROWS();


}

ZEND_METHOD(git_Revwalk, push_range) {
	zend_string *range;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(range);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_range(O(revwalk), ZSTR_VAL(range))))
		RETURN_THROWS();

	RETURN_NULL();
}

ZEND_METHOD(git_Revwalk, push_head) {
	ZEND_PARSE_PARAMETERS_NONE();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_head(O(revwalk))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, push_ref) {
	zend_string *ref;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(ref);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_ref(O(revwalk), ZSTR_VAL(ref))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, push_glob) {
	zend_string *glob;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(glob);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_push_glob(O(revwalk), ZSTR_VAL(glob))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, hide) {
	zval *oid_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *oid = Z_OID_P(oid_dp);
	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_hide(O(revwalk), O(oid))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Revwalk, hide_glob) {
	zend_string *glob;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(glob);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (GE(git_revwalk_hide_glob(O(revwalk), ZSTR_VAL(glob))))
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
	switch (git_revwalk_next(O(this->oid), O(this))) {
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
