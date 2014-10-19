#ifndef KCPREFERENCEITEMCOLOR_H
#define KCPREFERENCEITEMCOLOR_H

#include "kcpreferenceitembase.h"

class QLabel;
class QMouseEvent;
class QPushButton;

class KCPreferenceColorViewer : public QLabel
{
    Q_OBJECT
public:
    explicit KCPreferenceColorViewer(QWidget *parent = 0);
    void setColor(const QColor &value);

signals:
    void viewerClicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint pointer;
    QPalette pal;
};

class KCPreferenceColorLabel : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceColorLabel(QWidget *parent = 0);

    QColor getCurrentColor() const;
    void setCurrentColor(const QColor &value);

signals:
    void colorChanged(QColor color);

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void onActionBrowseColor();

private:
    QPushButton *selectColor;
    KCPreferenceColorViewer *viewer;
    QBoxLayout *colorLayout;
    QColor currentColor;
    QString selectColorCaption;
};

class KCPreferenceItemColor : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemColor(QWidget *parent = 0);
    ~KCPreferenceItemColor();
    void setOriginalValue(const QVariant &value);
    void setColorCaptionText(const QString &value);

signals:

public slots:
    void retranslateAndSet();

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private:
    QString getColorString(const QColor &value) const;
    QLabel *colorCaption;
    QBoxLayout *colorLayout;
    KCPreferenceColorLabel *colorData;
};

#endif // KCPREFERENCEITEMCOLOR_H
