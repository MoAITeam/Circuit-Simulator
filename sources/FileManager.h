//
// Created by Sierra on 2019-08-28.
//

#ifndef FIRSTSIMULATORTEST_FILEMANAGER_H
#define FIRSTSIMULATORTEST_FILEMANAGER_H

#include <string>
#include <fstream>
#include "ComponentData.h"

class FileManager {

public:
    FileManager(std::string path);
    void write(std::string toWrite);
    std::vector<ComponentData> read();

private:
    std::string fileName;

};


#endif //FIRSTSIMULATORTEST_FILEMANAGER_H
