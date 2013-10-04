#include "kccolorconfigure.h"

KCColorConfigure *KCColorConfigure::instance=nullptr;
QString KCColorConfigure::colorConfigFilePath("DefaultColorConfig.ini");

KCColorConfigure *KCColorConfigure::getInstance()
{
    return instance==nullptr?
           instance=new KCColorConfigure:instance;
}

void KCColorConfigure::readConfigure()
{
    QSettings settings(colorConfigFilePath,QSettings::IniFormat);

    int i=settings.beginReadArray("UI-Palette");
    while(i--)
    {
        settings.setArrayIndex(i);

        QVector<ColorInfo> colorInfos;
        for(int j=settings.beginReadArray("ColorInfo")-1;
            j>=0;
            j--)
        {
            settings.setArrayIndex(j);

            ColorInfo _info;
            _info.r=settings.value("r").toInt();
            _info.g=settings.value("g").toInt();
            _info.b=settings.value("b").toInt();
            colorInfos<<_info;
        }
        settings.endArray();
        color.insert(settings.value("ObjectName").toString(),colorInfos);
    }
    settings.endArray();
}

void KCColorConfigure::writeConfigure()
{
    QSettings settings(colorConfigFilePath,QSettings::IniFormat);

    settings.beginWriteArray("UI-Palette");
    int count=0;
    for(auto i=color.begin();
        i!=color.end();
        i++,count++)
    {
        settings.setArrayIndex(count);

        settings.setValue("ObjectName",i.key());
        settings.beginWriteArray("ColorInfo");
        int _countColorInfo=0;
        const QVector<ColorInfo> &_colorInfos=i.value();
        for(auto j=_colorInfos.begin();
            j!=_colorInfos.end();
            j++,_countColorInfo++)
        {
            settings.setArrayIndex(_countColorInfo);

            const ColorInfo &_colorInfo=*j;
            settings.setValue("r",_colorInfo.r);
            settings.setValue("g",_colorInfo.g);
            settings.setValue("b",_colorInfo.b);
        }
        settings.endArray();
    }
    settings.endArray();
}

void KCColorConfigure::getPalette(QPalette &pal, const QString &objectName) const
{
    auto iterator=color.find(objectName);
    if(iterator!=color.end())
    {
        const QVector<ColorInfo> &colorVector=*iterator;
        for(auto i=colorVector.begin();
            i!=colorVector.end();
            i++)
        {
            pal.setColor(i->colorRole,QColor(i->r,i->g,i->b));
        }
    }
}

void KCColorConfigure::registerColorInfo(QPalette::ColorRole role,
                                         const QColor &color,
                                         const QString &objectName)
{
    QVector<ColorInfo> &colorInfos=this->color[objectName];
    ColorInfo colorInfo;
    color.getRgb(&colorInfo.r,&colorInfo.g,&colorInfo.b);
    colorInfo.colorRole=role;
    colorInfos.append(colorInfo);
}

KCColorConfigure::KCColorConfigure()
{

}

QString KCColorConfigure::getColorConfigFilePath()
{
    return colorConfigFilePath;
}

void KCColorConfigure::setColorConfigFilePath(const QString &filePath)
{
    colorConfigFilePath = filePath;
}
