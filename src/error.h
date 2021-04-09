#ifndef PHP_GIT2_ERROR_H
#define PHP_GIT2_ERROR_H
#include <zend_API.h>
extern zend_object *gexception;
int php_git2_check_error(int error_code, const char *action);
void php_git2_print_error();
int php_git2_check_and_set_error(int code);
#define RETURN_GITERROR() do { php_git2_print_error(); RETURN_THROWS(); } while (0)
#undef RETURN_THROWS
#define RETURN_THROWS() do { if (!EG(exception)) EG(exception) = gexception; gexception = NULL; ZEND_ASSERT(EG(exception)); (void) return_value; return; } while(0)
#define GE(x) (php_git2_check_and_set_error(x))
#endif // PHP_GIT2_ERROR_H
