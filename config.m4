PHP_ARG_ENABLE(git2, Whether to enable the "git2" extension,
	[  --enable-git2      Enable "php-git2" extension support])

if test $PHP_GIT2 != "no"; then
	PHP_SUBST(GIT2_SHARED_LIBADD)

	PHP_ADD_SOURCES(src, repository_arginfo.h clone_arginfo.h oid_arginfo.h signature_arginfo.h commit_arginfo.h tree_arginfo.h revwalk_arginfo.h reference_arginfo.h reference_iterator_arginfo.h tag_arginfo.h revparse_arginfo.h blob_arginfo.h)
	PHP_ADD_SOURCES_X(src, repository.c clone.c oid.c signature.c commit.c tree.c revwalk.c reference.c reference_iterator.c tag.c revparse.c blob.c,$ac_extra,shared_objects_git2,yes)

	PHP_ADD_SOURCES_X(src, error.c object.c php_git2.c,$ac_extra,shared_objects_git2,yes)

	PHP_NEW_EXTENSION(git2,,$ext_shared)

	PKG_CHECK_MODULES([LIBGIT2], [libgit2 >= 1.0.0])

	PHP_EVAL_INCLINE($LIBGIT2_CFLAGS)
	PHP_EVAL_LIBLINE($LIBGIT2_LIBS)
	PHP_ADD_LIBRARY(git2,,GIT2_SHARED_LIBADD)

	ifdef([PHP_ADD_EXTENSION_DEP],
	[
		PHP_ADD_EXTENSION_DEP(git2, spl, true)
	])
	PHP_ADD_MAKEFILE_FRAGMENT()
fi
