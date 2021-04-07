<?php

/** @generate-function-entries */

namespace git {
	class Repository {
		protected function __construct(string $bare_path) {}

		public static function init(string $path, bool $bare = false): Repository {}
		public static function open(string $path): Repository {}
		public static function open_bare(string $path): Repository {}
		public static function discover(string $start_path, bool $across_fs=false, array $ceiling_dirs=[]): string {}
		public function commondir(): string {}

		public function references(): ReferenceIterator {}
	}
}
?>
