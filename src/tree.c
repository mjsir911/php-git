#include <php.h>
#include <git2/tree.h>
#include <zend_interfaces.h>
#include "tree.h"
#include "repository.h"
#include "oid.h"
#include "commit.h"
#include "object.h"
#include "error.h"

ZEND_METHOD(git_TreeEntry, filemode) {
	ZEND_PARSE_PARAMETERS_NONE();
	tree_entry_t *this = Z_TREE_ENTRY_P(ZEND_THIS);
	RETURN_LONG(git_tree_entry_filemode(O(this)));
}
ZEND_METHOD(git_TreeEntry, id) {
	ZEND_PARSE_PARAMETERS_NONE();
	tree_entry_t *this = Z_TREE_ENTRY_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_tree_entry_id(O(this)), sizeof(*O(oid)));
	RETURN_OBJ(&oid->std);
}
ZEND_METHOD(git_TreeEntry, name) {
	ZEND_PARSE_PARAMETERS_NONE();
	tree_entry_t *this = Z_TREE_ENTRY_P(ZEND_THIS);
	RETURN_STRING(git_tree_entry_name(O(this)));
}
ZEND_METHOD(git_TreeEntry, type) {
	ZEND_PARSE_PARAMETERS_NONE();
	tree_entry_t *this = Z_TREE_ENTRY_P(ZEND_THIS);
	RETURN_STRING(php_git2_object_dispatch_typename(git_tree_entry_type(O(this))));
}
ZEND_METHOD(git_TreeEntry, to_object) {
	zval *repo_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
	ZEND_PARSE_PARAMETERS_END();
	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	tree_entry_t *this = Z_TREE_ENTRY_P(ZEND_THIS);
	git_object *obj;
	git_tree_entry_to_object(&obj, O(repo), O(this));
	RETURN_OBJ(php_git2_object_dispatch_new(obj));
}
ZEND_METHOD(git_TreeEntry, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval len;
	ZVAL_LONG(&len, 8);
	zval filemode, id, name; 
	array_init(return_value);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "id", &id);
	zend_call_method_with_1_params(Z_OBJ(id), Z_OBJCE(id), NULL, "__toString", &id, &len);
	add_assoc_zval(return_value, "id", &id);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "filemode", &filemode);
	add_assoc_zval(return_value, "filemode", &filemode);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "name", &name);
	add_assoc_zval(return_value, "name", &name);

	RETURN_ARR(Z_ARR_P(return_value));
}

ZEND_METHOD(git_Tree, __construct) {
	zval *repo_dp, *oid_dp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);
	oid_t *oid = Z_OID_P(oid_dp);

	tree_t *this = Z_TREE_P(ZEND_THIS);
	if (GE(git_tree_lookup(&O(this), O(repo), O(oid))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Commit, tree) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, tree_class_entry);
	tree_t *tree = Z_TREE_P(return_value);
	if (GE(git_commit_tree(&O(tree), O(commit))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Tree, id) {
	ZEND_PARSE_PARAMETERS_NONE();

	tree_t *this = Z_TREE_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_tree_id(O(this)), sizeof(*O(oid)));
	RETURN_OBJ(&oid->std);
}

ZEND_METHOD(git_Tree, byindex) {
	zend_long idx;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(idx)
	ZEND_PARSE_PARAMETERS_END();

	tree_t *this = Z_TREE_P(ZEND_THIS);

	object_init_ex(return_value, tree_entry_class_entry);
	tree_entry_t *tree_entry = Z_TREE_ENTRY_P(return_value);

	const git_tree_entry *tmp_tree_entry;
	if (!(tmp_tree_entry = git_tree_entry_byindex(O(this), idx)))
		RETURN_NULL();
	if (GE(git_tree_entry_dup(&O(tree_entry), tmp_tree_entry)))
		RETURN_THROWS();
	RETURN_OBJ(&tree_entry->std);
}

