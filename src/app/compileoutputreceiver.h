#ifndef COMPILEOUTPUTRECEIVER_H
#define COMPILEOUTPUTRECEIVER_H

#include <QStandardItemModel>
#include <QTime>
#include <QDebug>

#include "compilerbase.h"

class compileOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit compileOutputReceiver(QObject *parent = 0);
    //Tree View Controls:
    void addRootItem(const ErrInfo& error);
    void clearAllItem();

    //Text Controls:
    void clearText();
    void addText(const QString& NewText);
    void addForwardText();

    void reset();

    QStandardItemModel *getCompilerOutputModel() const;
    const QString& getCompilerOutputText() const;
    const QVector<ErrInfo> *getErifList() const;

    bool hasCompileError();

    QString getCompilerVersionString() const;
    void setCompilerVersionString(const QString& strVersion);

signals:
    void requireShowError();
    void compilerOutputTextChanged(QString text);
    
public slots:
    void onCompileMsgReceived(ErrInfo error);
    void onCompileFinished(bool hasError);
    
private:
    bool hasOutput;
    QStandardItemModel *compilerOutputModel;
    QString compilerOutputText;
    QModelIndex lastSelIndex;
    QVector<ErrInfo> erifList;
    QString compilerVersion;
};

#endif // COMPILEOUTPUTRECEIVER_H
