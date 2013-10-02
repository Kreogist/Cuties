#ifndef KCFILETYPE_H
#define KCFILETYPE_H

#include <QPalette>
#include <QComboBox>
#include <QHBoxLayout>
#include <QWidget>

class KCFileType : public QWidget
{
    Q_OBJECT
public:
    explicit KCFileType(QWidget *parent = 0);

signals:

public slots:

private:
    QHBoxLayout *mainLayout;
    QComboBox *fileType;

};

#endif // KCFILETYPE_H
