#ifndef KCPREFERENCEITEMPATH_H
#define KCPREFERENCEITEMPATH_H

#include <QLineEdit>
#include <QPushButton>
#include <QFileInfo>
#include <QFileDialog>

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
    void setDialogTitle(const QString &newDialogTitle);
    bool getGuaranteeFileExsist() const;
    void setGuaranteeFileExsist(bool value);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();
    void heightState(bool newState);

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private slots:
    void getFilePath();

private:
    bool guaranteeFileExsist;

    QString pathText,
            browseText,
            dialogTitleText;

    QHBoxLayout *pathLayout;
    QLabel *pathCaption;
    QLineEdit *filePathData;
    QPushButton *browseFileAction;
};

#endif // KCPREFERENCEITEMPATH_H
