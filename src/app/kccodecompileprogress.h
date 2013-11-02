#ifndef KCCODECOMPILEPROGRESS_H
#define KCCODECOMPILEPROGRESS_H

#include <QProgressBar>
#include <QWidget>

class KCCodeCompileProgress : public QWidget
{
    Q_OBJECT
public:
    explicit KCCodeCompileProgress(QWidget *parent = 0);

signals:

public slots:

private:
    QProgressBar *compileProgressDisplay;

};
#endif // KCCODECOMPILEPROGRESS_H
