#include <php.h>
#include <git2/blob.h>
#include <zend_interfaces.h>
#include "blob.h"
#include "repository.h"
#include "oid.h"
#include "error.h"

ZEND_METHOD(git_Blob, rawcontent) {
	ZEND_PARSE_PARAMETERS_NONE();
	blob_t *this = Z_BLOB_P(ZEND_THIS);
	RETURN_STRINGL(git_blob_rawcontent(O(this)), git_blob_rawsize(O(this)));
}

ZEND_METHOD(git_Blob, __construct) {
	zval *repo_dp, *oid_dp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);
	oid_t *oid = Z_OID_P(oid_dp);

	blob_t *this = Z_BLOB_P(ZEND_THIS);
	if (GE(git_blob_lookup(&O(this), O(repo), O(oid))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Blob, id) {
	ZEND_PARSE_PARAMETERS_NONE();
	blob_t *this = Z_BLOB_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_blob_id(O(this)), sizeof(*O(oid)));
	RETURN_OBJ(&oid->std);
}

ZEND_METHOD(git_Blob, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	blob_t *this = Z_BLOB_P(ZEND_THIS);

	zval len;
	ZVAL_LONG(&len, 8);
	zval id, size; 
	array_init(return_value);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "id", &id);
	zend_call_method_with_1_params(Z_OBJ(id), Z_OBJCE(id), NULL, "__toString", &id, &len);
	add_assoc_zval(return_value, "id", &id);
	ZVAL_LONG(&size, git_blob_rawsize(O(this)));
	add_assoc_zval(return_value, "size", &size);

	RETURN_ARR(Z_ARR_P(return_value));
}
