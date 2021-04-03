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
$repo = git_repository_open_bare("./tests/repo.git");

$revwalker = git_revwalk_new($repo);
git_revwalk_push_range($revwalker, "faa1fb22..64806db6");

while ($oid = git_revwalk_next($revwalker)) {
	echo git_oid_tostr($oid, 8), PHP_EOL;
}
?>
--EXPECT--
64806db6
0a64a3ad
