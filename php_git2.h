#include <php.h>
#ifndef PHP_GIT2_H
#define PHP_GIT2_H


extern zend_module_entry git2_module_entry;
# define phpext_git2_ptr &git2_module_entry

# define PHP_GIT2_VERSION "0.4.0"

#ifdef ZTS
#include <TSRM.h>
#endif

ZEND_BEGIN_MODULE_GLOBALS(git2)
	zend_long scale;
ZEND_END_MODULE_GLOBALS(git2)

ZEND_EXTERN_MODULE_GLOBALS(git2)

#define GIT2_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(git2, v)

#endif	/* PHP_GIT2_H */
