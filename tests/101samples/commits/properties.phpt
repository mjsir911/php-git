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
$oid = new Oid("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131");

$commit = new Commit($repo, $oid);

echo $commit->id()->__toString(8), PHP_EOL;
echo $commit->message_encoding(), PHP_EOL;
echo $commit->message(), PHP_EOL;
echo $commit->summary(), PHP_EOL;
print_r($commit->time());
echo $commit->committer()->name(), PHP_EOL;
echo $commit->committer()->email(), PHP_EOL;
echo $commit->author()->name(), PHP_EOL;
echo $commit->author()->email(), PHP_EOL;
# echo git_commit_raw_header($commit);
# echo git_commit_tree_id($commit);
print_r($commit);
?>
--EXPECT--
faa1fb22
UTF-8
Initial commit - add readme

Initial commit - add readme
DateTime Object
(
    [date] => 2021-04-02 17:26:16.000000
    [timezone_type] => 1
    [timezone] => -07:00
)
Marco Sirabella
marco@sirabella.org
Marco Sirabella
marco@sirabella.org
Commit Object
(
    [id] => faa1fb2
    [encoding] => UTF-8
    [message] => Initial commit - add readme

    [summary] => Initial commit - add readme
    [time] => DateTime Object
        (
            [date] => 2021-04-02 17:26:16.000000
            [timezone_type] => 1
            [timezone] => -07:00
        )

    [committer] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
            [when] => DateTime Object
                (
                    [date] => 2021-04-02 17:26:16.000000
                    [timezone_type] => 1
                    [timezone] => -07:00
                )

        )

    [author] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
            [when] => DateTime Object
                (
                    [date] => 2021-04-02 17:26:16.000000
                    [timezone_type] => 1
                    [timezone] => -07:00
                )

        )

)
