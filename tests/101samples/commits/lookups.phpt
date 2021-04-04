--TEST--
Commits - Lookups
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$oid = git_oid_fromstr("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131");

var_dump(git_commit_lookup($repo, $oid))
?>
--EXPECTF--
resource(%d) of type (Git Commit)
