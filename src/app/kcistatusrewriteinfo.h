#ifndef KCISTATUSREWRITEINFO_H
#define KCISTATUSREWRITEINFO_H

#include <QLabel>

class kciStatusRewriteInfo : public QLabel
{
    Q_OBJECT
public:
    explicit kciStatusRewriteInfo(QWidget *parent = 0);
    
    bool getTextMode() const;
    void setTextMode(bool value);

signals:
    
public slots:

private:
    QString rewriteText, unrewriteText;
    bool textMode;
};

#endif // KCISTATUSREWRITEINFO_H
