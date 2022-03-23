/**
 * \file        collection_test.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#include "unity.h"
#include "unity_fixture.h"

#include "collection.h"
#include "collection_port_fs.h"

#include "coll_port_fs_mock.h"
#include "coll_port_serializer_mock.h"
#include "slist.h"

#include <string.h>
/*----------------------------------------------*/
/*----------------------------------------------*/
/*----------------------------------------------*/
/*----------------------------------------------*/

TEST_GROUP(collection_test);

TEST_SETUP(collection_test)
{
    coll_fs_mock_init();
}

TEST_TEAR_DOWN(collection_test)
{
}

TEST(collection_test, coll_elem_add_null)
{
    TEST_ASSERT_EQUAL(-COLL_ERR_INVAL,
                      collection_elem_add(NULL, NULL, NULL, 0));
}

TEST(collection_test, coll_elem_add_one_without_serializer)
{
    coll_t    collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t   content[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    elem_id_t elem_id    = "elem_1";

    /* Try to add too big file. */
    TEST_ASSERT_EQUAL(-COLL_ERR_FBIG, collection_elem_add(&collection,
                                                          elem_id,
                                                          content,
                                                          COLL_FS_MOCK_FSIZE_MAX
                                                          + 1));

    /* Try to add valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                   elem_id,
                                                   content,
                                                   sizeof(content)));

    /* Try to overwrite file. */
    TEST_ASSERT_EQUAL(-COLL_ERR_EXIST, collection_elem_add(&collection,
                                                           elem_id,
                                                           content,
                                                           sizeof(content)));
}

TEST(collection_test, coll_elem_add_one_with_serializer)
{
    coll_t    collection = { .path = "/tst", .p_serializer = &serializer };
    tst_pet_t pet =
    {
        .buff = {0},
        .data = {
            ._Pet_name_tstr = {{.value = (const uint8_t*)"foo", .len = 3},
                     {.value = (const uint8_t*)"bar", .len = 3}},
            ._Pet_name_tstr_count = 2,
            ._Pet_birthday = {.value = (uint8_t[]){1,2,3,4,5,6,7,8}, .len = 8},
            ._Pet_species_choice = _Pet_species_dog,
        }
    };
    elem_id_t elem_id = "pet_1";

    /* Try to add valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                   elem_id,
                                                   &pet,
                                                   sizeof(pet)));
}

TEST(collection_test, coll_elem_add_too_much_files_without_serializer)
{
    coll_t  collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t content[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    char    suffix     = '1';
    char    elem_id[]  = "elem_0";

    /* Try to add too much files. */
    for(uint32_t idx = 0; idx < COLL_FS_MOCK_MAX_NO_OF_FILES; idx++)
    {
        elem_id[5] = suffix++;
        TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                       elem_id,
                                                       content,
                                                       sizeof(content)));
    }

    /* Adding once again should fail. */
    elem_id[5] = suffix++;
    TEST_ASSERT_EQUAL(-COLL_ERR_NOSPC, collection_elem_add(&collection,
                                                           elem_id,
                                                           content,
                                                           sizeof(content)));
}

TEST(collection_test, coll_elem_get_null)
{
    TEST_ASSERT_EQUAL(-COLL_ERR_INVAL,
                      collection_elem_get(NULL, NULL, NULL, NULL));
}

TEST(collection_test, coll_elem_get_one_without_serializer)
{
    coll_t    collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t   expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    elem_id_t elem_id    = "elem_1";

    /* Try to add valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                   elem_id,
                                                   expected,
                                                   sizeof(expected)));

    /* Try to get with too small buffer. */
    uint8_t  tested[sizeof(expected)] = { 0 };
    uint32_t read_size                = sizeof(expected) - 1;

    TEST_ASSERT_EQUAL(-COLL_ERR_NOMEM, collection_elem_get(&collection,
                                                           elem_id,
                                                           tested,
                                                           &read_size));

    /* Try to read file that does not exist. */
    TEST_ASSERT_EQUAL(-COLL_ERR_NOENT, collection_elem_get(&collection,
                                                           "dupa",
                                                           tested,
                                                           &read_size));

    /* Try to read file with valid size. */
    read_size = sizeof(expected);
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_get(&collection,
                                                   elem_id,
                                                   tested,
                                                   &read_size));

    /* Check if buffers match. */
    TEST_ASSERT_EQUAL_MEMORY(expected, tested, sizeof(expected));
}

