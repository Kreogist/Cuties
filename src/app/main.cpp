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

}

static inline void initApplicationSettings()
{
    KCGlobal *KCGlobalInstance = KCGlobal::getInstance();
    KCGlobalInstance->readSettings();
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
