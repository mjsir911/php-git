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
	public string $something_undefined;
	public int $something_defined;
	public function __construct(string $path) {
		parent::__construct($path);
		$this->something_defined = 42;
	}

	public function getCommit(string $oid) {
		$oid = git_oid_fromstr($oid);
		return new Commit($this, $oid);
	}
}
$repo = new Subclass("./tests/repo.git");

$sha = "faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131";
$commit = new Commit($repo, git_oid_fromstr($sha));
echo $commit->summary(), PHP_EOL;
echo $repo->getCommit("faa1fb22c4e0fb79bed3d3b7ea5901b7919fd131")->summary(), PHP_EOL;

echo $repo->something_defined, PHP_EOL;

if (!isset($repo->something_undefined)) {
	echo 'Success!';
}
?>
--EXPECT--
Initial commit - add readme
Initial commit - add readme
42
Success!
