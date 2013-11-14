#ifndef KCPREFERENCEITEMBASE_H
#define KCPREFERENCEITEMBASE_H

#include <QVariant>
#include <QWidget>
#include <QTimeLine>
#include <QLabel>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

class KCPreferenceItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceItemBase(QWidget *parent = 0);
    QVariant getCurrentValue() const;
    void setCurrentValue(const QVariant &value);
    QVariant getOriginalValue() const;
    void setOriginalValue(const QVariant &value);
    void editFinished();
    void setExpandFinishedHeight(const int &endHeight);
    int getExpandFinishedHeight() const;

signals:
    void editFocusCapture();

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void setBackgroundAlpha(int newAlpha);
    void setItemHeight(int newHeight);
    virtual void showEditWidget()=0;
    virtual void hideEditWidget()=0;

protected:
    virtual QVariant getUserNewValue()=0;
    virtual void refreshValueDisplay()=0;
    void setOriginalDisplayVisible(bool statue);
    void mousePressEvent(QMouseEvent *e);
    bool valueChanged;
    bool editMode;
    QVariant originalValue, currentValue;
    int valueChangedAlpha;
    int expandEndHeight;
    QTimeLine *fadeMeOut;
    QTimeLine *expandAnimation;
    QTimeLine *foldAnimation;
    QPalette pal;
    QColor backgroundColor;
    QVBoxLayout *editLayout;
    QLabel *valueDisplayer, *originalValueDisplayer;
    QString originalValueIs;
};

#endif // KCPREFERENCEITEMBASE_H
