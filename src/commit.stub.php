<?php
/** @generate-function-entries */
namespace git {
	class Commit {
		public function __construct(Repository $repo, mixed $oid) {}

		// these are propreties and I would love to make an object
		public function id(): mixed {}
		public function message_encoding(): string {}
		public function message(): string {}
		public function summary(): string {}
		// public function time(mixed $commit): mixed {}
		// public function time_offset(mixed $commit): int {}
		// public function commiter(mixed $commit): mixed {}
		// public function author(mixed $commit): mixed {}
		// public function raw_header(mixed $commit): string {}
		public function tree_id(): mixed {}
	}
}
?>
