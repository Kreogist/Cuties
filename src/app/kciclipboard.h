#ifndef KCICLIPBOARD_H
#define KCICLIPBOARD_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QClipboard>
#include <QApplication>

class kciClipboard : public QObject
{
    Q_OBJECT
public:
    static kciClipboard* getInstance();
    const QStringList& getClipboardTexts(){return clipboardTexts;}
    
signals:
    
public slots:
    void onSystemClipboardChanged();

private:
    kciClipboard();
    void removeLastTextIfNeeded();

    QStringList clipboardTexts;
    static kciClipboard* instance;
    static int maxDataCount;
};

#endif // KCICLIPBOARD_H
