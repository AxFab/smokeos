#include <smkos/mod/vfs.h>
#include <stdlib.h>
#include <check.h>


START_TEST(ut_look_for_inode)
{
   

}
END_TEST


 int main(void)
{
  int number_failed;
  Suite *s;
  TCase *tc;
  SRunner *sr;

  s = suite_create("Kernel");
  tc = tcase_create("VFS");

  tcase_add_test(tc, ut_look_for_inode);

  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
