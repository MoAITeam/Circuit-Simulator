//
// Created by cipher on 22/07/19.
//

#ifndef FIRSTSIMULATORTEST_RESOURCEMANAGER_H
#define FIRSTSIMULATORTEST_RESOURCEMANAGER_H

#include <map>
#include <QtWidgets>
#include <QtGui/QtGui>
#include "Component.h"



class ResourceManager {

public:
    ResourceManager();

    static  QPixmap& getImage(std::string const &filename);

    static std::string getName(Component::types const type);

private:
    std::map<std::string,QPixmap> images;
    std::map<Component::types ,std::string> myStrComponent;

    static ResourceManager *sInstance;


};


#endif //FIRSTSIMULATORTEST_RESOURCEMANAGER_H
