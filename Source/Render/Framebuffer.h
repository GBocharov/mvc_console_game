#ifndef OOP_RENDER_FRAMEBUFFER_H_
#define OOP_RENDER_FRAMEBUFFER_H_

#include <string>
#include <utility>
#include "../Def.h"

class Framebuffer {
public:
	explicit Framebuffer(const coord_t &size);

	void SetPixel(const coord_t &coord, char value);

	void Present();

	void Clear();

private:
	std::string buffer_;
	coord_t size_;
};

#endif // OOP_RENDER_FRAMEBUFFER_H_

