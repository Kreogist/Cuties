#ifndef KCCODECOMPILEPROGRESS_H
#define KCCODECOMPILEPROGRESS_H

#include <QPropertyAnimation>
#include <QProgressBar>
#include <QWidget>

class KCCodeCompileProgress : public QWidget
{
    Q_OBJECT
public:
    explicit KCCodeCompileProgress(QWidget *parent = 0);

signals:

public slots:
    void animeShow();
    void animeHide();

private:
    QProgressBar *compileProgressDisplay;

};
#endif // KCCODECOMPILEPROGRESS_H
