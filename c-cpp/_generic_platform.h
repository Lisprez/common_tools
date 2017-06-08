#pragma once


//---------------------------------------------------------------------
// Utility for automatically setting up the pointer-sized integer type
//---------------------------------------------------------------------

template<typename T32BITS, typename T64BITS, int PointerSize>
struct SelectIntPointerType
{
	// nothing here are is it an error if the partial specializations fail
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType<T32BITS, T64BITS, 8>
{
	typedef T64BITS TIntPointer; // select the 64 bit type
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType<T32BITS, T64BITS, 4>
{
	typedef T32BITS TIntPointer; // select the 64 bit type
};

/**
 * Generic types for almost all compilers and platforms
 */
struct GenericPlatformTypes
{
	// Unsigned base types.
	typedef unsigned char 		uint8;		// 8-bit  unsigned.
	typedef unsigned short int	uint16;		// 16-bit unsigned.
	typedef unsigned int		uint32;		// 32-bit unsigned.
	typedef unsigned long long	uint64;		// 64-bit unsigned.

	// Signed base types.
	typedef	signed char			int8;		// 8-bit  signed.
	typedef signed short int	int16;		// 16-bit signed.
	typedef signed int	 		int32;		// 32-bit signed.
	typedef signed long long	int64;		// 64-bit signed.

	// Character types.
	typedef char				ANSICHAR;	// An ANSI character       -                  8-bit fixed-width representation of 7-bit characters.
	typedef wchar_t				WIDECHAR;	// A wide character        - In-memory only.  ?-bit fixed-width representation of the platform's natural wide character set.  Could be different sizes on different platforms.
	typedef uint8				CHAR8;		// An 8-bit character type - In-memory only.  8-bit representation.  Should really be char8_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
	typedef uint16				CHAR16;		// A 16-bit character type - In-memory only.  16-bit representation.  Should really be char16_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
	typedef uint32				CHAR32;		// A 32-bit character type - In-memory only.  32-bit representation.  Should really be char32_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
	typedef WIDECHAR			TCHAR;		// A switchable character  - In-memory only.  Either ANSICHAR or WIDECHAR, depending on a licensee's requirements.

	typedef SelectIntPointerType<uint32, uint64, sizeof(void*)>::TIntPointer UPTRINT;	// unsigned int the same size as a pointer
	typedef SelectIntPointerType<int32, int64, sizeof(void*)>::TIntPointer PTRINT;		// signed int the same size as a pointer
	typedef UPTRINT SIZE_T;																// unsigned int the same size as a pointer
	typedef PTRINT SSIZE_T;																// unsigned int the same size as a pointer

	typedef int32					TYPE_OF_NULL;
	typedef decltype(nullptr)		TYPE_OF_NULLPTR;
};

//------------------------------------------------------------------
// Transfer the platform types to global types
//------------------------------------------------------------------

// Unsigned base types.
typedef GenericPlatformTypes::uint8			uint8;		///< An 8-bit unsigned integer.
typedef GenericPlatformTypes::uint16		uint16;		///< A 16-bit unsigned integer.
typedef GenericPlatformTypes::uint32		uint32;		///< A 32-bit unsigned integer.
typedef GenericPlatformTypes::uint64		uint64;		///< A 64-bit unsigned integer.

// Signed base types.
typedef	GenericPlatformTypes::int8			int8;		///< An 8-bit signed integer.
typedef GenericPlatformTypes::int16			int16;		///< A 16-bit signed integer.
typedef GenericPlatformTypes::int32			int32;		///< A 32-bit signed integer.
typedef GenericPlatformTypes::int64			int64;		///< A 64-bit signed integer.

// Character types.
typedef GenericPlatformTypes::ANSICHAR		ANSICHAR;	///< An ANSI character. Normally a signed type.
typedef GenericPlatformTypes::WIDECHAR		WIDECHAR;	///< A wide character. Normally a signed type.
typedef GenericPlatformTypes::TCHAR			TCHAR;		///< Either ANSICHAR or WIDECHAR, depending on whether the platform supports wide characters or the requirements of the licensee.
typedef GenericPlatformTypes::CHAR8			UTF8CHAR;	///< An 8-bit character containing a UTF8 (Unicode, 8-bit, variable-width) code unit.
typedef GenericPlatformTypes::CHAR16		UCS2CHAR;	///< A 16-bit character containing a UCS2 (Unicode, 16-bit, fixed-width) code unit, used for compatibility with 'Windows TCHAR' across multiple platforms.
typedef GenericPlatformTypes::CHAR16		UTF16CHAR;	///< A 16-bit character containing a UTF16 (Unicode, 16-bit, variable-width) code unit.
typedef GenericPlatformTypes::CHAR32		UTF32CHAR;	///< A 32-bit character containing a UTF32 (Unicode, 32-bit, fixed-width) code unit.

typedef GenericPlatformTypes::UPTRINT		UPTRINT;		///< An unsigned integer the same size as a pointer
typedef GenericPlatformTypes::PTRINT		PTRINT;			///< A signed integer the same size as a pointer
typedef GenericPlatformTypes::SIZE_T		SIZE_T;			///< An unsigned integer the same size as a pointer, the same as UPTRINT
typedef GenericPlatformTypes::SSIZE_T		SSIZE_T;		///< An integer the same size as a pointer, the same as PTRINT

typedef GenericPlatformTypes::TYPE_OF_NULL		TYPE_OF_NULL;		///< The type of the NULL constant.
typedef GenericPlatformTypes::TYPE_OF_NULLPTR	TYPE_OF_NULLPTR;	///< The type of the C++ nullptr keyword.

