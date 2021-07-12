--TEST--
Commits - Lookups
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$oid = new Oid("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131");

$commit = new Commit($repo, $oid);
print_r($commit)
?>
--EXPECT--
Commit Object
(
    [id] => faa1fb2
    [encoding] => UTF-8
    [message] => Initial commit - add readme

    [summary] => Initial commit - add readme
    [committer] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
        )

    [author] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
        )

)
