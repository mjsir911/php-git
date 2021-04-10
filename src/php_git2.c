#include <php.h>
#include <ext/standard/info.h>
#include <git2.h>
#include <zend_API.h>
#include "php_git2.h"

#define MAIN
#include "types.h"
#undef MAIN

ZEND_DECLARE_MODULE_GLOBALS(git2);



static zend_function_entry php_git2_functions[] = {
	#define XF(func) ZEND_NS_FENTRY("git", func, ZEND_FN(git_##func), arginfo_git_##func, 0)
	#include "types.h"
	#undef XF
	ZEND_FE_END
};

#define X(name, Name) \
	zend_class_entry ce_##name; \
	INIT_CLASS_ENTRY(ce_##name, #Name, class_git_##Name##_methods) \
  name##_class_entry = zend_register_internal_class(&ce_##name); \
	name##_class_entry->create_object = php_git2_##name##_new; \
	memcpy(&name##_object_handlers, &std_object_handlers, sizeof(zend_object_handlers)); \
	name##_object_handlers.free_obj = php_git2_##name##_free; \
	name##_object_handlers.offset = XtOffsetOf(name##_t, std);
PHP_MINIT_FUNCTION(git2) {
	git_libgit2_init();
	#include "types.h"
	#undef X
	#define XI(name, super) zend_class_implements(name##_class_entry, 1, super);
	#include "types.h"
	#undef XI
	// php_register_url_stream_wrapper // I could use this to register git://
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(git2) {
	int error = git_libgit2_shutdown();
	return SUCCESS;
}

PHP_RINIT_FUNCTION(git2) {
	return SUCCESS;
}
PHP_RSHUTDOWN_FUNCTION(git2) {
	return SUCCESS;
}
PHP_MINFO_FUNCTION(git2) {
	char buf[32] = {0};
	int major, minor, rev;

	php_printf("PHP Git2 Extension\n");

	git_libgit2_version(&major, &minor, &rev);
	snprintf(buf, 32, "%d.%d.%d", major, minor, rev);

	php_info_print_table_start();
	php_info_print_table_header(2, "Git2 Support", "enabled");
	php_info_print_table_header(2, "libgit2 version", buf);
	php_info_print_table_end();
}

static PHP_GINIT_FUNCTION(git2) {
}

static PHP_GSHUTDOWN_FUNCTION(git2) {
}


zend_module_entry git2_module_entry = {
	STANDARD_MODULE_HEADER,
	"git2",
	php_git2_functions,					/* Functions */
	PHP_MINIT(git2),	/* MINIT */
	PHP_MSHUTDOWN(git2),	/* MSHUTDOWN */
	PHP_RINIT(git2),	/* RINIT */
	PHP_RSHUTDOWN(git2),		/* RSHUTDOWN */
	PHP_MINFO(git2),	/* MINFO */
	PHP_GIT2_VERSION,
	PHP_MODULE_GLOBALS(git2),
	PHP_GINIT(git2),
	PHP_GSHUTDOWN(git2),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

ZEND_GET_MODULE(git2)

#ifdef COMPILE_DL_GIT2
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(git2)
#endif
