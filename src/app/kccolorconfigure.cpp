#include "kccolorconfigure.h"

KCColorConfigure *KCColorConfigure::instance=nullptr;

KCColorConfigure *KCColorConfigure::getInstance()
{
    return instance==nullptr?
           instance=new KCColorConfigure:instance;
}

void KCColorConfigure::readConfigure()
{

}

void KCColorConfigure::writeConfigure()
{

}

void KCColorConfigure::getPalette(QPalette &pal, const QString &text) const
{
    const QVector<ColorInfo> &colorVector=color[text];
    for(auto i=colorVector.begin();
        i!=colorVector.end();
        i++)
    {
        pal.setColor(i->colorRole,QColor(i->r,i->g,i->b));
    }
}

KCColorConfigure::KCColorConfigure()
{

}
