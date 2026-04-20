#if !defined (_btree_h_)
# define _btree_h_ 1
#
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
#
# if !defined DAAPI
#  define DAAPI extern
# endif /* DAAPI */

typedef struct s_bnode *t_btree;

struct s_bnode {
    void *b_data;

    struct s_bnode *b_left;
    struct s_bnode *b_right;
};

DAAPI t_btree da_btreenew(void *);

DAAPI int da_btreeclear(t_btree *, void (*)(void *));

# if defined (BTREE_IMPLEMENTATION)

DAAPI t_btree da_btreenew(void *data) {
    t_btree tree = malloc(sizeof(struct s_bnode));
    if (!tree) {
        return (0);
    }

    tree->b_data  = data;
    tree->b_left  = 0;
    tree->b_right = 0;
    return (tree);
}

DAAPI int da_btreeclear(t_btree *tree, void (*f)(void *)) {
    if (!tree || !*tree) { return (0); }

    /* recursive 'left' leave cleanup... */
    da_btreeclear(&(*tree)->b_left, f);
    /* recursive 'right' leave cleanup... */
    da_btreeclear(&(*tree)->b_right, f);

    f((*tree)->b_data);
    free(*tree);
    return (1);
}

# endif /* BTREE_IMPLEMENTATION */
#endif /* _btree_h_ */
