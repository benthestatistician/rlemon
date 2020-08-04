#define LEMON_VERSION "1.3.1"

#undef LEMON_HAVE_LP
#undef LEMON_HAVE_MIP
#undef LEMON_HAVE_GLPK
#undef LEMON_HAVE_CPLEX
#undef LEMON_HAVE_SOPLEX
#undef LEMON_HAVE_CLP
#undef LEMON_HAVE_CBC

#define _LEMON_CPLEX 1
#define _LEMON_CLP 2
#define _LEMON_GLPK 3
#define _LEMON_SOPLEX 4
#define _LEMON_CBC 5

#define LEMON_DEFAULT_LP _LEMON_GLPK
#define LEMON_DEFAULT_MIP _LEMON_GLPK

/* further macros to be specified platform-dependent:
   LEMON_HAVE_LONG_LONG
   LEMON_USE_PTHREAD
   LEMON_CXX11
   LEMON_WIN32
   LEMON_USE_WIN32_THREADS
 */