<?php
/** @generate-function-entries */
namespace git {
	class Revwalk implements Iterator {
		public function __construct(Repository $repo) {}

		public function push_range(string $range): void {}
		public function push_head(): void {}
		public function push_ref(string $ref): void {}
		public function push_glob(string $ref): void {}

		public function hide(Oid $oid): void {}
		public function hide_glob(string $glob): void {}

		public function current(): Oid {}
		public function key(): int {}
		public function next(): void {}
		public function rewind(): void {}
		public function valid(): bool {}
	}
}
?>
