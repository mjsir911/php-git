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
$repo = git_repository_init($tempdir, false);
# …or bare:
$repo = git_repository_init($tempdir, true);
?>
--EXPECT--
--CLEAN--
<?php
rmdir($tempdir);
?>

