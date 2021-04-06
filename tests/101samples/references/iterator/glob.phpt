--TEST--
References - Iterator (glob)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

foreach ($repo->references("refs/heads/*") as $ref) {
	echo $ref->name(), " ", git_oid_tostr($ref->target(), 8), PHP_EOL;
}
?>
--EXPECT--
refs/heads/master 64806db6
