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
    void *data;

    struct s_bnode *left;
    struct s_bnode *right;
};

DAAPI t_btree da_btreenew(void *);

DAAPI int da_btreeclear(t_btree *, void (*)(void *));

# if defined (BTREE_IMPLEMENTATION)

DAAPI t_btree da_btreenew(void *data) {
    t_btree tree = malloc(sizeof(struct s_bnode));
    if (!tree) {
        return (0);
    }

    tree->data  = data;
    tree->left  = 0;
    tree->right = 0;
    return (tree);
}

DAAPI int da_btreeclear(t_btree *tree, void (*f)(void *)) {
    if (!tree || !*tree) { return (0); }

    /* recursive 'left' leave cleanup... */
    da_btreeclear(&(*tree)->left, f);
    /* recursive 'right' leave cleanup... */
    da_btreeclear(&(*tree)->right, f);

    f((*tree)->data);
    free(*tree);
    return (1);
}

# endif /* BTREE_IMPLEMENTATION */
#endif /* _btree_h_ */
