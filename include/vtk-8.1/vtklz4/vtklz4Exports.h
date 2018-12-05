
#ifndef VTKLZ4_EXPORT_H
#define VTKLZ4_EXPORT_H

#ifdef VTKLZ4_STATIC_DEFINE
#  define VTKLZ4_EXPORT
#  define VTKLZ4_NO_EXPORT
#else
#  ifndef VTKLZ4_EXPORT
#    ifdef vtklz4_EXPORTS
        /* We are building this library */
#      define VTKLZ4_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKLZ4_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKLZ4_NO_EXPORT
#    define VTKLZ4_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKLZ4_DEPRECATED
#  define VTKLZ4_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VTKLZ4_DEPRECATED_EXPORT
#  define VTKLZ4_DEPRECATED_EXPORT VTKLZ4_EXPORT VTKLZ4_DEPRECATED
#endif

#ifndef VTKLZ4_DEPRECATED_NO_EXPORT
#  define VTKLZ4_DEPRECATED_NO_EXPORT VTKLZ4_NO_EXPORT VTKLZ4_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKLZ4_NO_DEPRECATED
#    define VTKLZ4_NO_DEPRECATED
#  endif
#endif

#endif
