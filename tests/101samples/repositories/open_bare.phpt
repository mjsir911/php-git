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
$repo = Repository::open_bare("./tests/repo.git");
var_dump($repo);
?>
--EXPECTF--
object(Repository)#%d (0) {
}
