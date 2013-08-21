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
    void setTextValue(const QString& NewTextValue);
    QString getTextValue();
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
