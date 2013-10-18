#ifndef KCGDBCOMMANDIO_H
#define KCGDBCOMMANDIO_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStyleFactory>

#include "kcplaintextbrowser.h"

class KCDebugCommandIO : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugCommandIO(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QVBoxLayout *mainLayout;
    KCPlainTextBrowser *debugOutputTextBrowser;
    QComboBox *debugInput;
};

#endif // KCGDBCOMMANDIO_H
