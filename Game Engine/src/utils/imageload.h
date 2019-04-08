#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <FreeImage.h>

namespace sge { 

	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height){
		FreeImage_Initialise();
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);

		if(fif==FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if(fif==FIF_UNKNOWN){
			std::cout << "Cannot find the file!" << std::endl; 
			return nullptr;
		}
		if(FreeImage_FIFSupportsReading(fif)){
			dib = FreeImage_Load(fif, filename);
		}
		if(!dib){
			std::cout << "Failed to open image!" << std::endl;
			return nullptr;
		}
		
		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		int bits = FreeImage_GetBPP(dib);

		int size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];

		memcpy(result, pixels, size);
		FreeImage_Unload(dib);
		FreeImage_DeInitialise();

		return result;
	}
}