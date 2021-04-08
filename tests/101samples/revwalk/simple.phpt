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
$walker = new Revwalk($repo);

$walker->push_range("faa1fb22..64806db6");

foreach ($walker as $oid) {
	echo $oid->__toString(8), PHP_EOL;
}
?>
--EXPECT--
64806db6
0a64a3ad
