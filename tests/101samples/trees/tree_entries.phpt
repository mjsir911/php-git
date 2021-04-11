--TEST--
Trees - Tree Entries
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
$repo = Repository::open_bare("./tests/repo.git");
$tree = $repo->revparse_single("HEAD^{tree}");

echo count($tree), PHP_EOL;

$entry = $tree->byindex(0);

echo $entry->name(), PHP_EOL; /* filename */
// print_r($entry->type()); /* blob or tree */
echo $entry->filemode(), PHP_EOL; /* *NIX filemode */

$entry2 = $tree->bypath("a/b/c.txt");
// no need to free, GCd!
print_r($entry2);
// unset($entry2);
?>
--EXPECT--
4
LICENSE
33188
TreeEntry Object
(
    [id] => 64ebe54d
    [filemode] => 33188
    [name] => c.txt
)
