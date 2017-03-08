#include "utils\IOManager.h"
#include <fstream>

namespace fractal {
	bool IOManager::readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer) {
		std::ifstream file(filePath, std::ios::binary); //reads the file in a binary format (raw bytes)

		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end of the file
		file.seekg(0, std::ios::end); //zero offset
									  //get the file size
		std::streamsize fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		//reduce the file size by any header that might be present
		fileSize -= file.tellg();

		buffer.resize((unsigned int)fileSize);
		file.read((char*)&(buffer[0]), fileSize); //converting the vector to a char*
		file.close();

		return true;
	}

	bool IOManager::readFileToBuffer(const std::string& filePath, std::string& buffer) {
		std::ifstream file(filePath, std::ios::binary); //reads the file in a binary format (raw bytes)

		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end of the file
		file.seekg(0, std::ios::end); //zero offset
									  //get the file size
		std::streamsize fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		//reduce the file size by any header that might be present
		fileSize -= file.tellg();

		buffer.resize((unsigned int)fileSize);
		file.read((char*)&(buffer[0]), fileSize); //converting the vector to a char*
		file.close();

		return true;
	}
}