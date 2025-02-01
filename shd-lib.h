#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    size_t len;
    char content[];
} page_t;

typedef struct {
    size_t len;
    page_t **pages;
} notebook_t;

#define MAX_PAGES 0x100

/**
 * @param len The number of pages in the notebook. Must be less than MAX_PAGES
 *
 * @return A pointer to the newly created notebook if successful, or NULL
 */
notebook_t *create_notebook(size_t len);

/**
 * @param nb The notebook to destroy
 */
void destroy_notebook(notebook_t *nb);

/**
 * @param nb Notebook object
 * @param page_nr The page # to read
 *
 * @return A pointer to the page's content if valid, else NULL
 *         A non-existent page is considered a failure case.
 */
char *read_page(notebook_t *nb, int page_nr);

/**
 * @param nb Notebook object
 * @param page_nr The page # to write to
 * @param msg The message to write
 *
 * @return 0 on success, -1 otherwise. 
 *         If a page_nr already exists, replace it with this new msg.
 */
int write_page(notebook_t *nb, int page_nr, const char *msg);

/**
 * @param nb Notebook object
 * @param page_nr The page to grow
 * @param msg The amount to grow the page by in bytes
 *
 * @return 0 on success, -1 otherwise
 *         A non-existent page is considered a failure case.
 *         A new size greater than the maximum unsigned 64-bit value is a failure case.
 */
int grow_page(notebook_t *nb, int page_nr, size_t amount);

/**
 * @param nb Notebook object
 * @param page_nr The page to delete
 *
 * @return 0 on success, -1 otherwise
 *         A non-existent page is considered a failure case.
 */
int delete_page(notebook_t *nb, int page_nr);

/**
 * @param nb Notebook object
 * @param page_nr The page to append to
 * @param msg The message to append
 *
 * @return 0 on success, -1 otherwise
 *         A non-existent page is considered a failure case.
 */
int append_page(notebook_t *nb, int page_nr, const char *msg);