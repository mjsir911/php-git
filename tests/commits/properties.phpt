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
$repo = git_repository_open_bare("./tests/repo.git");
$oid = git_oid_fromstr("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131");

$commit = git_commit_lookup($repo, $oid);

echo git_oid_tostr(git_commit_id($commit), 8);
echo PHP_EOL;
echo git_commit_message_encoding($commit);
echo PHP_EOL;
echo git_commit_message($commit);
echo PHP_EOL;
echo git_commit_summary($commit);
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
