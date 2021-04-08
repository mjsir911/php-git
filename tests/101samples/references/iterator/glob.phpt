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
	echo $ref->name(), " ", $ref->target()->__toString(8), PHP_EOL;
}
?>
--EXPECT--
refs/heads/master 64806db6
refs/heads/msirabella/fix/importable 2596aeb1
refs/heads/msirabella/foobar 25d231de
