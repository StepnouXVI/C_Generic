#ifndef LAST_H
#define LAST_H
#include "../../Enumerators/IEnumerator/IEnumerator.h"


void *last(enumerator_t* enumerator_t);
void *last_with_predicate(predicate_t predicate, enumerator_t* enumerator_t);

#endif