#ifndef KCPREFERENCE_H
#define KCPREFERENCE_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QTimeLine>

#include "kclistbutton.h"

enum KCPreferenceCategory
{
    KCPreferenceGerneral,
    KCPreferenceEditor,
    KCPreferenceCompiler,
    KCPreferenceDebugger,
    KCPreferenceFileAssociation,
    KCPreferenceLanguage,
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

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QLabel *categoryIcon, *categoryCaption;
    QPalette pal;
    QColor normalColor, changedColor, hoverColor, pushColor;
    QTimeLine *fadeOutAnimation;
    bool categoryChanged, categoryPressed;
};

class KCPreferenceCategoryList : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceCategoryList(QWidget *parent = 0);

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    void listSelectChangedEvent(int listIndex);

private:
    QString categoryCaptions[KCCategoryCount];
    int currentCategory;

    KCPreferenceListButton *categoryButton[KCCategoryCount];
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
    //Translate Strings
    QString titleText;
};

#endif // KCPREFERENCE_H
