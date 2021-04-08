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

		public function tags(?string $pattern): array {}
		public function lookup_tag(Oid $oid): ?Tag {}
		public function foreach_tag(callable $callback): void {}
		// public function create_tag_lightweight(string $name, Oid $target, bool $force): Oid {}
		// public function create_tag(string $name, Oid $target, Signature $tagger, string $message, bool $force): Oid {}
	}
}
?>
