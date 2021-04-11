<?php
/** @generate-function-entries */
namespace git {
	class TreeEntry {
		public function filemode(): int {}
		public function id(): Oid {}
		public function name(): string {}
		public function type(): string {}
		public function to_object(Repository $repo): object {}

		public function __debugInfo(): array {}
	}
	class Tree implements Countable, ArrayAccess, Iterator {
		public function __construct(Repository $repo, Oid $oid) {}
		public function id(): Oid {}
		// would love a better suggestion than implementing TreeEntry
		// but unfortunately, it contains information like "name"
		public function byindex(int $idx): TreeEntry {}
		public function byname(string $filename): TreeEntry {}
		public function bypath(string $path): ?TreeEntry {}
		// public function walk(callable $cb): void {}

		public function __debugInfo(): array {}

		// for Countable
		public function count(): int {}

		// for ArrayAccess
		public function offsetExists(mixed $filename): bool {}
		/** @alias git_Tree::byname */
		public function offsetGet(mixed $filename): TreeEntry {}
		// not allowed
		public function offsetSet(mixed $filename, mixed $value): void {}
		public function offsetUnset(mixed $filename): void {}

		// for Iterator
		public function current(): Tree {}
		public function key(): TreeEntry {}
		public function next(): void {}
		public function rewind(): void {}
		public function valid(): void {}

	}
}
?>
