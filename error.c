#include <git2.h>
#include <php.h>
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
	const git_error *error = giterr_last();
	return php_error_docref(NULL, E_WARNING, "%s", (error && error->message) ? error->message : "???");
}
