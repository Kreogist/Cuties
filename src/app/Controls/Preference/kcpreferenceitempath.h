#ifndef KCPREFERENCEITEMPATH_H
#define KCPREFERENCEITEMPATH_H

#include <QLineEdit>
#include <QPushButton>

#include "kcpreferenceitembase.h"

class KCPreferenceItemPath : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemPath(QWidget *parent = 0);
    ~KCPreferenceItemPath();
    void setOriginalValue(const QVariant &value);
    void setPathText(const QString &value);
    void setPathCaptionText(const QString &value);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);

private:
    QString pathText,
            browseText;

    QHBoxLayout *pathLayout;
    QLabel *pathCaption;
    QLineEdit *filePathData;
    QPushButton *browseFileAction;
};

#endif // KCPREFERENCEITEMPATH_H
