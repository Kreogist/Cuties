#ifndef KCIPLAINTEXTBROWSER_H
#define KCIPLAINTEXTBROWSER_H

#include <QPlainTextEdit>
#include <QScrollBar>

class kciPlainTextBrowser : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit kciPlainTextBrowser(QWidget *parent = 0);
    
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

#endif // KCIPLAINTEXTBROWSER_H
