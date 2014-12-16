#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <stdio.h>

class Bitmap {
	
	public:
		
		Bitmap() {};

		Bitmap(const char * imagepath) {
			
			FILE * file = fopen(imagepath,"rb");
			if (!file) {
				printf("Image could not be opened\n");
				// return 0;
			}

			unsigned char header[54];
			if (fread(header, 1, 54, file) != 54) {
    			printf("Not a correct BMP file\n");
    			// return false;
			}

			if (header[0] != 'B' || header[1] != 'M') {
    			printf("Not a correct BMP file\n");
    			// return 0;
			}

			dataPos    = *(unsigned int*)&(header[0x0A]);
			imageSize  = *(unsigned int*)&(header[0x22]);
			width      = *(unsigned int*)&(header[0x12]);
			height     = *(unsigned int*)&(header[0x16]);

			if (imageSize == 0) imageSize = width * height * 3;
			if (dataPos == 0) dataPos = 54;

			data = new unsigned char [imageSize];
			fread(data,1,imageSize,file);
			fclose(file);

		}

		unsigned char * getData() const { return data; }
		unsigned int getWidth() const { return width; }
		unsigned int getHeight() const { return height; }
		unsigned int getSize() const { return imageSize; }

	private:

		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
};

#endif