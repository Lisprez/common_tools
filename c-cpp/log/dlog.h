#define dlog_(var) do {\
	std::cerr << #var##": " << var << std::endl;\
} while (0)

#define dlogf_(format, ...) fprintf(stderr, format, __VA_ARGS__)

#define debug2output_(format, ...) do {\
	char strBuffer[4096] = {0};\
	sprintf_s(strBuffer, format, __VA_ARGS__);\
	OutputDebugString(strBuffer);\
} while (0)

#ifdef _DEBUG
#define dlog dlog_
#define dlogf dlogf_
#define debug2output debug2output_
#else
#define dlog
#define dlogf
#define debug2output
#endif

