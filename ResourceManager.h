//
// Created by cipher on 22/07/19.
//

#ifndef FIRSTSIMULATORTEST_RESOURCEMANAGER_H
#define FIRSTSIMULATORTEST_RESOURCEMANAGER_H

#include <map>
#include <QtWidgets>
#include <QtGui/QtGui>



class ResourceManager {

public:
    ResourceManager();

    static  QPixmap& getImage(std::string const &filename);

private:
    std::map<std::string,QPixmap> images;

    static ResourceManager *sInstance;


};


#endif //FIRSTSIMULATORTEST_RESOURCEMANAGER_H
