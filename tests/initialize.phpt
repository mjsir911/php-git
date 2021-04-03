--TEST--
Best Practices - Initialize the library
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# The library needs to keep some global state and initialize its dependencies.
# You must therefore initialize the library before working with it
#
# Usually you don’t need to call the shutdown function as the operating system
# will take care of reclaiming resources, but if your application uses libgit2
# in some areas which are not usually active, you can use
#
# in php-git this is done automatically
echo extension_loaded('git2');
?>
--EXPECT--
1
