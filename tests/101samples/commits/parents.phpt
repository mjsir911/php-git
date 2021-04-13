--TEST--
Commits - Parents
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$oid = new Oid("41756be70fdc3c4eeb70cd5df7e183443db8b031");
$commit = new Commit($repo, $oid);

print_r($commit->parents());
?>
--EXPECT--
Array
(
    [0] => Commit Object
        (
        )

)
