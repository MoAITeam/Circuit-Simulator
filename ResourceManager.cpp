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
    auto im_volm=new QPixmap(":/images/voltm.png");
    images.insert(std::make_pair("resistor",*im_res));
    images.insert(std::make_pair("currentSource",*im_cur));
    images.insert(std::make_pair("voltageSource",*im_vol));
    images.insert(std::make_pair("wire",*im_wir));
    images.insert(std::make_pair("voltmeter",*im_volm));

    myStrComponent.insert(std::make_pair(Component::types::resistor ,"Resistor"));
    myStrComponent.insert(std::make_pair(Component::types::currentSource ,"Current Source"));
    myStrComponent.insert(std::make_pair(Component::types::voltageSource ,"Voltage Source"));
    myStrComponent.insert(std::make_pair(Component::types::wire ,"Wire"));
    myStrComponent.insert(std::make_pair(Component::types::voltmeter ,"Voltmeter"));



}

QPixmap& ResourceManager::getImage(std::string const &filename) {

auto myPair=sInstance->images.find(filename);
if(myPair!=sInstance->images.end())
    return myPair->second;
}

std::string ResourceManager::getName(Component::types const type) {
    auto myNames=sInstance->myStrComponent.find(type);
    if(myNames!=sInstance->myStrComponent.end())
        return myNames->second;
}