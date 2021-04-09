#ifndef T
#error "no T"
#endif
#include "ctl.h"
#define CE(T) JOIN(T, class_entry)
#define OH(T) JOIN(T, object_handlers)

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

inline A *PG2(from_obj)(zend_object *obj) {
	return ((A *)((char *)(obj) - XtOffsetOf(A, std)));
}

#ifdef MAIN
zend_class_entry *CE(T) = NULL;
zend_object_handlers OH(T);

zend_object *PG2(new)(zend_class_entry *ce) {
	A *obj = zend_object_alloc(sizeof(A), ce);
	zend_object_std_init(&obj->std, ce);
	object_properties_init(&obj->std, ce);
	obj->std.handlers = &OH(T);
	return &obj->std;
}

void PG2(free)(zend_object *zobj) {
	A *obj = PG2(from_obj)(zobj);

	if (obj->obj) {
		JOIN(G, free)(obj->obj);
	}
	zend_object_std_dtor(&obj->std);
}
#endif


#undef CE
#undef OH
#undef A
#undef G
#undef PG2
