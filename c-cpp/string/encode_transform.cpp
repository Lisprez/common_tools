#include "encode_transform.h"

#include <Windows.h>

std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

std::string WStringToMBytes(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen;
	// wide char to multi char
	iTextLen = ::WideCharToMultiByte(CP_ACP, 0, lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, lpwcszWString, 0, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

std::wstring UTF8ToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset((void*)pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wstrReturn(pUnicode);
	delete[] pUnicode;
	return wstrReturn;
}

std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}


////下面是第二个C++中文字符串处理的代码片段
#include <cstddef>
#include <clocale>
#include <cstdlib>
#include <Windows.h>

wchar_t * MBs2WCs(const char* pszSrc) 
{
	wchar_t* pwcs = NULL;
	int size = 0;
#ifdef _linux_
	setlocale(LC_ALL, "zh_CN.GB2312");
	size = mbstowcs(NULL, pszSrc, 0);
	pwcs = new wchar_t[size + 1];
	size = mbstowcs(pwcs, pszSrc, size + 1);
	pwcs[size] = 0;
#else
	size = MultiByteToWideChar(20936, 0, pszSrc, -1, 0, 0);
	if (size <= 0)
		return NULL;
	pwcs = new wchar_t[size];
	MultiByteToWideChar(20936, 0, pszSrc, -1, pwcs, size);
#endif 
	return pwcs;
}

char* WCs2MBs(const wchar_t * wcharStr) 
{
	char* str = NULL;
	int size = 0;
#ifdef _linux_
	setlocale(LC_ALL, "zh_CN.UTF8");
	size = wcstombs(NULL, wcharStr, 0);
	str = new char[size + 1];
	wcstombs(str, wcharStr, size);
	str[size] = '\0';
#else
	size = WideCharToMultiByte(CP_UTF8, 0, wcharStr, -1, NULL, NULL, NULL, NULL);
	str = new char[size];
	WideCharToMultiByte(CP_UTF8, 0, wcharStr, -1, str, size, NULL, NULL);
#endif 
	return str;
}
