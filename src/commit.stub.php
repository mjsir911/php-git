<?php
/** @generate-function-entries */
namespace git {
	class Commit {
		public function __construct(Repository $repo, Oid $oid) {}

		// these are propreties and I would love to make an object
		public function id(): Oid {}
		public function message_encoding(): string {}
		public function message(): string {}
		public function summary(): string {}
		// public function time(mixed $commit): mixed {}
		// public function time_offset(mixed $commit): int {}
		public function committer(): Signature {}
		public function author(): Signature {}
		// public function raw_header(mixed $commit): string {}
		public function tree_id(): Oid {}
		public function tree(): Tree {}

		public function parents(): array {}
	}
}
?>
