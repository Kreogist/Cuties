/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCWELCOMEWINDOW_H
#define KCWELCOMEWINDOW_H

#include <QStackedWidget>
#include <QModelIndex>
#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QToolButton;
class QListView;

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
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

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

signals:
    void requiredNewFile(QString fileSuffix);

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

signals:
    void requiredOpenFile();

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void setBackgroundAlpha(int newAlpha);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QLabel *openFileCaption;
    QString openFileTitleCaption;
    QPalette pal;

    QColor backgroundColor;
};

class KCWelcomeWindowHistoryList : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindowHistoryList(QWidget *parent = 0);
    ~KCWelcomeWindowHistoryList();

signals:
    void requiredOpenFile();
    void requiredOpenRecentFile(QString filePath);

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void dblClickHistoryItems(QModelIndex itemIndex);

private:
    QListView *recentListWidget;
    QString recentTitle;
    QVBoxLayout *recentWidgetLayout;
    KCWelcomeWindowOpenFile *openFileBanner;
    QLabel *recentCaption;
};

class KCWelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit KCWelcomeWindow(QWidget *parent = 0);
    ~KCWelcomeWindow();

signals:
    void requiredNewFile(QString fileSuffix);
    void requiredOpenFile();
    void requiredOpenRecentFile(QString fileName);

public slots:
    void retranslateAndSet();

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QHBoxLayout *contentsLayout;
    QVBoxLayout *captionLayout;
    QLabel *bannerBackground;

    KCWelcomeWindowNewFile *newFileContentWidget;
    KCWelcomeWindowHistoryList *openFileContentWidget;
};

#endif // KCWELCOMEWINDOW_H
