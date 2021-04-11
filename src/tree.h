#ifdef X
X(tree, Tree)
X(tree_entry, TreeEntry)
#elif defined XO
XO(tree, TREE)
#elif defined XI
XI(tree, zend_ce_countable);
XI(tree, zend_ce_iterator);
XI(tree, zend_ce_arrayaccess);
#else
#ifndef PHP_GIT2_TREE
#define PHP_GIT2_TREE
#include <php.h>
#include <git2/tree.h>

#include "tree_arginfo.h"

#define T tree
#define E zval current;
#include "gitobj.h"

#define Z_TREE_P(zv) php_git2_tree_from_obj(Z_OBJ_P((zv)))

#define T tree_entry
#include "gitobj.h"

#define Z_TREE_ENTRY_P(zv) php_git2_tree_entry_from_obj(Z_OBJ_P((zv)))

#endif
#endif
