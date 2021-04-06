#include <php.h>
#include <git2/repository.h>
#include <git2/buffer.h>
#include "repository.h"
#include "error.h"

zend_class_entry *repository_class_entry = NULL;
zend_object_handlers repository_object_handlers;

zend_object *php_git2_repository_new(zend_class_entry *ce) {
	repository_t *repo = zend_object_alloc(sizeof(repository_t), ce);
	zend_object_std_init(&repo->std, ce);
	repo->std.handlers = &repository_object_handlers;
	return &repo->std;
}

void php_git2_repository_free(zend_object *obj) {
	repository_t *repo = php_git2_repository_from_obj(obj);

	if (repo->repo) {
		git_repository_free(repo->repo);
	}
	zend_object_std_dtor(&repo->std);
}

ZEND_METHOD(git_Repository, init) {
	repository_t *repo = php_git2_repository_from_obj(php_git2_repository_new(repository_class_entry));

	zend_string *path;
	zend_bool is_bare;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS(),
		"P|b", &path, &is_bare) == FAILURE) {
		RETURN_THROWS();
	}

	if (git_repository_init(&repo->repo, ZSTR_VAL(path), is_bare))
		RETURN_GITERROR();

	RETURN_OBJ(&repo->std);
}

ZEND_METHOD(git_Repository, open) {
	repository_t *repo = php_git2_repository_from_obj(php_git2_repository_new(repository_class_entry));
	zend_string *path;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P", &path) == FAILURE)
		RETURN_THROWS();

	if (git_repository_open(&repo->repo, ZSTR_VAL(path)))
		RETURN_GITERROR();

	RETURN_OBJ(&repo->std);
}

ZEND_METHOD(git_Repository, open_bare) {
	repository_t *repo = php_git2_repository_from_obj(php_git2_repository_new(repository_class_entry));
	zend_string *path;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P", &path) == FAILURE)
		RETURN_THROWS();

	if (git_repository_open_bare(&repo->repo, ZSTR_VAL(path)))
		RETURN_GITERROR();

	RETURN_OBJ(&repo->std);
}

ZEND_METHOD(git_Repository, discover) {
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

ZEND_METHOD(git_Repository, commondir) {
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "") == FAILURE) {
		RETURN_THROWS();
	}

	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);
	if (!repo->repo)
		RETURN_THROWS();

	RETURN_STRING(git_repository_commondir(repo->repo));
}

#include "reference_iterator.h"

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
