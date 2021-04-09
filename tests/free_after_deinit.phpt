--TEST--
Crash - GC after RSHUTDOWN
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php

$repo = Repository::open_bare("./tests/repo.git");

$commits = new Revwalk($repo);
$commits->push_head();

$dup = [ $repo ];

unset($repo, $commits);
gc_collect_cycles();

echo 'Success!', PHP_EOL;

?>
--EXPECT--
Success!
