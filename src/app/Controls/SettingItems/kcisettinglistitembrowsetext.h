#ifndef KCISETTINGLISTITEMFOLDERTEXT_H
#define KCISETTINGLISTITEMFOLDERTEXT_H

#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>

#include "kcisettinglistitembase.h"

class kciSettingListItemBrowseText : public kciSettingListItemBase
{
    Q_OBJECT
public:
    explicit kciSettingListItemBrowseText(QWidget *parent = 0);
    void setValue(const QString& NewTextValue);
    QString getValue();
    bool getFolderMode() const;
    void setFolderMode(bool value);

protected:
    void mousePressEvent(QMouseEvent *e);

private slots:
    void getFolderPath();

private:
    QLineEdit *ValueEditor;
    QHBoxLayout *MainLayout;
    QLabel *ValueDisplayer;
    QString ItemValue;
    QToolButton *browseFolder;
    bool folderMode;
};

#endif // KCISETTINGLISTITEMFOLDERTEXT_H
