--TEST--
Tags - Listing (all)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

print_r($repo->tags());
?>
--EXPECT--
Array
(
    [neg_1] => Tag Object
        (
            [id] => 0bc9259
            [name] => neg_1
            [tagger] => Signature Object
                (
                    [name] => Marco Sirabella
                    [email] => marco@sirabella.org
                )

            [message] => What happens when I have two tags on a commit?

        )

    [tests-depend-on-this-being-head] => Commit Object
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
                )

            [author] => Signature Object
                (
                    [name] => Marco Sirabella
                    [email] => marco@sirabella.org
                )

        )

    [v0.0] => Tag Object
        (
            [id] => 27a4130
            [name] => 0.0
            [tagger] => Signature Object
                (
                    [name] => Marco Sirabella
                    [email] => marco@sirabella.org
                )

            [message] => This is version 0.0!

There is nothing here

its just a demo for annotated tags, which apparently are meant for
version releases?

from git-tag(1), but what are lightweight tags for? "are meant for
private or temporary object labels"? ok

        )

)
