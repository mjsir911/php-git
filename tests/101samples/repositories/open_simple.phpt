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
$repo = Repository::open($clonepath);
var_dump($repo);
?>
--EXPECTF--
object(Repository)#%d (0) {
}
--CLEAN--
<?php
require "tests/utils.inc";
$clonepath = __DIR__ . '/git-repo';
rmdir_rf($clonepath);
?>
