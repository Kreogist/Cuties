#ifndef KCIFILETYPE_H
#define KCIFILETYPE_H

#include <QPalette>
#include <QComboBox>
#include <QHBoxLayout>
#include <QWidget>

class kciFileType : public QWidget
{
    Q_OBJECT
public:
    explicit kciFileType(QWidget *parent = 0);

signals:

public slots:

private:
    QHBoxLayout *mainLayout;
    QComboBox *fileType;

};

#endif // KCIFILETYPE_H
