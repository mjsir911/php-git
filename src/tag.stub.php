<?php
/** @generate-function-entries */
namespace git {
	class Tag {
		// protected function __construct(Repository $repo, Oid $oid) {}

		public function target_id(): Oid {}
		public function id(): Oid {}
		// public function target_type(): mixed {}
		public function name(): string {}
		public function tagger(): Signature {}
		public function message(): string {}
		public function __debugInfo(): array {}
	}
}
?>
