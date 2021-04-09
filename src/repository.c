#include <php.h>
#include <git2/repository.h>
#include <git2/buffer.h>
#include <zend_interfaces.h>
#include "repository.h"
#include "error.h"

ZEND_METHOD(git_Repository, __construct) {

	zend_string *bare_path;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(bare_path)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);

	if (GE(git_repository_open_bare(&repo->obj, ZSTR_VAL(bare_path))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Repository, init) {
	object_init_ex(ZEND_THIS, repository_class_entry);
	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);

	zend_string *path;
	zend_bool is_bare;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS(),
		"P|b", &path, &is_bare) == FAILURE) {
		RETURN_THROWS();
	}

	if (GE(git_repository_init(&repo->obj, ZSTR_VAL(path), is_bare)))
		RETURN_THROWS();

	RETURN_OBJ(&repo->std);
}

ZEND_METHOD(git_Repository, open) {
	object_init_ex(ZEND_THIS, repository_class_entry);
	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);

	zend_string *path;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P", &path) == FAILURE)
		RETURN_THROWS();

	if (GE(git_repository_open(&repo->obj, ZSTR_VAL(path))))
		RETURN_THROWS();

	RETURN_OBJ(&repo->std);
}


ZEND_METHOD(git_Repository, open_bare) {
	object_init_ex(return_value, repository_class_entry);
	repository_t *repo = Z_REPOSITORY_P(return_value);

	zend_string *bare_path;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(bare_path)
	ZEND_PARSE_PARAMETERS_END();


	zval bare_path_dp;
	ZVAL_STR(&bare_path_dp, bare_path);

	zend_call_method_with_1_params(Z_OBJ_P(return_value), Z_OBJCE_P(return_value), NULL, "__construct", NULL, &bare_path_dp);

	RETURN_OBJ(&repo->std);
}

ZEND_METHOD(git_Repository, discover) {
	git_buf buf = {0};
	zend_string *start_path;
	zend_bool cross_fs;
	// zend_array // don't wanna handle ceiling_dirs

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P|b", &start_path, &cross_fs) == FAILURE)
		RETURN_THROWS();

	if (GE(git_repository_discover(&buf, ZSTR_VAL(start_path), cross_fs, NULL)))
		RETURN_THROWS();

	zend_long len = buf.size;
	char root[len];
	memcpy(root, buf.ptr, buf.size);

	git_buf_dispose(&buf);
	RETURN_STRINGL(root, len);
}

ZEND_METHOD(git_Repository, commondir) {
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "") == FAILURE) {
		RETURN_THROWS();
	}

	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);
	if (!repo->obj)
		RETURN_THROWS();

	RETURN_STRING(git_repository_commondir(repo->obj));
}
