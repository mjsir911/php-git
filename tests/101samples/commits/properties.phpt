--TEST--
Commits - Properties
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

$commit = new Commit($repo, $oid);

echo git_oid_tostr($commit->id(), 8);
echo PHP_EOL;
echo $commit->message_encoding();
echo PHP_EOL;
echo $commit->message();
echo PHP_EOL;
echo $commit->summary();
echo PHP_EOL;
# echo git_commit_time($commit); // special
# echo git_commit_time_offset($commit); // int
# echo git_commit_committer($commit); // special
# echo git_commit_author($commit); // special
# echo git_commit_raw_header($commit);
# echo git_commit_tree_id($commit);
?>
--EXPECT--
faa1fb22
UTF-8
Initial commit - add readme

Initial commit - add readme
