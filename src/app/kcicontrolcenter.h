#ifndef KCICONTROLCENTER_H
#define KCICONTROLCENTER_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QFrame>
#include <QLabel>
#include <QIcon>
#include <QSize>
#include <QHBoxLayout>
#include <QStackedWidget>

class kciControlCenterBanner : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenterBanner(QWidget *parent = 0);

private:
    QLabel *lblBannerTitle;

};

class ccGeneral : public QWidget
{
    Q_OBJECT
public:
    explicit ccGeneral(QWidget *parent = 0);
private:

};

class ccEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ccEditor(QWidget *parent = 0);
private:
};

class ccCompiler : public QWidget
{
    Q_OBJECT
public:
    explicit ccCompiler(QWidget *parent = 0);
private:
};

class ccDebugger : public QWidget
{
    Q_OBJECT
public:
    explicit ccDebugger(QWidget *parent = 0);
private:
};

class ccFileAssociation : public QWidget
{
    Q_OBJECT
public:
    explicit ccFileAssociation(QWidget *parent = 0);
private:
};

class ccLanguage : public QWidget
{
    Q_OBJECT
public:
    explicit ccLanguage(QWidget *parent = 0);
private:
};

class kciControlCenter : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenter(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QStackedWidget *ccMainTabs;
    ccGeneral *tabGeneral;
    ccEditor *tabEditor;
    ccCompiler *tabCompiler;
    ccDebugger *tabDebugger;
    ccFileAssociation *tabFileAssociation;
    ccLanguage *tabLanguage;
    QVBoxLayout *WholeTitleBarSplit;
    kciControlCenterBanner *ccBanner;

    void createLeftList();
    
};

#endif // KCICONTROLCENTER_H
