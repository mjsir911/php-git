--TEST--
Repositories - Clone (Simple)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
include "tests/utils.inc";
$path = __DIR__ . "/php-git-test.git";
$repo = git_clone(TEST_REPO, $path);
echo is_dir($path);
?>
--CLEAN--
<?php
$path = __DIR__ . "/php-git-test.git";
include "tests/utils.inc";
rmdir_rf($path);
?>
--EXPECT--
1
