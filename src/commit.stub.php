<?php
namespace git\commit {
	function lookup(mixed $repo, mixed $oid): mixed {};
	
	// these are propreties and I would love to make an object
	function id(mixed $commit): mixed {};
	function message_encoding(mixed $commit): string {};
	function message(mixed $commit): string {};
	function summary(mixed $commit): string {};
}
?>
