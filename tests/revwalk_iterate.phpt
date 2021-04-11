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
$revwalker->push_head();

foreach (new LimitIterator($revwalker, 0, 1) as $oid) {
	echo $oid, PHP_EOL;
}
?>
--EXPECT--
41756be70fdc3c4eeb70cd5df7e183443db8b031
