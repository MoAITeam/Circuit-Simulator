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
    auto im_amp=new QPixmap(":/images/amperometer.png");
    auto im_volm=new QPixmap(":/images/voltm.png");
    auto im_gnd=new QPixmap(":/images/ground.png");
    auto im_vcvs=new QPixmap(":/images/vcvs.png");
    images.insert(std::make_pair("resistor",*im_res));
    images.insert(std::make_pair("currentSource",*im_cur));
    images.insert(std::make_pair("voltageSource",*im_vol));
    images.insert(std::make_pair("wire",*im_wir));
    images.insert(std::make_pair("amperometer",*im_amp));
    images.insert(std::make_pair("voltmeter",*im_volm));
    images.insert(std::make_pair("ground",*im_gnd));
    images.insert(std::make_pair("vcvs",*im_vcvs));

    myStrComponent.insert(std::make_pair(Component::types::resistor ,"Resistor"));
    myStrComponent.insert(std::make_pair(Component::types::currentSource ,"Current Source"));
    myStrComponent.insert(std::make_pair(Component::types::voltageSource ,"Voltage Source"));
    myStrComponent.insert(std::make_pair(Component::types::wire ,"Wire"));
    myStrComponent.insert(std::make_pair(Component::types::amperometer ,"Amperometer"));
    myStrComponent.insert(std::make_pair(Component::types::vcvs ,"Vcvs"));
    myStrComponent.insert(std::make_pair(Component::types::ground ,"Ground"));
    // myStrComponent.insert(std::make_pair(Component::types::voltmeter ,"Voltmeter"));



}

QPixmap& ResourceManager::getImage(std::string const &filename) {
QPixmap result;
auto myPair=sInstance->images.find(filename);
if(myPair!=sInstance->images.end())
    result=myPair->second;
return result;
}

std::string ResourceManager::getName(Component::types const type) {
    std::string result;
    auto myNames=sInstance->myStrComponent.find(type);
    if(myNames!=sInstance->myStrComponent.end())
        result=myNames->second;
    return result;
}