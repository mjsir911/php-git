#include <php.h>
#include <git2/signature.h>
#include <zend_interfaces.h>
#include <ext/date/php_date.h>
#include "signature.h"
#include "oid.h"
#include "repository.h"
#include "error.h"

ZEND_METHOD(git_Signature, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(O(signature)->name);
}

ZEND_METHOD(git_Signature, email) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(O(signature)->email);
}

ZEND_METHOD(git_Signature, when) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	// this is probably the worst datetime API I've ever seen.
	// I'm not going to do string formatting fuckery to get a working datetime
	// object

	git_time t = O(signature)->when;

	// first, let's get a datetime object to manipulate.
	zval dt;
	{
		zend_fcall_info fci;
		fci.retval = &dt;
		fci.param_count = 0;
		zval args[0];
		fci.params = args;
		fci.size = sizeof(fci);
		fci.object = NULL;
		fci.named_params = NULL;
		ZVAL_STRING(&fci.function_name, "date_create");
		zend_call_function(&fci, NULL);
	}

	// set the timezone with fuckery
	zval tz;
	{
		zend_fcall_info fci;
		fci.retval = &tz;
		zval args[1];
		ZVAL_STRING(&args[0], "+2500");
		fci.params = args;
		fci.param_count = 1;
		fci.size = sizeof(fci);
		fci.object = NULL;
		fci.named_params = NULL;
		ZVAL_STRING(&fci.function_name, "timezone_open");
		zend_call_function(&fci, NULL);
	}
	// fuckery
	Z_PHPTIMEZONE_P(&tz)->tzi.utc_offset = t.offset * 60;

	// set the timestamp 
	Z_PHPDATE_P(&dt)->time->sse = t.time;
	Z_PHPDATE_P(&dt)->time->us = 0; // git doesn't have this much precision

	// attach the new tz (this also updates time based on sse)
	zend_call_method_with_1_params(Z_OBJ(dt), Z_OBJCE(dt), NULL, "setTimezone", NULL, &tz);

	// RETURN_STRING(O(signature)->name);
	RETURN_OBJ_COPY(Z_OBJ_P(&dt));
}

ZEND_METHOD(git_Signature, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval name, email, when;
	array_init(return_value);

	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "name", &name);
	add_assoc_zval(return_value, "name", &name);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "email", &email);
	add_assoc_zval(return_value, "email", &email);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "when", &when);
	add_assoc_zval(return_value, "when", &when);
}
