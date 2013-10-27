#ifndef KCSETTINGLISTITEMLANGUAGEITEM_H
#define KCSETTINGLISTITEMLANGUAGEITEM_H

#include "kcsettinglistitembase.h"

class KCSettingListItemLanguageItem : public KCSettingListItemBase
{
    Q_OBJECT
public:
    explicit KCSettingListItemLanguageItem(QWidget *parent = 0);
    void setLanguageImage(QString imgFilePath);
    void setLanguageName(QString strLanName);
    void setCheck(bool value);

signals:
    void languageSelect();

protected:
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private slots:

private:
    bool languageSelected;
    QHBoxLayout *mainLayout;
    QLabel *languageIcon;
    QLabel *languageName;
    QPalette pal;
};

#endif // KCSETTINGLISTITEMLANGUAGEITEM_H
