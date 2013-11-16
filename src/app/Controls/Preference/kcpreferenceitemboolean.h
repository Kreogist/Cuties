#ifndef KCPREFERENCEITEMBOOLEAN_H
#define KCPREFERENCEITEMBOOLEAN_H

#include <QLabel>
#include <QCheckBox>

#include "kcpreferenceitembase.h"

class KCPreferenceItemBoolean : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemBoolean(QWidget *parent = 0);
    ~KCPreferenceItemBoolean();
    void setOriginalValue(const QVariant &value);
    void refreshBooleanText();
    QString getBooleanText() const;
    void setBooleanText(const QString &value);
    void setBooleanCaptionText(const QString &value);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private:
    QString booleanText;
    QString booleanDataText,
            booleanStatusText[2];

    QHBoxLayout *booleanLayout;
    QLabel *booleanCaption;
    QCheckBox *booleanData;

    QColor enabledColor, disabledColor;
    QPalette displayPalette;
};

#endif // KCPREFERENCEITEMBOOLEAN_H
