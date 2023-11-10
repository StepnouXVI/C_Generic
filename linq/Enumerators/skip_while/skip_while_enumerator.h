#ifndef SKIP_WHILE_ENUMERATORS_H
#define SKIP_WHILE_ENUMERATORS_H
#include "../../support/types.h"
#include "../IEnumerator/IEnumerator.h"

enumerator_t skip_while(predicate_t predicate, enumerator_t *enumerator_t);

#endif