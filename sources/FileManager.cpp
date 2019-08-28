//
// Created by Sierra on 2019-08-28.
//

#include "FileManager.h"

FileManager::FileManager(std::string path) {
    fileName=path;
}

void FileManager::write(std::string toWrite) {
    std::ofstream outputStream(fileName);
    outputStream << toWrite;
}

std::vector<ComponentData> FileManager::read() {

    std::vector<ComponentData> circuitData;
    std::ifstream inputStream(fileName);

    std::string buffer;
    std::vector<std::string> data;

    while (inputStream.good()) {
        getline(inputStream, buffer, '/');
        data.push_back(buffer);
    }

    for(int i=0;i<data.size()-8;i+=8) {
        ComponentData componentData;
        componentData.type = Component::types(std::stoi(data[i + 0]));
        componentData.label = data[i + 1];
        componentData.value = stof(data[i + 2]);
        componentData.pX = std::stof(data[i + 3]);
        componentData.pY = std::stof(data[i + 4]);
        componentData.nX = std::stof(data[i + 5]);
        componentData.nY = std::stof(data[i + 6]);
        componentData.dependent =data[i+7];
        circuitData.push_back(componentData);
    }

    return circuitData;
}