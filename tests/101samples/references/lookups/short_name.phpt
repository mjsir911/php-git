--TEST--
References - Lookups (short name)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# Get the object pointed to by a symbolic reference (or a chain of them).
$repo = Repository::open_bare("./tests/repo.git");

$ref = Reference::dwim($repo, "master");

var_dump($ref);
?>
--EXPECTF--
object(Reference)#%d (0) {
}
