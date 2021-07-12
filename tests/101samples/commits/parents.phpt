--TEST--
Commits - Parents
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$oid = new Oid("41756be70fdc3c4eeb70cd5df7e183443db8b031");
$commit = new Commit($repo, $oid);

print_r($commit->parents());
?>
--EXPECT--
Array
(
    [0] => Commit Object
        (
            [id] => 64806db
            [encoding] => UTF-8
            [message] => Add a license file

To be clear, this license file only applies to the test repository

            [summary] => Add a license file
            [committer] => Signature Object
                (
                    [name] => Marco Sirabella
                    [email] => marco@sirabella.org
                    [when] => DateTime Object
                        (
                            [date] => 2021-04-03 00:58:33.000000
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
                            [date] => 2021-04-03 00:58:33.000000
                            [timezone_type] => 1
                            [timezone] => -07:00
                        )

                )

        )

)
