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
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>. *  
 */

/*!
 *  \copyright GNU Public License
 *  \details
 *    This file contains the main() of this program. Many initialization functions are defined here.
 */

#include <QApplication>
#include <QTranslator>
#include <QStyle>
#include <QString>
#include <QStyleFactory>
#include <QDebug>
#include <QTimer>

#include <cstdlib>

#include "mainwindow.h"
#include "kcglobal.h"
#include "kcsplashscreen.h"
#include "kcmessagebox.h"
#include "kreogistcutestyle.h"
#include "kcstatusrecorder.h"
#include "kcdocumentrecorder.h"

static inline void setApplicationInfo()
{
    QApplication::setApplicationName(QString("Cuties"));
    QApplication::setApplicationVersion(QString("0.2.6.3"));
    QApplication::setOrganizationName("Kreogist Dev Team");
    QApplication::setOrganizationDomain("https://kreogist.github.io/Cuties");

    QApplication::setWindowIcon(QIcon(":/mainicon/image/Cuties.png"));
}

static inline void initApplicationSettings()
{
    KCStatusRecorder::getInstance()->readRecord();
    KCDocumentRecorder::getInstance()->readSettings();
    KCGlobal *KCGlobalInstance = KCGlobal::getInstance();
    KCGlobalInstance->readSettings();
}

static inline void printVersion()
{
    printf("%s\n",qApp->applicationName().toLocal8Bit().constData());
    printf("Version: %s\n",qApp->applicationVersion().toLocal8Bit().constData());
    printf("Copyright (C) 2013 %s\n",qApp->organizationName().toLocal8Bit().constData());
    printf("Homepage: %s\n",qApp->organizationDomain().toLocal8Bit().constData());
    printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n");
    printf("This is free software: you are free to change and redistribute it.\n");
}

static inline void printHelp()
{
    QByteArray appName=qApp->applicationName().toLocal8Bit();
    printf("Usage:\n");
    printf("  %s -h,--help              Print this message\n",
           appName.constData());
    printf("  %s -v,--version           Print %s version\n",
           appName.constData(),
           appName.constData());
    printf("  %s [FILES]             Open [FILES] in %s\n",
           appName.constData(),
           appName.constData());
    fflush(stdout);
}

static inline void processArg()
{
    QStringList argList=qApp->arguments();

    //remove the application name
    argList.removeFirst();

    for(int i=0,l=argList.size();i<l;i++)
    {
        const QString &arg=argList.at(i);
        if(arg == "--version" || arg == "-v")
        {
            printVersion();
            std::exit(0);
        }
        else if(arg == "--help" || arg == "-h")
        {
            printHelp();
            std::exit(0);
        }
        else if(QFileInfo(arg).exists())
        {
            /*
             * We didn't have a normal way to open a file before the MainWindow be created.
             * But MainWindow will open the files which didn't be closed when quit Cuties.
             * So we add it as a unclosed file so that when the mainwindow show,it will be opened.
             */
            KCHistoryConfigure::getInstance()->addUnClosedFilePath(QFileInfo(arg).absoluteFilePath(),0,0);
        }
    }

}

/*!
 * \brief This is a custom message handler to deal with Qt's message(for example, qDebug).
 *
 *  KCMessageHandler outputs message which was sended by calling qDebug()(and so on) to both file
 *  (named log.txt) and stderr. This function will be called by Qt.
 * \param type describes the messages that be sent to a message handler
 * \param context This provides additional information about a log message.
 * \param msg message
 */
void KCMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QFile file(QApplication::applicationDirPath()+"/log.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out<<(QTime::currentTime().toString().toUtf8()+" ");
        switch(type)
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
    switch(type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: (%s:%u, %s)\n", context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: (%s:%u, %s)\n", context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: (%s:%u, %s)\n", context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: (%s:%u, %s)\n", context.file, context.line, context.function);
        abort();
    }
    fprintf(stderr,"%s", localMsg.constData());
}

/*!
 * \brief main() initial application's informations, language, fonts and set KCMessageHandler.
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    //qInstallMessageHandler(KCMessageHandler);
    //Load QApplication Object.
    QApplication app(argc,argv);
    setApplicationInfo();
    processArg();

    app.setEffectEnabled(Qt::UI_AnimateCombo, true);
    app.setEffectEnabled(Qt::UI_FadeMenu, true);
    app.setEffectEnabled(Qt::UI_AnimateToolBox, true);
    app.setEffectEnabled(Qt::UI_AnimateTooltip, true);
    app.setEffectEnabled(Qt::UI_FadeTooltip, true);

    //Load Splash Screen
    KCSplashScreen *splash=new KCSplashScreen;
    splash->setPixmap(QPixmap(":/img/image/Splash.png"));
    splash->show();
    splash->raise();
    app.processEvents();

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
    splash->finish(&mainWindow);

    return app.exec();
}
