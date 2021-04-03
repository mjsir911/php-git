--TEST--
Repositories - Find Repository
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
# Check if a given path is inside a repository and return the repository root
# directory if found.
require "tests/utils.inc";
$clonepath = __DIR__ . '/git-repo';
localRepo($clonepath);
echo getRelativePath(
	__DIR__,
	git_repository_discover($clonepath . '/src/')
);
?>
--EXPECT--
git-repo/.git/
--CLEAN--
<?php
require "tests/utils.inc";
$clonepath = __DIR__ . '/git-repo';
rmdir_rf($clonepath);
?>
