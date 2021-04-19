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
--EXPECT--
Tag Object
(
    [id] => 0bc9259
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
    [id] => 27a4130
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
