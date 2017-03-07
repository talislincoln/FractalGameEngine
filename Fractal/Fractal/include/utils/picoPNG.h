#ifndef PICO_PNG_H
#define PICO_PNG_H
#include <vector>
struct PicoPNG{

	PicoPNG() = delete;
	PicoPNG(const PicoPNG&) = delete;
	PicoPNG(PicoPNG&&) = delete;
	PicoPNG& operator=(const PicoPNG&) = delete;
	PicoPNG& operator=(PicoPNG&&) = delete;

	static int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

};


#endif // !PICO_PNG_H
