
#if 0
	#define WINDOWS
#endif

#if 0
	#define APPLE
#endif

#if 1
	#define LINUX
#endif

#if 0
	#define BSD
#endif

#if 0
	#define HAIKU
#endif

#if 0
	#define STEAMWORKS
#endif

#if 0
	#define USE_EOS
	#define BUILD_ENV_PR ""
	#define BUILD_ENV_SA ""
	#define BUILD_ENV_DE ""
	#define BUILD_ENV_CC ""
	#define BUILD_ENV_CS ""
	#define BUILD_ENV_GSE ""
#endif

#if 0
	#define USE_FMOD
#endif

#if 1
	#define USE_OPENAL
#endif

#if 0
	#define USE_TREMOR
#endif

#if 0
	#define PANDORA
#endif

#if 1
	/*
	 * https://msdn.microsoft.com/en-us/library/cc230318.aspx
	 * A DWORD is a 32-bit unsigned integer (range: 0 through 4294967295 decimal). Because a DWORD is unsigned, its first bit (Most Significant Bit (MSB)) is not reserved for signing. 
	 * This type is declared as follows:
	 * typedef unsigned long DWORD, *PDWORD, *LPDWORD;
	 */
	typedef unsigned long DWORD;
#endif
