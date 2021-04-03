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
$repo = git_repository_open("./tests/git-repo");
var_dump($repo);
?>
--EXPECT--
resource(4) of type (Git Repository)
