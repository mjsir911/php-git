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
$oid = git_oid_fromstr($sha);
var_dump($oid);

/* Make a shortened printable string from an OID */
$shortsha = git_oid_tostr($oid, 8);
echo $shortsha;
?>
--EXPECT--
resource(4) of type (Git OID)
4a202b34
