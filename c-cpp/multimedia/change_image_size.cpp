static std::map<std::wstring, std::wstring> MimeTypeMap{
	{ L".jpeg",	L"image/jpeg" },
	{ L".jpe",	L"image/jpeg" },
	{ L".jpg",	L"image/jpeg" },
	{ L".png",	L"image/png" },
	{ L".gif",	L"image/gif" },
	{ L".tiff",	L"image/tiff" },
	{ L".tif",	L"image/tiff" },
	{ L".bmp",	L"image/bmp" }
};


Gdiplus::Bitmap* ResizeClone(Gdiplus::Bitmap* bmp, int width, int height)
{
	UINT image_height = bmp->GetHeight();
	UINT image_width = bmp->GetWidth();
	UINT target_height = 0;
	UINT target_width = 0;

	double ratio = static_cast<double>(image_height) / static_cast<double>(image_width);
	if (image_height > image_width)
	{
		target_height = 1024;
		target_width = static_cast<UINT>(static_cast<double>(1024) / ratio);
	}
	else
	{
		target_width = 1024;
		target_height = static_cast<UINT>(static_cast<double>(target_width) * ratio);
	}
	Gdiplus::Bitmap* new_bmp = new Gdiplus::Bitmap(target_width, target_height, bmp->GetPixelFormat());
	Gdiplus::Graphics graphics(new_bmp);
	graphics.DrawImage(bmp, 0, 0, target_width, target_height);

	return new_bmp;
}

int GetGdiplusEncoder(const std::wstring& form, CLSID* clsid)
{
	UINT num;
	UINT size;
	Gdiplus::ImageCodecInfo* imageCodecInfo = nullptr;
	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1;
	}
	imageCodecInfo = static_cast<Gdiplus::ImageCodecInfo*>(malloc(size));
	if (imageCodecInfo == nullptr)
	{
		return -1;
	}
	Gdiplus::GetImageEncoders(num, size, imageCodecInfo);

	for (auto i = 0; i < num; i++)
	{
		if (wcscmp(imageCodecInfo[i].MimeType, form.c_str()) == 0)
		{
			*clsid = imageCodecInfo[i].Clsid;
			return i;
		}
	}
	free(imageCodecInfo);

	return -1;
}

int convert_image(const std::string& source_file_path, const std::string& target_file_path)
{
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	std::wstring image_file_name;
	image_file_name.assign(source_file_path.begin(), source_file_path.end());
	std::wstring target_image_file_name;
	target_image_file_name.assign(target_file_path.begin(), target_file_path.end());
	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(image_file_name.c_str());
	if (bmp->GetHeight() <= 1024 && bmp->GetWidth() <= 1024)
	{
		LOG(INFO) << "Image is small not to process.";
		if (CopyFileA(source_file_path.c_str(), target_file_path.c_str(), FALSE) == 0)
		{
			LOG(INFO) << "Copy the source image error!";
			delete bmp;
			Gdiplus::GdiplusShutdown(gdiplusToken);
			return -1;
		}
		delete bmp;
		Gdiplus::GdiplusShutdown(gdiplusToken);

		return 0;
	}
	Gdiplus::Bitmap* resized_bmp = ResizeClone(bmp, 0, 0);
	LPWSTR ext = PathFindExtensionW(image_file_name.c_str());
	std::wstring form = MimeTypeMap[ext];
	CLSID encId;
	if (GetGdiplusEncoder(form, &encId) > -1)
	{
		resized_bmp->Save(target_image_file_name.c_str(), &encId, nullptr);
	}
	else
	{
		return -1;
	}

	delete bmp;
	delete resized_bmp;
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return 0;
}
