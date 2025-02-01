#include "shd-lib.h"
notebook_t *create_notebook(size_t len) {
    if (len > MAX_PAGES)
        return NULL;
    notebook_t *nb = malloc(sizeof(notebook_t));
    if (len > 0) {
        nb->len = len;
        nb->pages = malloc(sizeof(*nb->pages) * len);
        for (size_t i = 0; i < len; i++) {
            nb->pages[i] = NULL;
        }
    }
    return nb;
}

void destroy_notebook(notebook_t *nb) {
    for (size_t i = 0; i < nb->len; i++) {
        free(nb->pages[i]);
    }
    free(nb->pages);
    free(nb);
}

char *read_page(notebook_t *nb, int page_nr) {
    return nb->pages[page_nr]->content;
}

int write_page(notebook_t *nb, int page_nr, const char *msg) {
    size_t len = strlen(msg);
    page_t *page = malloc(sizeof(page_t) + len);
    page->len = len;
    strcpy(page->content, msg);
    nb->pages[page_nr] = page;
    return 0;
}

int grow_page(notebook_t *nb, int page_nr, size_t amount) {
    size_t orig_len = nb->pages[page_nr]->len;
    size_t new_len = orig_len + amount;
    nb->pages[page_nr] = realloc(nb->pages[page_nr], new_len);
    nb->pages[page_nr]->len = new_len;
    return 0;
}

int delete_page(notebook_t *nb, int page_nr) {
    free(nb->pages[page_nr]);
    return 0;
}

int append_page(notebook_t *nb, int page_nr, const char *msg) {
    page_t *page = nb->pages[page_nr];
    size_t len = strlen(msg);
    size_t orig_len = strlen(page->content);
    if (len < page->len - orig_len - 2) {
        strcpy(page->content + orig_len, msg);    
    }
    return 0;
}

