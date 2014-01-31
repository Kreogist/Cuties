/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCPREFERENCE_H
#define KCPREFERENCE_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QTimeLine>
#include <QToolButton>
#include <QPropertyAnimation>

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
    void requiredChangeLanguage();

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void listSelectChangedEvent(int listIndex);
    void refreshLanguageInfo();

private:
    QString categoryCaptions[KCCategoryCount];
    int currentCategory;

    KCPreferenceListButton *categoryButton[KCCategoryCount];
    QToolButton *localeSettings;

    KCLanguageConfigure *instance;
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
    void hideLanguageSelector();
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
    QPropertyAnimation *languageSelectorShow, *languageSelectorHide;
};

#endif // KCPREFERENCE_H
