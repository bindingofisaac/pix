#include <Utils.hpp>

namespace Pix{
    std::string read_file(const std::string filePath){
        std::ifstream file(filePath);

        if(file.fail()){
            logger<<"unable to open "<<filePath<<"\n";
        }

        std::string fileContents = "", line;
        while(std::getline(file, line)){
            fileContents += line + "\n";
        }
        file.close();
        return fileContents;
    }
}
