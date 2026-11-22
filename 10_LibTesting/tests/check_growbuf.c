#include <check.h>

#include <config.h>

#include <growbuf.h>

START_TEST(test_init) {
    float *a = 0;
    ck_assert_uint_eq(buf_capacity(a), 0);
    ck_assert_uint_eq(buf_size(a), 0);
}
END_TEST

START_TEST(test_push_one) {
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    ck_assert(a[0] == 1.3f);
    buf_free(a);
}
END_TEST

START_TEST(test_clear) {
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert(a != 0);
    buf_free(a);
    ck_assert(a == 0);
}
END_TEST

START_TEST(test_clear_null) {
    float *a = 0;
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert(a == 0);
}
END_TEST

START_TEST(test_push_many) {
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_uint_eq(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)buf_size(ai); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000);
    buf_free(ai);
}
END_TEST

START_TEST(test_grow) {
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    ck_assert_uint_eq(buf_size(ai), 0);
    buf_free(ai);
}
END_TEST

START_TEST(test_trunc) {
    long *ai = 0;
    buf_grow(ai, 1000);
    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);
    buf_free(ai);
}
END_TEST

START_TEST(test_pop) {
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_uint_eq(buf_size(a), 4);
    ck_assert(buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    ck_assert_uint_eq(buf_size(a), 3);
    ck_assert(buf_pop(a) == (float)1.3f);
    ck_assert(buf_pop(a) == (float)1.2f);
    ck_assert(buf_pop(a) == (float)1.1f);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);
}
END_TEST

Suite * growbuf_suite(void) {
    Suite *s = suite_create("growbuf");

    TCase *tc_basic = tcase_create("basic");
    tcase_add_test(tc_basic, test_init);
    tcase_add_test(tc_basic, test_push_one);
    tcase_add_test(tc_basic, test_clear);
    tcase_add_test(tc_basic, test_clear_null);
    suite_add_tcase(s, tc_basic);

    TCase *tc_push = tcase_create("push");
    tcase_add_test(tc_push, test_push_many);
    suite_add_tcase(s, tc_push);

    TCase *tc_size = tcase_create("grow_trunc");
    tcase_add_test(tc_size, test_grow);
    tcase_add_test(tc_size, test_trunc);
    suite_add_tcase(s, tc_size);

    TCase *tc_pop = tcase_create("pop");
    tcase_add_test(tc_pop, test_pop);
    suite_add_tcase(s, tc_pop);

    return s;
}

int main(void) {
    SRunner *sr = srunner_create(growbuf_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}