TEST(collection_test, coll_elem_get_one_with_serializer)
{
    coll_t    collection = { .path = "/tst", .p_serializer = &serializer };
    tst_pet_t expected =
    {
        .buff = {0},
        .data = {
            ._Pet_name_tstr = {{.value = (const uint8_t*)"foo", .len = 3},
                     {.value = (const uint8_t*)"bar", .len = 3}},
            ._Pet_name_tstr_count = 2,
            ._Pet_birthday = {.value = (uint8_t[]){1,2,3,4,5,6,7,8}, .len = 8},
            ._Pet_species_choice = _Pet_species_dog,
        }
    };
    elem_id_t elem_id = "elem_1";

    /* Try to add valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                   elem_id,
                                                   &expected,
                                                   sizeof(expected)));

    /* Try to read file with valid size. */
    tst_pet_t tested    = { 0 };
    uint32_t  read_size = sizeof(expected);

    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_get(&collection,
                                                   elem_id,
                                                   &tested,
                                                   &read_size));

    /* Check if buffers match. */
    for(uint8_t idx = 0; idx < expected.data._Pet_name_tstr_count; idx++)
    {
        TEST_ASSERT_EQUAL_MEMORY(expected.data._Pet_name_tstr[idx].value,
                                 tested.data._Pet_name_tstr[idx].value,
                                 expected.data._Pet_name_tstr[idx].len);
    }

    TEST_ASSERT_EQUAL(expected.data._Pet_name_tstr_count,
                      tested.data._Pet_name_tstr_count);
    TEST_ASSERT_EQUAL_MEMORY(expected.data._Pet_birthday.value,
                             tested.data._Pet_birthday.value,
                             expected.data._Pet_birthday.len);
    TEST_ASSERT_EQUAL(expected.data._Pet_species_choice,
                      tested.data._Pet_species_choice);
}

TEST(collection_test, coll_elem_remove_null)
{
    TEST_ASSERT_EQUAL(-COLL_ERR_INVAL, collection_elem_remove(NULL, NULL));
}

TEST(collection_test, coll_elem_remove_one_without_serializer)
{
    coll_t    collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t   expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    elem_id_t elem_id    = "elem_1";

    /* Try to remove not existing file. */
    TEST_ASSERT_EQUAL(-COLL_ERR_NOENT,
                      collection_elem_remove(&collection, elem_id));

    /* Try to add valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                   elem_id,
                                                   expected,
                                                   sizeof(expected)));

    /* Remove valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_remove(&collection, elem_id));

    /* Try to get file previously removed. */
    uint8_t  tested[sizeof(expected)] = { 0 };
    uint32_t read_size                = sizeof(expected);

    /* Try to read file that does not exist. */
    TEST_ASSERT_EQUAL(-COLL_ERR_NOENT, collection_elem_get(&collection,
                                                           "dupa",
                                                           tested,
                                                           &read_size));
}

TEST(collection_test, coll_elem_cnt_get_null)
{
    TEST_ASSERT_EQUAL(-COLL_ERR_INVAL, collection_elem_cnt_get(NULL));
}

TEST(collection_test, coll_elem_cnt_get_multiple)
{
    coll_t  collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t content[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    char    suffix     = '1';
    char    elem_id[]  = "elem_0";

    TEST_ASSERT_EQUAL(0, collection_elem_cnt_get(&collection));

    /* Add multiple files and check element count in the collection. */
    for(uint32_t idx = 0; idx < COLL_FS_MOCK_MAX_NO_OF_FILES; idx++)
    {
        elem_id[5] = ++suffix;
        TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                       elem_id,
                                                       content,
                                                       sizeof(content)));
        TEST_ASSERT_EQUAL(idx + 1, collection_elem_cnt_get(&collection));
    }

    /* Remove multiple files and check element count in the collection. */
    int32_t elem_cnt = COLL_FS_MOCK_MAX_NO_OF_FILES;

    for(uint32_t idx = 0; idx < COLL_FS_MOCK_MAX_NO_OF_FILES; idx++)
    {
        TEST_ASSERT_EQUAL(COLL_OK, collection_elem_remove(&collection,
                                                          elem_id));
        elem_id[5] = --suffix;
        TEST_ASSERT_EQUAL(--elem_cnt, collection_elem_cnt_get(&collection));
    }
}

