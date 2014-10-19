#include <QtCore/QtGlobal>

#if defined(KCLLIB_LIBRARY)
#  define KCLIB_EXPORT Q_DECL_EXPORT
#else
#  define KCLIB_EXPORT Q_DECL_IMPORT
#endif