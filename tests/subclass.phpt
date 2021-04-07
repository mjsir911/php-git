--TEST--
Subclassing - Repositories
--SKIPIF--
<?php
if (!extension_loaded('git2')) {
    echo 'skip';
}
?>
--FILE--
<?php
class Subclass extends Repository {
	public function __construct(string $path) {
		parent::__construct($path);
	}

	public function getCommit(string $oid) {
		$oid = git_oid_fromstr($oid);
		return new Commit($this, $oid);
	}
}
$repo = new Subclass("./tests/repo.git");

echo $repo->getCommit("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131")->summary();
?>
--EXPECT--
Initial commit - add readme
