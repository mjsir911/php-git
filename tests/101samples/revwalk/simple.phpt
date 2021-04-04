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

$revwalker = new Revwalk($repo);
$revwalker->push_range("faa1fb22..64806db6");

foreach ($revwalker as $oid) {
	echo git_oid_tostr($oid, 8), PHP_EOL;
}
?>
--EXPECT--
64806db6
0a64a3ad
