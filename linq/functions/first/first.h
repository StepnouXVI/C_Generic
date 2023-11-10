#ifndef FIRST_H
#define FIRST_H
#include "../../Enumerators/IEnumerator/IEnumerator.h"


void *first(enumerator_t* source);
void *first_with_predicate(const predicate_t predicate, enumerator_t* source);

#endif