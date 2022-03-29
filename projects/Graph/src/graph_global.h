#ifndef GRAPH_GLOBAL_H
#define GRAPH_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GRAPH_LIB)
#  define GRAPH_EXPORT Q_DECL_EXPORT
# else
#  define GRAPH_EXPORT Q_DECL_IMPORT
# endif
#else
# define GRAPH_EXPORT
#endif

#endif // GRAPH_GLOBAL_H