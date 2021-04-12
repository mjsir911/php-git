<?php
/** @generate-function-entries */
namespace git {
	class Reference {
		public static function lookup(Repository $repo, string $name): Reference {}
		public static function dwim(Repository $repo, string $shorthand): Reference {}
		public static function name_to_id(Repository $repo, string $name): Oid {}

		public function target(): Oid {}
		public function name(): string {}
		public function shorthand(): string {}
	}
}
?>
