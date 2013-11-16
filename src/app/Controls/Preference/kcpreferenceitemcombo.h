#ifndef KCPREFERENCEITEMCOMBO_H
#define KCPREFERENCEITEMCOMBO_H

#include <QLabel>
#include <QComboBox>
#include <QList>
#include "kcpreferenceitembase.h"

class KCPreferenceItemCombo : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemCombo(QWidget *parent = 0);
    ~KCPreferenceItemCombo();
    void setOriginalValue(const QVariant &value);
    void refreshComboText();
    QList<QString> getComboTextList() const;
    void setComboTextList(const QList<QString> &value);
    void setComboCaptionText(const QString &value);

signals:

public slots:

private slots:

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private:
    QList<QString> comboTextList;

    QHBoxLayout *comboLayout;
    QLabel *comboCaption;
    QComboBox *comboData;
};

#endif // KCPREFERENCEITEMCOMBO_H
