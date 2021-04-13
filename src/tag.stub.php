<?php
/** @generate-function-entries */
namespace git {
	class Tag {
		// protected function __construct(Repository $repo, Oid $oid) {}
		static public function list(Repository $repo, ?string $pattern): array {}
		static public function lookup(Repository $repo, Oid $oid): ?Tag {}
		static public function foreach(callable $callback): void {}

		public function target_id(): Oid {}
		public function target_type(): string {}
		public function id(): Oid {}
		// public function target_type(): mixed {}
		public function name(): string {}
		public function tagger(): Signature {}
		// this is for polymorphism with git\Commit
		/** @implementation-alias git\Tag::tagger */
		public function author(): Signature {}
		public function message(): string {}
		public function __debugInfo(): array {}
	}
}
?>
