#ifndef KCISETTINGLISTITEMFOLDERTEXT_H
#define KCISETTINGLISTITEMFOLDERTEXT_H

#include <QLineEdit>

#include "kcisettinglistitembase.h"

class kciSettingListItemFolderText : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemFolderText(QWidget *parent = 0);
    void setTextValue(const QString& NewTextValue);
    QString getTextValue();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QLineEdit *ValueEditor;
    QHBoxLayout *MainLayout;
    QLabel *ValueDisplayer;
    QString ItemValue;
};

#endif // KCISETTINGLISTITEMFOLDERTEXT_H
