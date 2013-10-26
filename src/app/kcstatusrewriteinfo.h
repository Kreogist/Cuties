#ifndef KCSTATUSREWRITEINFO_H
#define KCSTATUSREWRITEINFO_H

#include <QLabel>

class KCStatusRewriteInfo : public QLabel
{
    Q_OBJECT
public:
    explicit KCStatusRewriteInfo(QWidget *parent = 0);

    bool getTextMode() const;
    void setTextMode(bool value);

signals:

public slots:

private:
    QString rewriteText, unrewriteText;
    bool textMode;
};

#endif // KCSTATUSREWRITEINFO_H
