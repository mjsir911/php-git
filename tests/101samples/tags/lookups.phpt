--TEST--
Tags - Lookups (annotations)
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

$oid = new Oid("0bc92598491cfa2e53a170130f81f33b5479d6af");

$tag = $repo->lookup_tag($oid);
print_r($tag);
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
