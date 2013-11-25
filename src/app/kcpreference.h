#ifndef KCPREFERENCE_H
#define KCPREFERENCE_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QTimeLine>
#include <QToolButton>
#include <QPropertyAnimation>

#include "kclistbutton.h"
#include "kcpreferencepager.h"
#include "kcpreferenceembedded.h"
#include "kcglobal.h"

enum KCPreferenceCategory
{
    KCPreferenceGeneral,
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

signals:
    void requiredChangeLanguage();

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void refreshLanguageInfo();

private:
    QLabel *titleCaption;
    QString titleCaptionText;

    QToolButton *localeSettings;
    KCLanguageConfigure *instance;
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
    Q_OBJECT
public:
    explicit KCPreferenceContents(QWidget *parent = 0);

public slots:
    void applyAllSettings();

private:
    KCPreferenceSuperList *embeddedSuperList[KCCategoryCount];
};

class KCPreferenceCommander : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceCommander(QWidget *parent = 0);

signals:
    void requireYes();
    void requireCancel();
    void requireApply();

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

private slots:
    void yesAction();
    void cancelAction();
    void applyAction();

    void showLanguageSelector();

protected:
    void resizeEvent(QResizeEvent *e);

private:
    //Layouts.
    QHBoxLayout *contentLayout;
    //Widgets:
    KCPreferenceBannerWidget *bannerWidget;
    KCPreferenceCategoryList *categoryList;
    KCPreferenceContents *contents;
    KCPreferenceCommander *commander;
    KCPreferenceEmbeddedLanguage *languageSelector;
    //Translate Strings
    QString titleText;
    //Animation
    QPropertyAnimation *languageSelectorShow;
};

#endif // KCPREFERENCE_H
