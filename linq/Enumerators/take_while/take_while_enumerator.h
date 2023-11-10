#ifndef TAKE_WHILE_ENUMERATORS_H
#define TAKE_WHILE_ENUMERATORS_H
#include "../../support/types.h"
#include "../IEnumerator/IEnumerator.h"

enumerator_t take_while(predicate_t predicate, enumerator_t *enumerator_t);

#endif