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
Warning: Repository::open(): could not find repository from '/dev/null' in %s on line 4
