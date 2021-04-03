#include <php.h>
#include <git2/repository.h>
#include <git2/buffer.h>
#include "repository.h"
#include "error.h"

int le_git_repository;

PHP_FUNCTION(git_repository_init) {
	git_repository *out;
	char *path;
	size_t path_len;
	zend_bool is_bare;
	int error;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS(),
		"s|b", &path, &path_len, &is_bare) == FAILURE) {
		RETURN_THROWS();
	}

	error = git_repository_init(&out, path, is_bare);

	if (php_git2_check_error(error, "git_repository_init")) {
		RETURN_FALSE;
	}

	RETURN_RES(zend_register_resource(out, le_git_repository));
}

PHP_FUNCTION(git_repository_commondir) {
	zval *repo_dp;
	git_repository *repo;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &repo_dp) == FAILURE) {
		RETURN_THROWS();
	}
	if ((repo = (git_repository *)zend_fetch_resource(Z_RES_P(repo_dp), le_git_repository_name, le_git_repository)) == NULL) {
		RETURN_THROWS();
	}

	RETURN_STRING(git_repository_commondir(repo));
}

PHP_FUNCTION(git_repository_open) {
	git_repository *repo;
	zend_string *path;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P", &path) == FAILURE)
		RETURN_THROWS();

	if (git_repository_open(&repo, ZSTR_VAL(path)))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(repo, le_git_repository));
}

PHP_FUNCTION(git_repository_open_bare) {
	git_repository *repo;
	zend_string *path;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P", &path) == FAILURE)
		RETURN_THROWS();

	if (git_repository_open_bare(&repo, ZSTR_VAL(path)))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(repo, le_git_repository));
}

PHP_FUNCTION(git_repository_discover) {
	git_buf buf = {0};
	zend_string *start_path;
	zend_bool cross_fs;
	// zend_array // don't wanna handle ceiling_dirs

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P|b", &start_path, &cross_fs) == FAILURE)
		RETURN_THROWS();

	if (git_repository_discover(&buf, ZSTR_VAL(start_path), cross_fs, NULL))
		RETURN_GITERROR();

	zend_long len = buf.size;
	char root[len];
	memcpy(root, buf.ptr, buf.size);

	git_buf_dispose(&buf);
	RETURN_STRINGL(root, len);
}

void php_git2_repository_free(zend_resource *rsrc) {
	git_repository *repo = (git_repository *) rsrc->ptr;

	if (repo) {
		git_repository_free(repo);
		rsrc->ptr = NULL;
	}
}
