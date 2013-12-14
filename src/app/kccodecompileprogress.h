#ifndef KCCODECOMPILEPROGRESS_H
#define KCCODECOMPILEPROGRESS_H

#include <QPropertyAnimation>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

class KCCodeCompileProgress : public QWidget
{
    Q_OBJECT
public:
    explicit KCCodeCompileProgress(QWidget *parent = 0);

signals:

public slots:
    void setText(const QString &text);
    void setValue(const int &value);
    void animeShow();
    void animeHide();

private:
    QProgressBar *compileProgressDisplay;
    QLabel *compileProgressText;
};
#endif // KCCODECOMPILEPROGRESS_H
