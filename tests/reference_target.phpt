--TEST--
Revwalk - Simple
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

$ref = Reference::dwim($repo, "HEAD");

$oid = $ref->target();
echo git_oid_tostr($oid, 8), PHP_EOL;
?>
--EXPECT--
64806db6
