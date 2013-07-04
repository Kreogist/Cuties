#ifndef KCICONTROLCENTER_H
#define KCICONTROLCENTER_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QFrame>
#include <QIcon>
#include <QSize>
#include <QHBoxLayout>
#include <QStackedWidget>

class kciControlCenter : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenter(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    enum ControlCenterItems
    {
        cciGeneral,
        cciEditor,
        cciCompiler,
        cciDebugger,
        cciFileAssociation,
        cciLanguage,
        ControlCenterItemCount  //the number of contorl center items.
    };

    QToolButton *LeftListItem[ControlCenterItemCount];
    QVBoxLayout *WholeTitleBarSplit;
    QVBoxLayout *LeftListButtons;
    QFrame *fraSplitLine;

    void createLeftList();
    
};

#endif // KCICONTROLCENTER_H
