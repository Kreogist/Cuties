/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QTranslator>
#include <QStyle>
#include <QFont>
#include <QFile>
#include <QString>
#include <QStyleFactory>
#include <QDebug>

#include "mainwindow.h"
#include "kciglobal.h"
#include "kreogistcutestyle.h"

int main(int argc, char *argv[])
{
    //Load QApplication Object.
    QApplication app(argc,argv);

    //Initialize Application Infomation.
    QApplication::setApplicationName(QString("Kreogist Cuties"));
    QApplication::setApplicationVersion(QString("0.0.0.1"));
    QApplication::setApplicationDisplayName(QString("Kreogist Cuties"));
    QApplication::setOrganizationName("Kreogist Team");
    QApplication::setOrganizationDomain("https://kreogist.github.io/Cuties");

    //Initialize Application Icon.
    QApplication::setWindowIcon(QIcon(":/mainicon/image/Cuties.ico"));

    //Initialize Application Language.
    QTranslator appTrans;
    appTrans.load(qApp->applicationDirPath() + "/Locale/" + QLocale::system().name());
    app.installTranslator(&appTrans);

    //Initialize Application Fonts
    QStringList list;
    list << "monaco.ttf" << "Kreogist-UI.ttf";
    int fontID(-1);
    bool fontWarningShown(false);
    for (auto constIterator = list.constBegin();
         constIterator != list.constEnd();
         ++constIterator)
    {
        QFile res(qApp->applicationDirPath() + "/Fonts/" + *constIterator);
        if (res.open(QIODevice::ReadOnly) == false) {
            if (fontWarningShown == false) {
                QMessageBox::warning(0,
                                     QApplication::applicationName(),
                                     QString(QApplication::tr("Error occur when load font file.")) +
                                     "\n" +
                                     QString(QApplication::tr("Error: ")) +
                                     res.errorString());
                fontWarningShown = true;
            }
        } else {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if (fontID == -1 && fontWarningShown == false) {
                QMessageBox::warning(0,
                                     QApplication::applicationName(),
                                     QString(QApplication::tr("Error occur when load font file.")) +
                                     "\n" +
                                     QString(QApplication::tr("Error: ")) +
                                     res.errorString());
                fontWarningShown = true;
            }
        }
    }

    //Initalize Application Palette.
    QPalette pal=app.palette();
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::Highlight,QColor(0xf7,0xcf,0x3d));
    pal.setColor(QPalette::HighlightedText,QColor(0,0,0));
    app.setPalette(pal);

    //Initalize Application Style
    KreogistCuteStyle *cuteStyle=new KreogistCuteStyle;
    app.setStyle(cuteStyle);

    //Initalize and show Application MainWindow.
    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
