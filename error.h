#ifndef PHP_GIT2_ERROR_H
#define PHP_GIT2_ERROR_H
int php_git2_check_error(int error_code, const char *action);
void php_git2_print_error();
#define RETURN_GITERROR() do { php_git2_print_error(); RETURN_THROWS(); } while (0)
#endif // PHP_GIT2_ERROR_H
