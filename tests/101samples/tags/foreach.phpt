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

$repo->foreach_tag(function($obj) use ($repo) {
	print_r($obj);
});
?>
--EXPECTF--
Tag Object
(
    [id] => 0bc92598491cfa2e53a170130f81f33b5479d6af
    [name] => neg_1
    [tagger] => Signature Object
        (
        )

    [message] => What happens when I have two tags on a commit?

)
Commit Object
(
)
Tag Object
(
    [id] => 27a4130713568080615800200f02365b904e797d
    [name] => 0.0
    [tagger] => Signature Object
        (
        )

    [message] => This is version 0.0!

There is nothing here

its just a demo for annotated tags, which apparently are meant for
version releases?

from git-tag(1), but what are lightweight tags for? "are meant for
private or temporary object labels"? ok

)
