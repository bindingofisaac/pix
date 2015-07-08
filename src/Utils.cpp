#include <Utils.hpp>

namespace Pix{
    std::string read_file(const std::string filePath){
        std::ifstream file(filePath);
        // TODO: check for error
        std::string fileContents = "", line;
        while(std::getline(file, line)){
            fileContents += line + "\n";
        }
        file.close();
        return fileContents;
    }
}
