--TEST--
Objects - SHAs and OIDs
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# SHA-1 hashes are usually written as 40 characters of hexadecimal. These are
# converted to a binary representation internally, called git_oid, and there
# are routines for converting back and forth.

/* Convert a SHA to an OID */
$sha = "4a202b346bb0fb0db7eff3cffeb3c70babbd2045";
$oid = new Oid($sha);
print_r($oid);

/* Make a shortened printable string from an OID */
$shortsha = $oid->__toString(8);
echo $shortsha;
?>
--EXPECT--
Oid Object
(
    [sha] => 4a202b34
)
4a202b34
