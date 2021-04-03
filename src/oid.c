#include <php.h>
#include <git2/oid.h>
#include "oid.h"
#include "error.h"

int le_git_oid;

PHP_FUNCTION(git_oid_fromstr) {
	zend_string *sha;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &sha) == FAILURE)
		RETURN_THROWS();

	git_oid *oid = php_git2_oid_alloc();
	if (git_oid_fromstr(oid, ZSTR_VAL(sha)))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(oid, le_git_oid));
}

PHP_FUNCTION(git_oid_tostr) {
	zval *oid_dp;
	zend_long len;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r|l", &oid_dp, &len) == FAILURE)
		RETURN_THROWS();

	git_oid *oid;
	if ((oid = (git_oid *)zend_fetch_resource(Z_RES_P(oid_dp), le_git_oid_name, le_git_oid)) == NULL)
		RETURN_THROWS();

	len++; // for the trailing null
	char buf[len];
	git_oid_tostr(buf, len, oid);
	RETURN_STRING(buf);
}

git_oid* php_git2_oid_alloc(void) {
	return emalloc(sizeof(git_oid));
}

void php_git2_oid_free(zend_resource *rsrc) {
	git_repository *repo = (git_repository *) rsrc->ptr;

	if (repo) {
		efree(rsrc->ptr);
		rsrc->ptr = NULL;
	}
}
