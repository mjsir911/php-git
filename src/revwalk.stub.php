<?php
/** @generate-function-entries */
namespace git {
	class Revwalk implements IteratorAggregate {
		public function __construct(Repository $repo) {}
		public function push_range(string $range): void {}
		public function push_head(): void {}
		public function getIterator(): Iterator {}
	}
}
?>
