#ifndef KCPREFERENCE_H
#define KCPREFERENCE_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QTimeLine>
#include <QToolButton>

#include "kclistbutton.h"
#include "kcpreferencepager.h"

enum KCPreferenceCategory
{
    KCPreferenceGerneral,
    KCPreferenceEditor,
    KCPreferenceCompiler,
    KCPreferenceDebugger,
    KCPreferenceFileAssociation,
    KCCategoryCount
};

class KCPreferenceBannerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceBannerWidget(QWidget *parent = 0);

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    QLabel *titleCaption;
    QString titleCaptionText;
};

class KCPreferenceListButton : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceListButton(QWidget *parent = 0);
    void setCategoryIcon(const QString &fileName);
    void setCategoryTitle(const QString &text);
    void setChangedState(const bool &state);
    bool getCategoryPressed() const;
    void setCategoryPressed(bool value);

signals:
    void categorySelected();

public slots:
    void fadeMeOut();

private slots:
    void changeBackAlpha(int newAlpha);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QLabel *categoryIcon, *categoryCaption;
    QPalette pal;
    int normalAlpha, changedAlpha, hoverAlpha, pushAlpha;
    QColor backgroundColor;
    QTimeLine *fadeOutAnimation;
    bool categoryChanged, categoryPressed;
};

class KCPreferenceCategoryList : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceCategoryList(QWidget *parent = 0);

signals:
    void categoryChanged(int newCategoryIndex);

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void listSelectChangedEvent(int listIndex);

private:
    QString categoryCaptions[KCCategoryCount];
    int currentCategory;

    KCPreferenceListButton *categoryButton[KCCategoryCount];
};

class KCPreferenceContents : public KCPreferencePager
{
public:
    explicit KCPreferenceContents(QWidget *parent = 0);

private:

};

class KCPreferenceCommander : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceCommander(QWidget *parent = 0);

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    QHBoxLayout *commanderLayout;
    enum commanderEnum
    {
        commanderYes,
        commanderCancel,
        commanderApply,
        commanderCount
    };
    QToolButton *commanderControls[commanderCount];
    QString commanderTitle[commanderCount];
};

class KCPreference : public QDialog
{
    Q_OBJECT
public:
    explicit KCPreference(QWidget *parent = 0);
    ~KCPreference();

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    //Layouts.
    QHBoxLayout *contentLayout;
    //Widgets:
    KCPreferenceBannerWidget *bannerWidget;
    KCPreferenceCategoryList *categoryList;
    KCPreferenceContents *contents;
    KCPreferenceCommander *commander;
    //Translate Strings
    QString titleText;
};

#endif // KCPREFERENCE_H
