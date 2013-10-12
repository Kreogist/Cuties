#ifndef KCPLAINTEXTBROWSER_H
#define KCPLAINTEXTBROWSER_H

#include <QPlainTextEdit>
#include <QScrollBar>

class KCPlainTextBrowser : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit KCPlainTextBrowser(QWidget *parent = 0);

signals:

public slots:
    void scrollToEnd();

private slots:
    void onScrollValueChanged(int value);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    bool autoScrollEnabled;
    QMetaObject::Connection autoScrollHandle;
};

#endif // KCPLAINTEXTBROWSER_H
