/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  main.cpp is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QTranslator>
#include <QStyle>
#include <QFont>
#include <QFile>
#include <QString>
#include <QStyleFactory>
#include "mainwindow.h"
#include "kreogistcutestyle.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QStringList list;
    list << "Hiragino.otf";
    int fontID(-1);
    bool fontWarningShown(false);
    for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
        QFile res(qApp->applicationDirPath() + "/Fonts/" + *constIterator);
        if (res.open(QIODevice::ReadOnly) == false) {
            if (fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Impossible d'ouvrir la police " + QChar(0x00AB) + " DejaVu Serif " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        } else {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if (fontID == -1 && fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Impossible d'ouvrir la police " + QChar(0x00AB) + " DejaVu Serif " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        }
    }

    QApplication::setApplicationName(QString("Kreogist Cute IDE"));
    QApplication::setApplicationVersion(QString("0.1.0"));
    QApplication::setOrganizationName("Kreogist Team");
    QApplication::setOrganizationDomain("https://github.com/Harinlen/Kreogist-Cute-IDE");
    app.setFont(QFont("Hiragino Sans GB W3", 10));

    QTranslator appTrans;

    appTrans.load(qApp->applicationDirPath() + "/" + QLocale::system().name());
    app.installTranslator(&appTrans);

    QPalette pal=app.palette();
    //pal.setColor(QPalette::Window,QColor(0x53,0x53,0x53));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::Highlight,QColor(0xf7,0xcf,0x3d));
    pal.setColor(QPalette::HighlightedText,QColor(0,0,0));
    app.setPalette(pal);

    //set style
    KreogistCuteStyle *cuteStyle=new KreogistCuteStyle;
    app.setStyle(cuteStyle);
    //app.setStyle("fusion");

    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
