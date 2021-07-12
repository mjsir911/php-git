--TEST--
Signatures - Properties
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$oid = new Oid("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131");

$commit = new Commit($repo, $oid);
$sig = $commit->author();

echo $sig->name(), PHP_EOL;
echo $sig->email(), PHP_EOL;
// echo $sig->when(), PHP_EOL;
print_r($sig);
?>
--EXPECT--
Marco Sirabella
marco@sirabella.org
Signature Object
(
    [name] => Marco Sirabella
    [email] => marco@sirabella.org
)
