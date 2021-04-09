#ifndef T
#error "no T"
#endif
#include "ctl.h"
#define CE(T) JOIN(T, class_entry)
#define OH(T) JOIN(T, object_handlers)

#ifndef GITOBJ_COMMON_DEFS
#define GITOBJ_COMMON_DEFS
#define O(o) ((o)->obj)
#endif

extern zend_class_entry *CE(T);

#define A JOIN(T, t)
#define G JOIN(git, T)

typedef struct A {
	G *obj;
	#ifdef E
	E
	#endif
	zend_object std;
} A;

#define PG2(s) JOIN(JOIN(php_git2, T), s)

A *PG2(from_obj)(zend_object *obj);

extern zend_object *PG2(new)(zend_class_entry *);
extern void PG2(free)(zend_object *zobj);

#ifdef NOMAIN
extern zend_object_handlers OH(T);
#endif

#ifdef MAIN
zend_class_entry *CE(T) = NULL;
zend_object_handlers OH(T);

A *PG2(from_obj)(zend_object *obj) {
	return ((A *)((char *)(obj) - XtOffsetOf(A, std)));
}


#ifndef NOMAIN
zend_object *PG2(new)(zend_class_entry *ce) {
	A *obj = zend_object_alloc(sizeof(A), ce);
	zend_object_std_init(&obj->std, ce);
	object_properties_init(&obj->std, ce);
	obj->std.handlers = &OH(T);
	return &obj->std;
}

void PG2(free)(zend_object *zobj) {
	A *obj = PG2(from_obj)(zobj);

	if (O(obj)) {
		JOIN(G, free)(O(obj));
	}
	zend_object_std_dtor(&obj->std);
}
#endif
#endif

#undef NOMAIN
#undef CE
#undef OH
#undef A
#undef G
#undef PG2
#undef E
#undef T
