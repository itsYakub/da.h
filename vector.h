#if !defined (_vector_h_)
# define _vector_h_ 1
#
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
#
# if !defined DAAPI
#  define DAAPI extern
# endif /* DAAPI */

typedef struct s_vechdr t_vechdr;

struct s_vechdr {
    size_t v_len;
    size_t v_cap;
};

# if !defined (da_vecpushback)
#  define DA_VEC_DEF_CAP 8
#  define da_vecpushback(arr, value)                                                     \
    do {                                                                                 \
        /* allocate new 'arr' if needed... */                                            \
        if (!arr) {                                                                      \
            /* create new vector header... */                                            \
            t_vechdr *hdr = malloc(DA_VEC_DEF_CAP * sizeof(*arr) + sizeof(t_vechdr));    \
            if (!hdr) { break; }                                                         \
                                                                                         \
            hdr->v_len = 0;                                                              \
            hdr->v_cap = DA_VEC_DEF_CAP;                                                 \
                                                                                         \
            /* assign 'arr' to header's data section... */                               \
            arr = (void *) (hdr + 1);                                                    \
        }                                                                                \
                                                                                         \
        /* get the header from 'arr'... */                                               \
        t_vechdr *hdr = (t_vechdr *) arr - 1;                                            \
                                                                                         \
        /* resize vector if length exceeds the capacity... */                            \
        while (hdr->v_len >= hdr->v_cap) {                                               \
            size_t cap = hdr->v_cap + hdr->v_cap / 2;                                    \
            t_vechdr *tmp = realloc(hdr, cap * sizeof(*arr) + sizeof(t_vechdr));         \
            if (!tmp) { break; }                                                         \
                                                                                         \
            hdr = tmp;                                                                   \
            hdr->v_cap = cap;                                                            \
                                                                                         \
            /* 'arr' is now invalid, reassign it... */                                   \
            (arr) = (void *) (hdr + 1);                                                  \
        }                                                                                \
                                                                                         \
        (arr)[hdr->v_len++] = (value);                                                   \
    } while (0)
# endif /* da_vecpushback */
#
# if !defined (da_vecfree)
#  define da_vecfree(arr)                                                                \
    do {                                                                                 \
        if (!arr) { break; }                                                             \
                                                                                         \
        t_vechdr *hdr = (t_vechdr *) arr - 1;                                            \
        hdr->v_len = 0;                                                                  \
        hdr->v_cap = 0;                                                                  \
        free(hdr);                                                                       \
        hdr = 0;                                                                         \
    } while (0)
# endif /* da_vecfree */
#
# if !defined (da_veclength)
#  define da_veclength(arr)                                                              \
    ((t_vechdr *) (arr) - 1)->v_len
# endif /* da_veclength */
#
# if !defined (da_veccapacity)
#  define da_veccapacity(arr)                                                            \
    ((t_vechdr *) (arr) - 1)->v_cap
# endif /* da_veccapacity */
#
#endif /* _vector_h_ */
