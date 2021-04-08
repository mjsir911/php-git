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
64806db6955b90da39203a9bdb7285efffdd1402
