--TEST--
Best Practices - Errors
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# Return codes from public APIs indicate general failure category. For extended
# information, libgit2 keeps some data in thread-local storage:
Repository::open("/dev/null")
?>
--EXPECTF--
Fatal error: Uncaught Exception: could not find repository from '/dev/null' in %s/tests/101samples/best_practices/errors.php:4
Stack trace:
#0 %s/tests/101samples/best_practices/errors.php(4): Repository->open('/dev/null')
#1 {main}
  thrown in %s/tests/101samples/best_practices/errors.php on line 4
