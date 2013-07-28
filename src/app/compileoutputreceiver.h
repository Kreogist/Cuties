#ifndef COMPILEOUTPUTRECEIVER_H
#define COMPILEOUTPUTRECEIVER_H

#include <QObject>
#include <QStandardItemModel>
#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QTextCursor>
#include <QTime>

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
    void addText(QString NewText);
    void addForwardText();

    void reset();

    //getter
    QStandardItemModel *getCompilerOutputModel() const;
    QTextDocument *getCompilerOutputText() const;
    const QVector<ErrInfo> *getErifList() const;

    bool hasCompileError();

    void connectCompiler(compilerBase* compiler);

    QString getCompilerVersion() const;

signals:
    void requireShowError();
    
public slots:
    void onCompileMsgReceived(ErrInfo error);
    void compileFinish(int ExitNum);
    
private:
    enum connectionType
    {
        compileinfo,
        output,
        compileError,
        finished,
        typeCount
    };

    bool hasError;
    QStandardItemModel *compilerOutputModel;
    QTextDocument *compilerOutputText;
    QPlainTextDocumentLayout *plainTextLayout;
    QModelIndex lastSelIndex;
    QVector<ErrInfo> erifList;
    QString compilerVersion;

    compilerBase *connectedCompiler;

    QMetaObject::Connection connectHandle[typeCount];
};

#endif // COMPILEOUTPUTRECEIVER_H
