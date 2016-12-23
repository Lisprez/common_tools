#include <Windows.h>
constexpr int MD5LEN = 16
constexpr int BUFSIZE = 1024
std::tuple<bool, std::string> supervisor::util::GetFileMD5(const std::string& filePath)
{
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HANDLE hFile = NULL;
	BYTE rgbFile[BUFSIZE];
	DWORD cbRead = 0;
	BYTE rgbHash[MD5LEN];
	DWORD cbHash = 0;
	CHAR rgbDigits[] = "0123456789abcdef";

	hFile = CreateFileA(filePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwStatus = GetLastError();
		std::cout << "[----ERROR----] Open file" << filePath << "with error code " << dwStatus << "for calcu md5" << std::endl;
		return std::make_tuple(false, std::string({}));
	}

	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError();
		std::cout << "[----ERROR----] CryptAcquireContext failed: " << dwStatus << std::endl;
		CloseHandle(hFile);
		return std::make_tuple(false, std::string({}));
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError();
		std::cout << "[----ERROR----]CryptAcquireContext failed: " << dwStatus << std::endl;
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return std::make_tuple(false, std::string({}));
	}

	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
		&cbRead, NULL))
	{
		if (0 == cbRead)
		{
			break;
		}

		if (!CryptHashData(hHash, rgbFile, cbRead, 0))
		{
			dwStatus = GetLastError();
			std::cout << "[----ERROR----] CryptHashData failed: " << dwStatus << std::endl;
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hFile);
			return std::make_tuple(false, std::string({}));
		}
	}

	if (!bResult)
	{
		dwStatus = GetLastError();
		std::cout << "[----ERROR----] ReadFile failed: %d\n" << dwStatus << std::endl;
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return std::make_tuple(false, std::string({}));
	}

	cbHash = MD5LEN;
	char md5value[32] = {};
	std::string md5({});
	bool final = false;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		for (DWORD i = 0; i < cbHash; i++)
		{
			md5value[i * 2] = rgbDigits[rgbHash[i] >> 4];
			md5value[i * 2 + 1] = rgbDigits[rgbHash[i] & 0xf];
		}
		md5 = std::string(md5value, 0, 32);
		final = true;
	}
	else
	{
		dwStatus = GetLastError();
		std::cout << "[----ERROR----] CryptGetHashParam failed: " << dwStatus << std::endl;
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);

	return std::make_tuple(final, md5);
}
