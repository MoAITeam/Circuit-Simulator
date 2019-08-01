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

    static  QPixmap& getImage(Component::types const &type);

private:
    std::map<Component::types,QPixmap> images;

    static ResourceManager *sInstance;


};


#endif //FIRSTSIMULATORTEST_RESOURCEMANAGER_H
