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

foreach ($repo->references() as $ref) {
	echo $ref->name(), " ", $ref->target()->__toString(8), PHP_EOL;
}

echo '======', PHP_EOL;

foreach ($repo->references("refs/heads/msirabel*") as $ref) {
	echo $ref->name(), " ", $ref->target()->__toString(8), PHP_EOL;
}

echo '======', PHP_EOL;

foreach ($repo->references("refs/tags/*") as $ref) {
	echo $ref->name(), " ", $ref->target()->__toString(8), PHP_EOL;
}
?>
--EXPECT--
refs/heads/master 41756be7
refs/heads/msirabella/fix/importable 2596aeb1
refs/heads/msirabella/foobar 25d231de
refs/tags/neg_1 0bc92598
refs/tags/tests-depend-on-this-being-head 64806db6
refs/tags/v0.0 27a41307
======
refs/heads/msirabella/fix/importable 2596aeb1
refs/heads/msirabella/foobar 25d231de
======
refs/tags/neg_1 0bc92598
refs/tags/tests-depend-on-this-being-head 64806db6
refs/tags/v0.0 27a41307
