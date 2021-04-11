--TEST--
Blobs - Lookups
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

print_r(new Blob($repo, new Oid("64ebe54dbfda50c3d7df56631a32d5cc4c17f584")))
?>
--EXPECT--
Blob Object
(
    [id] => 64ebe54d
    [size] => 43
)
