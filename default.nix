{ pkgs ? import <nixpkgs-unstable> { } }:
with pkgs;

let php=(import (builtins.fetchTarball https://github.com/talyz/nixpkgs/archive/refs/heads/php-dev-output.tar.gz) {}).php80; in
php.buildPecl {
	pname = "git";
	version = "0";

	src = ./.;

	phpParser = (fetchzip {
		url = "https://github.com/nikic/php-parser/archive/v4.9.0.tar.gz";
		sha256 = "0zs0jl0vx9n9vd0wvsah7g5f9rvnxk83crzwi6add1a5gj3ldbj5";
	});
	preBuild = ''
		ln -s $phpParser build/PHP-Parser-4.9.0
	'';

	nativeBuildInputs = [ (php.withExtensions ({all, ...}: with all; [tokenizer])) ];
	buildInputs = [ pkg-config libgit2 ];
}
