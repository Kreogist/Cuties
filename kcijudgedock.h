#ifndef KCIJUDGEDOCK_H
#define KCIJUDGEDOCK_H

#include <QList>
#include <QLabel>
#include <QWidget>
#include <QPalette>
#include <QSplitter>
#include <QTreeView>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDockWidget>

class kciJudgeFileEdit : public QWidget
{
    Q_OBJECT
public:
    explicit kciJudgeFileEdit(QWidget *parent = 0);

private:
    QLabel *lblInput, *lblOutput, *lblUserOutput;
    QPlainTextEdit *InputFileEdit, *OutputFileEdit, *UserOutput;
    QVBoxLayout *EditLayout;
};

class kciJudgeDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit kciJudgeDock(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QTreeView *trevwJudgeList;
    QSplitter *splCombine;
    QTabWidget *tabJudgeFiles;
    QList<int> l_sizes;
    QToolButton *addANewTab;

};

#endif // KCIJUDGEDOCK_H
