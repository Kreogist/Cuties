#ifndef KCICONTROLCENTER_H
#define KCICONTROLCENTER_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QIcon>
#include <QSize>
#include <QHBoxLayout>

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
    QVBoxLayout *LeftListButtons;

    void createLeftList();
    
};

#endif // KCICONTROLCENTER_H
