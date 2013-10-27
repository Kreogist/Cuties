#ifndef KCFONTCONFIGURE_H
#define KCFONTCONFIGURE_H

#include <QFont>
#include "kcconfigure.h"

class KCFontConfigure : public KCConfigure
{
public:
    void readConfigure();
    void writeConfigure();
    static KCFontConfigure *getInstance();
    
    void initCustomFonts();
    void applyConfigure();
    void setApplicationFont();
    QString getCodeFontName() const;
    void setCodeFontName(const QString &value);
    QFont getCodeFont() const;
    void setCodeFont(const QFont &value);
    QFont getMenuFont() const;
    void setMenuFont(const QFont &value);

signals:
    
public slots:
    
private:
    KCFontConfigure();
    static KCFontConfigure *instance;
    QFont applicationFont;
    QFont codeFont;
    QFont menuFont;
    QString codeFontName;
};

#endif // KCFONTCONFIGURE_H
