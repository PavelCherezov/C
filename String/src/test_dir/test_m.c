#include "test.h"

int main(void) {
  int fail = 0;
  Suite *my_string_test[] = {
      test_memchr(),    test_memcmp(),    test_memcpy(),     test_memset(),
      test_strchr(),    test_strncat(),   test_strncmp(),    test_strncpy(),
      test_strcspn(),   test_strerror(),  test_strlen(),     test_strpbrk(),
      test_strrchr(),   test_strstr(),    test_strtok(),     test_insert(),
      test_to_lower(),  test_to_upper(),  test_trim(),       test_sprintf_c(),
      test_sprintf_d(), test_sprintf_f(), test_sprintf_u(),  test_sprintf_s(),
      test_sprintf_o(), test_sprintf_x(), test_sprintf_hX(), NULL};

  for (int i = 0; my_string_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(my_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    fail += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("FAILED: %d", fail);

  if (fail == 0) {
    return 0;
  } else {
    return 1;
  }
}
