--TEST--
Revwalk - Pushing and Hiding
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

/* Pushing marks starting points */
$walker->push_head();
$walker->push_ref("HEAD");
$walker->push_glob("tags/*");

/* Hiding marks stopping points */
$walker->hide(new Oid("0a64a3ad3af9c3b185067c47e47d46f4faa3b17d"));
$walker->hide_glob("tags/v0.*");

foreach ($walker as $oid) {
	echo $oid->__toString(8), PHP_EOL;
}
?>
--EXPECT--
64806db6
