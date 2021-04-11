<?php
/** @generate-function-entries */
namespace git {
	interface Object {
		public function id(): Oid {}
		public function short_id(): string {}
		// static public function lookup(Repository $repo, Oid $id): ?Object {}
	}
}
?>
