--TEST--
Blobs - Content
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");

$blob = new Blob($repo, new Oid("2a19b7405f795f88e9346104f4a843251e6eef2d"));

$rawcontent = $blob->rawcontent();
echo $rawcontent, PHP_EOL;

$rawsize = strlen($rawcontent);
echo $rawsize, PHP_EOL;
?>
--EXPECT--
# Hello, world!

16
