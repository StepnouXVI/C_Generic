#include "../../../support/validators.h"
#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"

#include <stdlib.h>

void destruct_sorted_list(sorted_list_t *list) {
  if (list == NULL)
    return;

  destruct_linked_list((linked_list_t *)list);
}
