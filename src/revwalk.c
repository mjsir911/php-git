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

ZEND_METHOD(git_Revwalk, push_ref) {
	zend_string *ref;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(ref);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (git_revwalk_push_ref(revwalk->revwalk, ZSTR_VAL(ref)))
		RETURN_GITERROR();
}

ZEND_METHOD(git_Revwalk, push_glob) {
	zend_string *glob;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(glob);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (git_revwalk_push_glob(revwalk->revwalk, ZSTR_VAL(glob)))
		RETURN_GITERROR();
}

ZEND_METHOD(git_Revwalk, hide) {
	zval *oid_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *oid = Z_OID_P(oid_dp);
	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (git_revwalk_hide(revwalk->revwalk, &oid->oid))
		RETURN_GITERROR();
}

ZEND_METHOD(git_Revwalk, hide_glob) {
	zend_string *glob;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(glob);
	ZEND_PARSE_PARAMETERS_END();

	revwalk_t *revwalk = Z_REVWALK_P(ZEND_THIS);

	if (git_revwalk_hide_glob(revwalk->revwalk, ZSTR_VAL(glob)))
		RETURN_GITERROR();
}


// begin iterator hell

#include "commit.h"
ZEND_METHOD(git_Revwalk, current) {
	ZEND_PARSE_PARAMETERS_NONE();

	revwalk_t *this = Z_REVWALK_P(ZEND_THIS);
	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(&oid->oid, &this->oid, sizeof(oid->oid));
}
ZEND_METHOD(git_Revwalk, key) {
	ZEND_PARSE_PARAMETERS_NONE();
}
#include <git2/errors.h>
ZEND_METHOD(git_Revwalk, next) {
	ZEND_PARSE_PARAMETERS_NONE();
	revwalk_t *this = Z_REVWALK_P(ZEND_THIS);
	switch (git_revwalk_next(&this->oid, this->revwalk)) {
		case 0:
			this->more = true;
			break;
		case GIT_ITEROVER:
		default:
			this->more = false;
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

	RETURN_BOOL(this->more);
}
