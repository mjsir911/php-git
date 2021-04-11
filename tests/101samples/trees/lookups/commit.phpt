--TEST--
Trees - Lookups (commit)
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

// Each commit has a tree:
$tree = $commit->tree();
print_r($tree);
?>
--EXPECT--
Tree Object
(
    [id] => 628ce9b2
    [count] => 3
)
