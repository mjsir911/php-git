--TEST--
Tags - Lookups (glob)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

print_r($repo->tags("v0.*"));
?>
--EXPECT--
Array
(
    [v0.0] => Tag Object
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

)
