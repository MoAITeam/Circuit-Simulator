#include "ActiveComponent.h"

void ActiveComponent::drawLabels(QPainter* painter, QString text){
    painter->save();
    painter->translate(QPointF((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2)-pos());
    QFont font=painter->font();
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawText(QPointF(-40,-50), text);
    font.setBold(false);
    painter->setFont(font);
    painter->drawText(QPointF(-40,-50)+QPointF(0,20),QString::number(value)+unit);
    painter->restore();
}

void ActiveComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *s, QWidget *w){
    if(controller!= nullptr)
        drawLabels(painter,label+" ∝ "+controller->getLabel());
    else
        drawLabels(painter,label);
        Component::paint(painter,s,w);
}

float ActiveComponent::getValue(){
    return value;
}

int ActiveComponent::type() const {
    return itemType::activeComponent;
}

std::string ActiveComponent::getData(){
    return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"//";
}