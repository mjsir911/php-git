--TEST--
Trees - Lookups (OID)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

// You can look them up by OID:
$tree = new Tree($repo, new Oid("d06993fdd350123c28230d762cc6682d97393db7"));
print_r($tree);
?>
--EXPECT--
Tree Object
(
    [id] => d06993fd
    [count] => 1
)
