#include <git2.h>
#include <php.h>
#include <zend.h>
#include <zend_exceptions.h>
#include <zend_interfaces.h>
zend_object *gexception = NULL;
int php_git2_check_error(int error_code, const char *action)
{
	const git_error * error;
	if (!error_code) {
		return error_code;
	}

	error = giterr_last();
	php_error_docref(NULL, E_WARNING, "WARNING %d %s - %s",
		error_code, action, (error && error->message) ? error->message : "???");

	return error_code;
}

void php_git2_print_error() {
	const git_error *error = git_error_last();
	if (error)
		if (error->message)
			return php_error_docref(NULL, E_WARNING, "%s", error->message);
		else
			return php_error_docref(NULL, E_WARNING, "git_error->code: %d",  error->klass);
	else
		return php_error_docref(NULL, E_WARNING, "unknown error");
}

zend_object *php_git2_error2exception(const git_error *err) {
	zval exception, msg, code;
	object_init_ex(&exception , zend_ce_exception);

	ZVAL_LONG(&code, err->klass);
	ZVAL_STRING(&msg, err->message);
	zend_call_method_with_2_params(Z_OBJ(exception), Z_OBJCE(exception), NULL, "__construct",  NULL, &msg, &code);
	return Z_OBJ(exception);
}

int php_git2_check_and_set_error(int code) {
	const git_error *error;
	if ((error = git_error_last()))
		gexception = php_git2_error2exception(error);
	else
		gexception = NULL;
	return code;
}
