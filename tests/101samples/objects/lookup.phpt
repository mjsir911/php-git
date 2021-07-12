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

$oid = new Oid("0a64a3ad3af9c3b185067c47e47d46f4faa3b17d");
print_r(new Commit($repo, $oid))
?>
--EXPECTF--
Commit Object
(
    [id] => 0a64a3a
    [encoding] => UTF-8
    [message] => Add code to run (and a subdirectory)

This is for testing out git-php

    [summary] => Add code to run (and a subdirectory)
    [committer] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
            [when] => DateTime Object
                (
                    [date] => 2021-04-02 17:28:23.000000
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
                    [date] => 2021-04-02 17:28:23.000000
                    [timezone_type] => 1
                    [timezone] => -07:00
                )

        )

)