ZEND_METHOD(git_Tree, byname) {
	zend_string *filename;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(filename)
	ZEND_PARSE_PARAMETERS_END();

	tree_t *this = Z_TREE_P(ZEND_THIS);

	object_init_ex(return_value, tree_entry_class_entry);
	tree_entry_t *tree_entry = Z_TREE_ENTRY_P(return_value);

	const git_tree_entry *tmp_tree_entry;
	if (!(tmp_tree_entry = git_tree_entry_byname(O(this), ZSTR_VAL(filename))))
		RETURN_NULL();
	if (GE(git_tree_entry_dup(&O(tree_entry), tmp_tree_entry)))
		RETURN_THROWS();
	RETURN_OBJ(&tree_entry->std);
}

ZEND_METHOD(git_Tree, bypath) {
	zend_string *path;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH_STR(path)
	ZEND_PARSE_PARAMETERS_END();

	tree_t *this = Z_TREE_P(ZEND_THIS);

	object_init_ex(return_value, tree_entry_class_entry);
	tree_entry_t *tree_entry = Z_TREE_ENTRY_P(return_value);

	if (git_tree_entry_bypath(&O(tree_entry), O(this), ZSTR_VAL(path)))
		RETURN_NULL();
	RETURN_OBJ(&tree_entry->std);
}

ZEND_METHOD(git_Tree, count) {
	ZEND_PARSE_PARAMETERS_NONE();
	tree_t *this = Z_TREE_P(ZEND_THIS);
	RETURN_LONG(git_tree_entrycount(O(this)));
}

ZEND_METHOD(git_Tree, offsetExists) {
	zval *filename;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(filename)
	ZEND_PARSE_PARAMETERS_END();

	zval tmp;
	zend_call_method_with_1_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "offsetGet", &tmp, filename);
	RETURN_BOOL(ZVAL_IS_NULL(&tmp));
}

ZEND_METHOD(git_Tree, offsetSet) {
	zval *filename, *thing;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(filename)
		Z_PARAM_ZVAL(thing)
	ZEND_PARSE_PARAMETERS_END();

	zend_throw_error(NULL, "Cannot modify Tree");
	RETURN_THROWS();
}
ZEND_METHOD(git_Tree, offsetUnset) {
	zval *filename;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(filename)
	ZEND_PARSE_PARAMETERS_END();

	zend_throw_error(NULL, "Cannot modify Tree");
	RETURN_THROWS();
}

ZEND_METHOD(git_Tree, current) {
	ZEND_PARSE_PARAMETERS_NONE();

	tree_t *this = Z_TREE_P(ZEND_THIS);
	zval current;
	ZVAL_LONG(&current, this->current);
	zend_call_method_with_1_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "byindex", return_value, &current);
}

ZEND_METHOD(git_Tree, key) {
	ZEND_PARSE_PARAMETERS_NONE();

	tree_t *this = Z_TREE_P(ZEND_THIS);
	zval current;
	ZVAL_LONG(&current, this->current);

	zval tree_entry;
	zend_call_method_with_1_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "byindex", &tree_entry, &current);
	zend_call_method_with_0_params(Z_OBJ(tree_entry), Z_OBJCE(tree_entry), NULL, "name", return_value);
	RETURN_OBJ(Z_OBJ_P(return_value));
}
ZEND_METHOD(git_Tree, next) {
	ZEND_PARSE_PARAMETERS_NONE();

	tree_t *this = Z_TREE_P(ZEND_THIS);
	this->current++;
	RETURN_NULL();
}
ZEND_METHOD(git_Tree, rewind) {
	ZEND_PARSE_PARAMETERS_NONE();

	tree_t *this = Z_TREE_P(ZEND_THIS);
	this->current = 0;
	RETURN_NULL();
}
ZEND_METHOD(git_Tree, valid) {
	ZEND_PARSE_PARAMETERS_NONE();

	tree_t *this = Z_TREE_P(ZEND_THIS);
	zval count;
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "count", &count);
	RETURN_BOOL(this->current < Z_LVAL(count));
}

ZEND_METHOD(git_Tree, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval len;
	ZVAL_LONG(&len, 8);
	zval count, id;
	array_init(return_value);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "id", &id);
	zend_call_method_with_1_params(Z_OBJ(id), Z_OBJCE(id), NULL, "__toString", &id, &len);
	add_assoc_zval(return_value, "id", &id);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "count", &count);
	add_assoc_zval(return_value, "count", &count);

	RETURN_ARR(Z_ARR_P(return_value));
}
