#ifdef X
X(reference_iterator, ReferenceIterator)
#elif defined XI
XI(reference_iterator, zend_ce_iterator)
#else
#ifndef PHP_GIT2_REFERENCE_ITERATOR
#define PHP_GIT2_REFERENCE_ITERATOR
#include <php.h>
#include <git2/refs.h>
#include <zend_interfaces.h>
#include "reference.h"

#include "reference_iterator_arginfo.h"

#define T reference_iterator
#define E reference_t *current;
#include "gitobj.h"

#define Z_REFERENCE_ITERATOR_P(zv) php_git2_reference_iterator_from_obj(Z_OBJ_P((zv)))

// zend_class_implements(reference_iterator_class_entry, 1, zend_ce_iterator);
#endif
#endif
