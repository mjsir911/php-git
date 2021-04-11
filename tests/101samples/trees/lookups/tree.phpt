--TEST--
Trees - Lookups (subtree)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$commit = new Commit($repo, new Oid("64806db6955b90da39203a9bdb7285efffdd1402"));

// Trees can contain trees:
$tree = $commit->tree();
$entry = $tree->byindex(2);
print_r($entry);
print_r($entry->to_object($repo));
?>
--EXPECT--
TreeEntry Object
(
    [id] => 3dabcd1d
    [filemode] => 16384
    [name] => src
    [type] => Tree
)
Tree Object
(
    [id] => 3dabcd1d
    [count] => 1
)
