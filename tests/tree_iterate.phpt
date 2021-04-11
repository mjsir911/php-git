--TEST--
Tree - Iterator
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

foreach ($repo->revparse_single("HEAD^{tree}") as $entry) {
	print_r($entry);
}
?>
--EXPECT--
TreeEntry Object
(
    [id] => ff9e935f
    [filemode] => 33188
    [name] => LICENSE
    [type] => Blob
)
TreeEntry Object
(
    [id] => 2a19b740
    [filemode] => 33188
    [name] => README.md
    [type] => Blob
)
TreeEntry Object
(
    [id] => 3c25b180
    [filemode] => 16384
    [name] => a
    [type] => Tree
)
TreeEntry Object
(
    [id] => 3dabcd1d
    [filemode] => 16384
    [name] => src
    [type] => Tree
)
