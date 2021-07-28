--TEST--
References - Lookups (short name)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# Get the object pointed to by a symbolic reference (or a chain of them).
$repo = Repository::open_bare("./tests/repo.git");

$ref = Reference::dwim($repo, "master");

print_r($ref);
?>
--EXPECT--
Reference Object
(
    [name] => master
    [peel] => Commit Object
        (
            [id] => 41756be
            [encoding] => UTF-8
            [message] => Add file for blob test based on 101 samples

            [summary] => Add file for blob test based on 101 samples
            [time] => DateTime Object
                (
                    [date] => 2021-04-11 09:43:41.000000
                    [timezone_type] => 1
                    [timezone] => -07:00
                )

            [committer] => Signature Object
                (
                    [name] => Marco Sirabella
                    [email] => marco@sirabella.org
                    [when] => DateTime Object
                        (
                            [date] => 2021-04-11 09:43:41.000000
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
                            [date] => 2021-04-11 09:43:41.000000
                            [timezone_type] => 1
                            [timezone] => -07:00
                        )

                )

        )

)
