--TEST--
Repositories - Open (Bare)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# A fast way of opening a bare repository when the exact path is known.
$repo = git_repository_open_bare("./tests/repo.git");
var_dump($repo);
?>
--EXPECT--
resource(4) of type (Git Repository)
