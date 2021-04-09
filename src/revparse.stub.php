<?php
namespace git {
	// function revparse(Repository $repo, string $spec): Revspec {}
	function revparse_ext(Repository $repo, string $spec): Reference {}
	function revparse_single(Repository $repo, string $spec): object {}
}
?>
