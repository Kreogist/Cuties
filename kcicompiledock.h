#ifndef KCICOMPILEDOCK_H
#define KCICOMPILEDOCK_H

#include <QTreeView>
#include <QPalette>
#include <QDebug>
#include <QSignalMapper>
#include <QDockWidget>

class kcicompiledock : public QDockWidget
{
    Q_OBJECT
public:
    explicit kcicompiledock(QWidget *parent = 0);
    
private:
    QTreeView *trevwCompileInfo;

signals:
    
public slots:
    void parseMessage(QString msg);
    
};

#endif // KCICOMPILEDOCK_H
