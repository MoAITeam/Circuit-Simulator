//
// Created by cipher on 22/07/19.
//

#include "ResourceManager.h"
#include <cassert>
#include <iostream>

ResourceManager *ResourceManager::sInstance = nullptr;

ResourceManager::ResourceManager() {
    assert(sInstance==nullptr);
    sInstance=this;

    auto im_res=new QPixmap(":/images/resistor.png");
    auto im_vol= new QPixmap(":/images/voltagesource.png");
    auto im_cur=new QPixmap(":/images/currentsource.png");
    auto im_wir=new QPixmap(":/images/wire.png");
    images.insert(std::make_pair("resistor",*im_res));
    images.insert(std::make_pair("CurrentSource",*im_cur));
    images.insert(std::make_pair("voltageSource",*im_vol));
    images.insert(std::make_pair("wire",*im_wir));

}

QPixmap& ResourceManager::getImage(std::string const &filename) {

auto myPair=sInstance->images.find(filename);
if(myPair!=sInstance->images.end())
    return myPair->second;
}