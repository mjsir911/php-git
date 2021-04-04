--TEST--
Best Practices - Freeing
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# Anytime libgit2 fills in a non-const pointer for you, you should be using a
# _free call to release the resource.
# 
# Fortunately, php does this automatically
$tempdir = exec("mktemp -d");
$repo = Repository::init($tempdir, false);
unset($repo);
?>
--EXPECT--
--CLEAN--
<?php
rmdir($tempdir);
?>
