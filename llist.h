#if !defined (_llist_h_)
# define _llist_h_ 1
#
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
#
# if !defined DAAPI
#  define DAAPI extern
# endif /* DAAPI */

typedef struct s_lnode *t_llist;

struct s_lnode {
    void *l_dat;

    struct s_lnode *l_nxt;
};

DAAPI t_llist da_llistnew(void *);

DAAPI t_llist da_llistat(t_llist, size_t);

DAAPI t_llist da_llistlast(t_llist);

DAAPI int da_llistpushf(t_llist *, struct s_lnode *);

DAAPI int da_llistpushb(t_llist *, struct s_lnode *);

DAAPI int da_llistdelone(t_llist *, void (*)(void *));

DAAPI int da_llistclear(t_llist *, void (*)(void *));

DAAPI size_t da_llistsize(t_llist);

# if defined (LLIST_IMPLEMENTATION)

DAAPI t_llist da_llistnew(void *data) {
    t_llist list = malloc(sizeof(struct s_lnode));
    if (!list) {
        return (0);
    }

    list->l_dat = data;
    list->l_nxt = 0;
    return (list);
}

DAAPI t_llist da_llistat(t_llist list, size_t index) {
    if (!list) { return (0); }

    for (size_t i = 0; i < index; i++) {
        list = list->l_nxt;

        /* break if end-of-list reached... */
        if (!list) {
            break;
        }
    }

    return (list);
}

DAAPI t_llist da_llistlast(t_llist list) {
    if (!list) { return (0); }

    while (list->l_nxt) {
        list = list->l_nxt;
    }

    return (list);
}

DAAPI int da_llistpushf(t_llist *list, struct s_lnode *node) {
    node->l_nxt = *list;
    *list = node;

    return (1);
}

DAAPI int da_llistpushb(t_llist *list, struct s_lnode *node) {
    if (!list || !*list) {
        *list = node;
    }
    else {
        t_llist last = da_llistlast(*list);
        if (!last) {
            return (0);
        }

        last->l_nxt = node;
    }
    return (1);
}

DAAPI int da_llistdelone(t_llist *list, void (*f)(void *)) {
    if (!list || !*list) { return (0); }

    f((*list)->l_dat);
    free(*list);
    return (1);
}

DAAPI int da_llistclear(t_llist *list, void (*f)(void *)) {
    if (!list || !*list) { return (0); }

    t_llist cursor = *list;
    while (*list) {
        *list = (*list)->l_nxt;
        da_llistdelone(&cursor, f);
        cursor = *list;
    }
    return (1);
}

DAAPI size_t da_llistsize(t_llist list) {
    if (!list) { return (0); }
    
    size_t i;
    for (i = 1; list->l_nxt; i++) {
        list = list->l_nxt;
    }

    return (i);
}

# endif /* LLIST_IMPLEMENTATION */
#endif /* _llist_h_ */
