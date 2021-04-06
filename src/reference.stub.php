<?php
/** @generate-function-entries */
namespace git {
	class Reference {
		public static function lookup(Repository $repo, string $name): Reference {}
		public static function dwim(Repository $repo, string $shorthand): Reference {}
		public static function name_to_id(Repository $repo, string $name): mixed {}

		public function target(): mixed {}
		public function name(): string {}
	}
}
?>