TEST(collection_test, coll_elem_path_get_null)
{
    TEST_ASSERT_EQUAL(-COLL_ERR_INVAL,
                      collection_elem_path_get(NULL, NULL, NULL));
}

TEST(collection_test, coll_elem_path_get)
{
    coll_t     collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t    content[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    elem_id_t  elem_id    = "elem_1";
    const char *expected  = "/tst/elem_1";
    char       tested[16] = { 0 };

    /* Try to add valid file. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                   elem_id,
                                                   content,
                                                   sizeof(content)));

    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_path_get(&collection,
                                                        elem_id,
                                                        tested));

    /* Check if buffers match. */
    TEST_ASSERT_EQUAL_MEMORY(expected, tested, strlen(expected));
}

TEST(collection_test, coll_elem_list_get_null)
{
    TEST_ASSERT_EQUAL(-COLL_ERR_INVAL, collection_elem_list_get(NULL, NULL));
}

TEST(collection_test, coll_elem_list_get)
{
    coll_t  collection = { .path = "/tst", .p_serializer = NULL };
    uint8_t content[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    char    suffix     = '1';
    char    elem_id[]  = "elem_0";

    /* Add multiple files and check element count in the collection. */
    for(uint32_t idx = 0; idx < COLL_FS_MOCK_MAX_NO_OF_FILES; idx++)
    {
        elem_id[5] = ++suffix;
        TEST_ASSERT_EQUAL(COLL_OK, collection_elem_add(&collection,
                                                       elem_id,
                                                       content,
                                                       sizeof(content)));
        TEST_ASSERT_EQUAL(idx + 1, collection_elem_cnt_get(&collection));
    }

    elem_list_t list = collection_elem_list_create();

    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_list_get(&collection, list));

    /* Get first node from the list. */
    coll_node_t *node = NULL;

    node = collection_elem_list_peek_head(list);
    TEST_ASSERT_NOT_EQUAL(NULL, node);

    /* Check all file names in the list.*/
    elem_id[5] = '0';
    suffix     = '1';

    for( ;
         node->next != NULL;
         node = collection_elem_list_peek_next((void *)node))
    {
        /* Check if buffers match. */
        elem_id[5] = ++suffix;
        TEST_ASSERT_EQUAL_MEMORY(elem_id, node->f_name, sizeof(elem_id));
    }

    /* Free the list. */
    TEST_ASSERT_EQUAL(COLL_OK, collection_elem_list_free(list));
}

TEST_GROUP_RUNNER(collection_test)
{
    RUN_TEST_CASE(collection_test, coll_elem_add_null);
    RUN_TEST_CASE(collection_test, coll_elem_add_one_without_serializer);
    RUN_TEST_CASE(collection_test, coll_elem_add_one_with_serializer);
    RUN_TEST_CASE(collection_test,
                  coll_elem_add_too_much_files_without_serializer);

    RUN_TEST_CASE(collection_test, coll_elem_get_null);
    RUN_TEST_CASE(collection_test, coll_elem_get_one_with_serializer);
    RUN_TEST_CASE(collection_test, coll_elem_get_one_without_serializer);

    RUN_TEST_CASE(collection_test, coll_elem_remove_null);
    RUN_TEST_CASE(collection_test, coll_elem_remove_one_without_serializer);

    RUN_TEST_CASE(collection_test, coll_elem_cnt_get_null);
    RUN_TEST_CASE(collection_test, coll_elem_cnt_get_multiple);

    RUN_TEST_CASE(collection_test, coll_elem_path_get_null);
    RUN_TEST_CASE(collection_test, coll_elem_path_get);

    RUN_TEST_CASE(collection_test, coll_elem_list_get_null);
    RUN_TEST_CASE(collection_test, coll_elem_list_get);
}
