#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_da_h_)
# define _da_h_ 1
#
# /* fall-back to C++ */
# if defined (__cplusplus)
#  include "da.hpp"
# else
#  include "llist.h"
#  include "dllist.h"
# endif /* __cplusplus */
#endif /* _da_h_ */
