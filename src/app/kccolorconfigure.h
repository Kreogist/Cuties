#ifndef KCCOLORCONFIGURE_H
#define KCCOLORCONFIGURE_H

#include <QMap>
#include <QPalette>

#include "kcconfigure.h"

class KCColorConfigure : public KCConfigure
{
    Q_OBJECT
public:
    static KCColorConfigure *getInstance();
    void readConfigure();
    void writeConfigure();

    void getPalette(QPalette& pal,const QString& text) const;

signals:

public slots:

private:
    struct ColorInfo
    {
        int r,g,b;
        QPalette::ColorRole colorRole;
    };

    KCColorConfigure();

    static KCColorConfigure *instance;
    QMap<QString,QVector<ColorInfo>> color;
};

#endif // KCCOLORCONFIGURE_H
