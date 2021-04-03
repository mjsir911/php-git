#include "repository.h"
#include "clone.h"
#include <php.h>
#include <git2/clone.h>
#include "error.h"

PHP_FUNCTION(git_clone)
{
	git_repository *repo = NULL;
	zend_bool bare;
	zend_string *url = NULL, *local_path = NULL;
	git_clone_options _options = GIT_CLONE_OPTIONS_INIT;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
		"SS|b", &url, &local_path, &bare) == FAILURE)
		return;

	if (0 > git_clone(&repo, ZSTR_VAL(url), ZSTR_VAL(local_path), &_options))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(repo, le_git_repository));
}

