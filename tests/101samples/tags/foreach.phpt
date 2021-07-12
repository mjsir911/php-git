--TEST--
Tags - Foreach
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

$repo->foreach_tag(function($obj) {
	print_r($obj);
});
?>
--EXPECT--
Tag Object
(
    [id] => 0bc9259
    [name] => neg_1
    [tagger] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
            [when] => DateTime Object
                (
                    [date] => 2021-04-07 08:51:04.000000
                    [timezone_type] => 1
                    [timezone] => -07:00
                )

        )

    [message] => What happens when I have two tags on a commit?

    [time] => DateTime Object
        (
            [date] => 2021-04-07 08:51:04.000000
            [timezone_type] => 1
            [timezone] => -07:00
        )

)
Commit Object
(
    [id] => 64806db
    [encoding] => UTF-8
    [message] => Add a license file

To be clear, this license file only applies to the test repository

    [summary] => Add a license file
    [time] => DateTime Object
        (
            [date] => 2021-04-03 00:58:33.000000
            [timezone_type] => 1
            [timezone] => -07:00
        )

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
Tag Object
(
    [id] => 27a4130
    [name] => 0.0
    [tagger] => Signature Object
        (
            [name] => Marco Sirabella
            [email] => marco@sirabella.org
            [when] => DateTime Object
                (
                    [date] => 2021-04-07 08:37:26.000000
                    [timezone_type] => 1
                    [timezone] => -07:00
                )

        )

    [message] => This is version 0.0!

There is nothing here

its just a demo for annotated tags, which apparently are meant for
version releases?

from git-tag(1), but what are lightweight tags for? "are meant for
private or temporary object labels"? ok

    [time] => DateTime Object
        (
            [date] => 2021-04-07 08:37:26.000000
            [timezone_type] => 1
            [timezone] => -07:00
        )

)
