#ifndef KCSEARCHLINETEXT_H
#define KCSEARCHLINETEXT_H

#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>

#include "kccolorconfigure.h"

class KCSearchLineText : public QWidget
{
    Q_OBJECT
public:
    explicit KCSearchLineText(QWidget *parent = 0);

signals:

public slots:

private:
    QLineEdit *searchTextBox;
    QHBoxLayout *MainLayout;
    QLabel *lblImage;

};

#endif // KCSEARCHLINETEXT_H
