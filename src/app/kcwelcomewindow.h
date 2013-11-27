#ifndef KCWELCOMEWINDOW_H
#define KCWELCOMEWINDOW_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class KCWelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindow(QWidget *parent = 0);
    ~KCWelcomeWindow();

signals:

public slots:

private:
    QHBoxLayout *contentsLayout;
    QVBoxLayout *newFileLayout;
};

#endif // KCWELCOMEWINDOW_H
