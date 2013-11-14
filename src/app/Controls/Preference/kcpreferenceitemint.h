#ifndef KCPREFERENCEITEMINT_H
#define KCPREFERENCEITEMINT_H

#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QDial>

#include "kcpreferenceitembase.h"

class KCPreferenceItemInt : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemInt(QWidget *parent = 0);
    ~KCPreferenceItemInt();
    void setOriginalValue(const QVariant &value);
    void setIntCaptionText(const QString &value);

signals:

public slots:

private slots:
    void syncValue(int newValue);
    void showEditWidget();
    void hideEditWidget();

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();

private:
    QString intCaptionText;

    QLabel *intCaption;
    QHBoxLayout *intLayout, *dialLayout, *intSliderLayout;
    QSpinBox *intSpinValueChanger;
    QSlider *intSliderValueChanger;
    QDial *intDialValueChanger;
};

#endif // KCPREFERENCEITEMINT_H
