--TEST--
Tags - Annotation Properties
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

$oid = new Oid("27a4130713568080615800200f02365b904e797d");

$tag = $repo->lookup_tag($oid);

echo $tag->target_id(), PHP_EOL;
echo $tag->target_type(), PHP_EOL;
echo $tag->name(), PHP_EOL;
print_r($tag->tagger());
echo $tag->message(), PHP_EOL;
?>
--EXPECT--
faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131
Commit
0.0
Signature Object
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
This is version 0.0!

There is nothing here

its just a demo for annotated tags, which apparently are meant for
version releases?

from git-tag(1), but what are lightweight tags for? "are meant for
private or temporary object labels"? ok
