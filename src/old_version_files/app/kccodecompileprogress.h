#ifndef KCCODECOMPILEPROGRESS_H
#define KCCODECOMPILEPROGRESS_H

#include <QPropertyAnimation>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>
#include <QTimer>

class KCCodeCompileProgress : public QWidget
{
    Q_OBJECT
public:
    explicit KCCodeCompileProgress(QWidget *parent = 0);
    void countToCompile();
    void regeometry(int w);
    enum CompileState
    {
        certifyCompile,
        checkingCompiler,
        runningCompiler,
        compileSuccess,
        errorEnumBegin,
        errorCantFindCompiler,
        errorCompileError,
        CompileStateCount
    };
    void setCompileState(CompileState stateValue);

signals:
    void requireCompile();

public slots:
    void setText(const QString &text);
    void setValue(const int &value);
    void showCompileSuccess();
    void showCompileError(int errors);
    void delayHide();
    void animeShow();
    void animeHide();

private slots:
    void refreshTimemout();

private:
    void setProgressColor(QColor color);
    CompileState currentState;

    QTimer *timeoutCounter;
    QProgressBar *compileProgressDisplay;
    QLabel *compileProgressText;
    QPropertyAnimation *animation;
    QMetaObject::Connection hideConnection;
    QColor progressColor, originalColor;
    QPalette progressPal;

    static int compileProgressWidth;
    static int compileProgressHeight;
};
#endif // KCCODECOMPILEPROGRESS_H
