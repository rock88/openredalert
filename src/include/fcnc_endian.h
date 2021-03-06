// mode: -*- C++ -*-
/*****************************************************************************
 * fcnc_endian.h - Includes macro definitions to convert bytes to correct
 * endianess
 *       Author: Kareem Dana
 ****************************************************************************/
#ifndef FCNC_ENDIAN_H
#define FCNC_ENDIAN_H

#include <cstdint>

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef HAVE_SYS_ENDIAN_H
# include <sys/endian.h>
#elif HAVE_ENDIAN_H
# include <endian.h>
#else /* ! HAVE_SYS_ENDIAN_H */

# ifdef HAVE_BYTESWAP_H
#  include <byteswap.h>
#  define bswap16(x)  (bswap_16((x)))
#  define bswap32(x)  (bswap_32((x)))
#  define bswap64(x)  (bswap_64((x)))
# else /* ! HAVE_BYTESWAP_H */
#  define bswap16(x)  \
       ((((x) & 0x00ff) << 8) |  \
        (((x) & 0xff00) >> 8))
#  define bswap32(x)  \
((((x) & 0x000000ff) << 24) |  \
(((x) & 0x0000ff00) <<  8) |  \
(((x) & 0x00ff0000) >>  8) |  \
(((x) & 0xff000000) >> 24))
#  define bswap64(x)  \
((((x) & 0x00000000000000ffull) << 56) |  \
(((x) & 0x000000000000ff00ull) << 40) |  \
(((x) & 0x0000000000ff0000ull) << 24) |  \
(((x) & 0x00000000ff000000ull) <<  8) |  \
(((x) & 0x000000ff00000000ull) >>  8) |  \
(((x) & 0x0000ff0000000000ull) >> 24) |  \
(((x) & 0x00ff000000000000ull) >> 40) |  \
(((x) & 0xff00000000000000ull) >> 56))
# endif /* HAVE_BYTESWAP_H */

# ifdef WORDS_BIGENDIAN
#  define be16toh(x)  (x)
#  define be32toh(x)  (x)
#  define be64toh(x)  (x)
#  define le16toh(x)  bswap16((uint16_t)(x))
#  define le32toh(x)  bswap32((uint32_t)(x))
#  define le64toh(x)  bswap64((uint64_t)(x))
# else /* ! WORDS_BIGENDIAN */
#  define be16toh(x)  bswap16((uint16_t)(x))
#  define be32toh(x)  bswap32((uint32_t)(x))
#  define be64toh(x)  bswap64((uint64_t)(x))
#  define le16toh(x)  (x)
#  define le32toh(x)  (x)
#  define le64toh(x)  (x)
# endif /* WORDS_BIGENDIAN */

# define htobe16(x)  be16toh(x)
# define htobe32(x)  be32toh(x)
# define htobe64(x)  be64toh(x)
# define htole16(x)  le16toh(x)
# define htole32(x)  le32toh(x)
# define htole64(x)  le32toh(x)

#endif /* HAVE_SYS_ENDIAN_H */

#endif /* FCNC_ENDIAN_H */
