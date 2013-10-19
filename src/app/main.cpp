/*
 *  Copyright 2013 Kreogist Dev Team
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
#include <QDir>
#include <QList>
#include <QFileInfo>
#include <QStringList>
#include <QStyleFactory>
#include <QDebug>
#include <QTimer>

#include "mainwindow.h"
#include "kcglobal.h"
#include "kcsplashscreen.h"
#include "kcmessagebox.h"
#include "kreogistcutestyle.h"

static inline void initApplicationInfo()
{
    QApplication::setApplicationName(QString("Cuties"));
    QApplication::setApplicationVersion(QString("0.1.0.1"));
    QApplication::setOrganizationName("Kreogist Dev Team");
    QApplication::setOrganizationDomain("https://kreogist.github.io/Cuties");

    QApplication::setWindowIcon(QIcon(":/mainicon/image/Cuties.png"));
}

static void initApplicationFonts()
{
    QStringList filter;
    QDir *dir=new QDir(QString(qApp->applicationDirPath() + "/Fonts/"));
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));

    int fontID(-1);
    bool fontWarningShown(false);
    for(QList<QFileInfo>::iterator i=list->begin();
        i!=list->end();
        ++i)
    {
        if(i->fileName().length() < 4)
        {
            continue;
        }
        QFile res(i->filePath());
        if(res.open(QIODevice::ReadOnly) == false)
        {
            if(fontWarningShown == false)
            {
                QMessageBox::warning(0,
                                     QApplication::applicationName(),
                                     QString(QApplication::tr("Error occur when load font file.")) +
                                     "\n" +
                                     QString(QApplication::tr("Error: ")) +
                                     res.errorString());
                fontWarningShown = true;
            }
        }
        else
        {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if(fontID == -1 && fontWarningShown == false)
            {
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
}

static inline void initApplicationSettings()
{
    KCGlobal *KCGlobalInstance = KCGlobal::getInstance();
    KCGlobalInstance->readSettings();
}

void KCMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QFile file(QApplication::applicationDirPath()+"/log.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out<<(QTime::currentTime().toString().toUtf8()+" ");
        switch (type)
        {
        case QtDebugMsg:
            out<<QString("").sprintf("Debug: (%s:%u, %s)\n",
                                     context.file,
                                     context.line,
                                     context.function);
            break;
        case QtWarningMsg:
            out<<QString("").sprintf("Warning: (%s:%u, %s)\n",
                                     context.file,
                                     context.line,
                                     context.function);
            break;
        case QtCriticalMsg:
            out<<QString("").sprintf("Critical: (%s:%u, %s)\n",
                                     context.file,
                                     context.line,
                                     context.function);
            break;
        case QtFatalMsg:
            out<<QString("").sprintf("Fatal: (%s:%u, %s)\n",
                                     context.file,
                                     context.line,
                                     context.function);
            out<<msg<<"\n";
            abort();
        }
        out<<msg<<"\n";
    }

    QByteArray localMsg = msg.toUtf8();
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(KCMessageHandler);
    //Load QApplication Object.
    QApplication app(argc,argv);

    //Load Splash Screen
    KCSplashScreen *splash=new KCSplashScreen;
    splash->setPixmap(QPixmap(":/img/image/Splash.png"));
    splash->show();
    splash->raise();
    app.processEvents();

    /*static int splashAlign=Qt::AlignBottom|Qt::AlignRight;
    splash->showMessage(QApplication::tr("Initialize Application"),
                        splashAlign);*/
    initApplicationInfo();
    app.processEvents();

    /*splash->showMessage(QApplication::tr("Initialize Application Fonts"),
                        splashAlign);*/
    initApplicationFonts();
    app.processEvents();

    /*splash->showMessage(QApplication::tr("Initialize Application Settings"),
                        splashAlign);*/
    initApplicationSettings();
    app.processEvents();

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
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
