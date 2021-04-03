PHP_ARG_ENABLE(git2, Whether to enable the "git2" extension,
	[  --enable-git2      Enable "php-git2" extension support])

if test $PHP_GIT2 != "no"; then
	PHP_SUBST(GIT2_SHARED_LIBADD)

	PHP_NEW_EXTENSION(git2, src/php_git2.c src/repository.c src/clone.c src/oid.c src/commit.c src/revwalk.c src/error.c, $ext_shared)

	PKG_CHECK_MODULES([LIBGIT2], [libgit2 >= 1.1.0])

	PHP_EVAL_INCLINE($LIBGIT2_CFLAGS)
	PHP_EVAL_LIBLINE($LIBGIT2_LIBS)
	PHP_ADD_LIBRARY(git2,,GIT2_SHARED_LIBADD)

	ifdef([PHP_ADD_EXTENSION_DEP],
	[
		PHP_ADD_EXTENSION_DEP(git2, spl, true)
	])
fi
