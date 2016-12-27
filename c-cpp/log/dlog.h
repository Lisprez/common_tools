#define dlog_(var) do {\
	std::cerr << #var##": " << var << std::endl;\
} while (0)

#define dlogf_(format, ...) fprintf(stderr, format, __VA_ARGS__)

#define debug2output_(format, ...) do {\
	char strBuffer[4096] = {0};\
	sprintf_s(strBuffer, format, __VA_ARGS__);\
	OutputDebugString(strBuffer);\
} while (0)

#define error_(format, ...) do {\
	fprintf(stderr, format, __VA_ARGS__)\
} while (0)

// All this is for debug
#ifdef _DEBUG
#define DLOG dlog_
#define DLOGF dlogf_
#define DLOG2OUTPUT debug2output_
#else
#define DLOG
#define DLOGF
#define DLOG2OUTPUT
#endif

// This below is for log info
#define ERROR error_
