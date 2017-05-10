#ifndef _ENV_H_
#define _ENV_H_

#if _WIN32 || _WIN64
#if _WIN64
#define ENV_64BIT
#else
#define ENV_32BIT
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV_64BIT
#else
#define ENV_32BIT
#endif
#endif

#endif
