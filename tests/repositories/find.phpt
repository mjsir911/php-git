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
echo getRelativePath(
	getcwd(),
	git_repository_discover("./tests/git-repo/src")
);
?>
--EXPECT--
tests/git-repo/.git/
