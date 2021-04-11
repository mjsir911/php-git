--TEST--
References - Lookups (resolved)
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

$oid = Reference::name_to_id($repo, "HEAD");
echo $oid->__toString(8);
?>
--EXPECTF--
41756be7
