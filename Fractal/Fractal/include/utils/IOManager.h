#ifndef _IOMANAGER_H
#define _IOMANAGER_H

#include <string>
#include <vector>

namespace fractal {
	class IOManager
	{
	public:
		static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(const std::string& filePath, std::string& buffer);
	};
}

#endif // !_IOMANAGER_H
