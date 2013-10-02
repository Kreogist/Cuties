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

#ifndef KCJUDGEDOCK_H
#define KCJUDGEDOCK_H

#include <QList>
#include <QLabel>
#include <QWidget>
#include <QPalette>
#include <QSplitter>
#include <QTreeView>
#include <QIcon>
#include <QAction>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QToolButton>
#include <QToolBar>
#include <QMimeData>
#include <QDebug>
#include <QKeySequence>
#include <QVBoxLayout>
#include <QDockWidget>

class KCJudgeFileEdit : public QWidget
{
    Q_OBJECT
public:
    explicit KCJudgeFileEdit(QWidget *parent = 0);
    QString inputFile();
    QString outputFile();

signals:
    void textChange();

private:
    QLabel *lblInput, *lblOutput, *lblUserOutput;
    QPlainTextEdit *InputFileEdit, *OutputFileEdit, *UserOutput;
    QVBoxLayout *EditLayout;
};

class KCIJudgeEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KCIJudgeEditWidget(QWidget *parent = 0);

private slots:
    void addNewTab();
    void removeCurrentTab();
    void documentChanged();
    void backupTestData();
    void importTestData();

private:
    int judge_file_count;
    QTabWidget *tabJudgeFiles;
    QToolBar *tlbJudge;
    QVBoxLayout *MainLayout;
    QToolButton *tlbacAdd, *tlbacRemove, *tlbacStartAll, *tlbacStop,
                *tlbacBackup, *tlbacImport;

    QList<QString> strInputFiles, strOutputFiles;

    void resetJudgetEditWidget();
    void removeTabIndex(int TabIndex);
};

class KCIJudgeDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCIJudgeDock(QWidget *parent = 0);
    
signals:

public slots:

private:
    QTreeView *trevwJudgeList;
    QSplitter *splCombine;
    QList<int> l_sizes;
    QToolButton *addANewTab;
    KCIJudgeEditWidget *kjwEditWidget;
};

#endif // KCJUDGEDOCK_H
