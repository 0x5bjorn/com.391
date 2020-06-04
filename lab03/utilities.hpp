#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <sstream>
#include <fstream>

class FileUtilities {
public:
    static const std::string read_text_file(const std::string& path) {
        std::ifstream file_stream(path);
        std::stringstream string_stream;
        string_stream << file_stream.rdbuf();

        return string_stream.str();

        // std::string result; 
        // std::ifstream in(path, std::ios::in | std::ios::binary);
        // if(in)
        // {
        //     in.seekg(0, std::ios::end);
        //     size_t size = in.tellg();
        //     if(size != -1)
        //     {
        //         result.resize(size);
        //         in.seekg(0, std::ios::beg);
        //         in.read(&result[0], size);
        //         in.close();
        //     }
        // } else {
        //     std::cout << "!!!Failed to read!!!" << std::endl;
        // }

        // return result;
    }
};

#endif
