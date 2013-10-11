#ifndef KCCOLORCONFIGURE_H
#define KCCOLORCONFIGURE_H

#include <QMap>
#include <QPalette>
#include <QDebug>

#include "kcconfigure.h"

class KCColorConfigure : public KCConfigure
{
    Q_OBJECT
public:
    static KCColorConfigure *getInstance();
    void readConfigure();
    void writeConfigure();

    void getPalette(QPalette &pal, const QString &objectName) const;
    void registerColorInfo(QPalette::ColorRole role,
                           const QColor &color,
                           const QString &objectName);

    static QString getColorConfigFilePath();
    static void setColorConfigFilePath(const QString &filePath);

signals:

public slots:

private:
    struct Color
    {
        int r,g,b;
        Color()
        {
            r=-1;
            g=-1;
            b=-1;
        }
        Color(int red,int green,int blue)
        {
            r=red;
            g=green;
            b=blue;
        }
    };
    struct ColorInfo
    {
        Color color;
        QPalette::ColorRole colorRole;
        ColorInfo operator = (const Color &a)
        {
            color.r=a.r;
            color.g=a.g;
            color.b=a.b;
            return *this;
        }
    };

    KCColorConfigure();
    Color parseColor(const QString &content);
    Color parseObjectColor(const QString &content);
    bool isValidColor(const Color &color);
    QPalette::ColorRole getColorRoleFromString(const QString &string);
    QString getColorRoleString(QPalette::ColorRole role);

    static KCColorConfigure *instance;
    static QString colorConfigFilePath;
    QMap<QString,QVector<ColorInfo>> colorInfoMap;
    QMap<QString,Color> colorSheet;
};

#endif // KCCOLORCONFIGURE_H
