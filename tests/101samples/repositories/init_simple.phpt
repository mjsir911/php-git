--TEST--
Repositories - Init (Simple)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$tempdir = exec("mktemp -d");
# With working directory:
$repo = Repository::init($tempdir, false);
# …or bare:
$repo = Repository::init($tempdir, true);
?>
--EXPECT--
--CLEAN--
<?php
rmdir($tempdir);
?>

