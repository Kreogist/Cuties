#ifndef KCWELCOMEWINDOW_H
#define KCWELCOMEWINDOW_H

#include <QStackedWidget>
#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QToolButton;

class KCWelcomeWindowNewFileButton : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindowNewFileButton(QWidget *parent = 0);
    void setImage(const QString &filePath);
    void setText(const QString &buttonCaption);
    void setFileSuffix(const QString &newFileSuffix);
    void setEmitFileSuffix(const QString &value);
    void setBackgroundColor(const QColor &value);

signals:
    void requiredNewFile(QString fileSuffix);

private slots:
    void setBackgroundAlpha(int newAlpha);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    QColor backgroundColor;
    QPalette pal;
    QHBoxLayout *buttonLayout;
    QLabel *imageLabel, *textLabel;
    QString emitFileSuffix;
};

class KCWelcomeWindowNewFile : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindowNewFile(QWidget *parent = 0);

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    enum NewFileSuffix
    {
        plainTextType,
        cppType,
        cType,
        pascalType,
        NewFileSuffixCount
    };
    KCWelcomeWindowNewFileButton *newFileButtons[NewFileSuffixCount];
    QString newFileButtonCaption[NewFileSuffixCount];

    QLabel *newFileCaption;
    QString newFileTitleCaption;
};

class KCWelcomeWindowOpenFile : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindowOpenFile(QWidget *parent = 0);
    void setBackgroundColor(const QColor &value);

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void setBackgroundAlpha(int newAlpha);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    QLabel *openFileCaption;
    QString openFileTitleCaption;
    QPalette pal;

    QColor backgroundColor;
};

class KCWelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindow(QWidget *parent = 0);
    ~KCWelcomeWindow();

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QHBoxLayout *contentsLayout;
    QLabel *bannerBackground;
};

#endif // KCWELCOMEWINDOW_H
