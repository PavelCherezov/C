#include "my_test.h"

int main() {
  int failed = 0;

  Suite* my_decimal_test[] = {my_add_suite(),
                               my_sub_suite(),
                               my_mul_suite(),
                               my_div_suite(),
                               my_is_less_suite(),
                               my_is_less_or_equal_suite(),
                               my_is_greater_suite(),
                               my_is_greater_or_equal_suite(),
                               my_is_equal_suite(),
                               my_is_not_equal_suite(),
                               my_from_int_to_decimal_suite(),
                               my_from_float_to_decimal_suite(),
                               my_from_decimal_to_int_suite(),
                               my_from_decimal_to_float_suite(),
                               my_floor_suite(),
                               my_round_suite(),
                               my_truncate_suite(),
                               my_negate_suite(),
                               NULL};

  for (int i = 0; my_decimal_test[i] != NULL; i++) {
    printf("-----------------------------------------------\n      ");

    SRunner* sr = srunner_create(my_decimal_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);

    srunner_free(sr);
  }

  if (failed == 0) {
    printf(
        "\033[32m------------------- SUCCESS -------------------\033[0m\n\n");
  } else {
    printf("\033[31m------------------ FAILED: %d -----------------\033[0m\n\n",
           failed);
  }

  return (failed == 0) ? 0 : 1;
}
