<?php
/** @generate-function-entries */
namespace git {
	class Reference {
		public static function lookup(Repository $repo, string $name): Reference {}
		public static function dwim(Repository $repo, string $shorthand): Reference {}
		public static function name_to_id(Repository $repo, string $name): Oid {}

		public function target(): Oid {}
		public function peel(): object {}
		public function name(): string {}
		public function shorthand(): string {}

		/** @alias git\Reference::shorthand */
		public function __toString(): string {} // for polymorphism with Commit
		public function __debugInfo(): array {}
	}
}
?>
