#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_da_h_)
# define _da_h_ 1
#
# if defined DA_IMPLEMENTATION
#  define LLIST_IMPLEMENTATION
#  define BTREE_IMPLEMENTATION
# endif /* DA_IMPLEMENTATION */
#
# include "llist.h"
# include "btree.h"
# include "vector.h"
#
#endif /* _da_h_ */
