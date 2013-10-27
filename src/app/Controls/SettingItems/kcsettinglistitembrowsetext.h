#ifndef KCSETTINGLISTITEMFOLDERTEXT_H
#define KCSETTINGLISTITEMFOLDERTEXT_H

#include <QToolButton>
#include <QFileDialog>

#include "kcsettingcontrollineedit.h"
#include "kcsettinglistitembase.h"

class KCSettingListItemBrowseText : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemBrowseText(QWidget *parent = 0);
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
    KCSettingControlLineEdit *valueEditor;
    QHBoxLayout *mainLayout;
    QLabel *valueDisplayer;
    QString itemValue;
    QToolButton *browseFolder;
    bool folderMode, editMode;
};

#endif // KCSETTINGLISTITEMFOLDERTEXT_H
