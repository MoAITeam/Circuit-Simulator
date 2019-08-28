//
// Created by cipher on 22/07/19.
//

#include "ResourceManager.h"
#include <cassert>
#include <iostream>

//SINGLETON: over-used images are instanziated only 1 time

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
    auto im_vccs=new QPixmap(":/images/vccs.png");
    auto im_cccs=new QPixmap(":/images/cccs.png");
    auto im_ccvs=new QPixmap(":/images/ccvs.png");

    images.insert(std::make_pair(Component::types::resistor,im_res));
    images.insert(std::make_pair(Component::types::currentSource ,im_cur));
    images.insert(std::make_pair(Component::types::voltageSource ,im_vol));
    images.insert(std::make_pair(Component::types::wire,im_wir));
    images.insert(std::make_pair(Component::types::amperometer ,im_amp));
    images.insert(std::make_pair(Component::types::voltmeter ,im_volm));
    images.insert(std::make_pair(Component::types::ground ,im_gnd));
    images.insert(std::make_pair(Component::types::vcvs ,im_vcvs));
    images.insert(std::make_pair(Component::types::vccs ,im_vccs));
    images.insert(std::make_pair(Component::types::ccvs ,im_ccvs));
    images.insert(std::make_pair(Component::types::cccs ,im_cccs));

}

QPixmap ResourceManager::getImage(Component::types const &type) {
    QPixmap* result;
    auto myPair=sInstance->images.find(type);
    if(myPair!=sInstance->images.end())
        result=myPair->second;
    return *result;
}