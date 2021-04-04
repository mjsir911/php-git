<?php
/** @generate-function-entries */
namespace git {
	class Revwalk implements IteratorAggregate {
		public function __construct(Repository $repo) {}
		public function getIterator(): Iterator {} // this is needed for iteration

		public function push_range(string $range): void {}
		public function push_head(): void {}
		public function push_ref(string $ref): void {}
		public function push_glob(string $ref): void {}

		public function hide(mixed $oid): void {}
		public function hide_glob(string $glob): void {}
	}
}
?>
