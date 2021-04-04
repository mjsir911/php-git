--TEST--
Objects - Lookups
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# There are four kinds of objects in a Git repository – commits, trees, blobs,
# and tag annotations. Each type of object has an API for doing lookups.

$repo = Repository::open_bare("./tests/repo.git");

$oid = git_oid_fromstr("0a64a3ad3af9c3b185067c47e47d46f4faa3b17d");
var_dump(new Commit($repo, $oid))
?>
--EXPECTF--
object(Commit)#%d (0) {
}
