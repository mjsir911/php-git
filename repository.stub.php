<?php
namespace git\repository {
	// can't return resource type? :(
	function init(string $path, bool $bare=false): mixed {}
	function commondir(mixed $repo): string {}
	function open(string $path): mixed {}
	function open_bare(string $path): mixed {}
	function discover(string $start_path, bool $across_fs=false): string {}
}
?>
