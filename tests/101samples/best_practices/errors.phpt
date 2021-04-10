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
try {
	Repository::open("/dev/null");
	echo "No error raised!";
} catch (exception $e) {
	echo $e->getCode(), PHP_EOL;
	echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
6
could not find repository from '/dev/null'
