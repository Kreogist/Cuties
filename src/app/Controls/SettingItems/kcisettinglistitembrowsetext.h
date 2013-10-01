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
    void setValue(const QString &NewTextValue);
    QString getValue();
    bool getFolderMode() const;
    void setFolderMode(bool value);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);

private slots:
    void getFolderPath();
    void setEditModeEnabled();

private:
    QLineEdit *ValueEditor;
    QHBoxLayout *MainLayout;
    QLabel *ValueDisplayer;
    QString ItemValue;
    QToolButton *browseFolder;
    bool folderMode, blnEditMode;
};

#endif // KCISETTINGLISTITEMFOLDERTEXT_H
