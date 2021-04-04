<?php
/** @generate-function-entries */
namespace git {
	class Commit {
		public function __construct(Repository $repo, mixed $oid) {}

		// these are propreties and I would love to make an object
		public function id(mixed $commit): mixed {}
		public function message_encoding(mixed $commit): string {}
		public function message(mixed $commit): string {}
		public function summary(mixed $commit): string {}
		// public function time(mixed $commit): mixed {}
		// public function time_offset(mixed $commit): int {}
		// public function commiter(mixed $commit): mixed {}
		// public function author(mixed $commit): mixed {}
		// public function raw_header(mixed $commit): string {}
		public function tree_id(mixed $commit): mixed {}
	}
}
?>
