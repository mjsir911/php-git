--TEST--
Repositories - Open (Simple)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
require "tests/utils.inc";
$clonepath = __DIR__ . '/git-repo';
localRepo($clonepath);
$repo = git_repository_open($clonepath);
var_dump($repo);
?>
--EXPECT--
resource(6) of type (Git Repository)
--CLEAN--
<?php
require "tests/utils.inc";
$clonepath = __DIR__ . '/git-repo';
rmdir_rf($clonepath);
?>
