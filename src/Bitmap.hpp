#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <stdio.h>

class Bitmap {
	public:
		
		Bitmap();

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

			dataPos    = *(int*)&(header[0x0A]);
			imageSize  = *(int*)&(header[0x22]);
			width      = *(int*)&(header[0x12]);
			height     = *(int*)&(header[0x16]);

			if (imageSize == 0) imageSize = width * height * 3;
			if (dataPos == 0) dataPos = 54;

			data = new unsigned char [imageSize];
			fread(data,1,imageSize,file);
			fclose(file);

		}

		inline unsigned char * getData() { return data; }
		inline unsigned int getWidth() { return width; }
		inline unsigned int getHeight() { return height; }
		inline unsigned int getSize() { return imageSize; }

	private:
			unsigned int dataPos;
			unsigned int width, height;
			unsigned int imageSize;
			unsigned char * data;
};

#endif