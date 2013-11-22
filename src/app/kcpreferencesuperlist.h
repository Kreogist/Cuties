#ifndef KCPREFERENCESUPERLIST_H
#define KCPREFERENCESUPERLIST_H

#include <QFont>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QList>
#include <QResizeEvent>
#include <QSignalMapper>

#include "Controls/Preference/kcpreferenceitembase.h"
#include "Controls/Preference/kcpreferenceitemcombo.h"
#include "Controls/Preference/kcpreferenceitemboolean.h"
#include "Controls/Preference/kcpreferenceitemint.h"
#include "Controls/Preference/kcpreferenceitembooleangroup.h"
#include "Controls/Preference/kcpreferenceitempath.h"

class KCPreferenceSuperListContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceSuperListContent(QWidget *parent = 0);
    void appendTitle(QLabel *newTitleWidget);
    void appendItem(KCPreferenceItemBase *newItemWidget);
    void appendStretch();

signals:
    void changeHeight(int changedHeight);

public slots:
    void resetCurrentIndex();

private slots:
    void transferCurrentIndex(int newIndex);

private:
    int currentItemIndex;
    int originalHeight;
    QVBoxLayout *superListLayout;
    QList<QLabel *> superListTitles;
    QList<KCPreferenceItemBase *> superListItems;
    QSignalMapper *superListItemSignalProcessor;
};

class KCPreferenceSuperList : public QScrollArea
{
    Q_OBJECT
public:
    explicit KCPreferenceSuperList(QWidget *parent = 0);
    QLabel *addTitle(const QString &titleText);
    KCPreferenceItemCombo *addItemCombo(const QString &captionText,
                                        const QList<QString> &comboItemList,
                                        int defaultValue);
    KCPreferenceItemCombo *addItemCombo(KCPreferenceItemCombo *newComboItem);
    KCPreferenceItemBoolean *addItemBoolean(const QString &captionText,
                                            bool defaultValue);
    KCPreferenceItemBoolean *addItemBoolean(KCPreferenceItemBoolean *newBooleanItem);
    KCPreferenceItemInt *addItemInt(const QString &captionText,
                    int defaultValue,
                    int maxValue=100,
                    int minValue=0);
    KCPreferenceItemInt *addItemInt(KCPreferenceItemInt *newIntItem);
    KCPreferenceItemBooleanGroup *addItemBooleanGroup(const QString &captionText,
                                                      bool defaultValue);
    KCPreferenceItemPath *addItemPath(KCPreferenceItemPath *newPathItem);
    KCPreferenceItemPath *addItemPath(const QString &captionText,
                                      QString defaultValue);
    void addStretch();

signals:

public slots:
    void resetCurrentIndex();
    virtual void applyPreference()=0;

protected:
    void resizeEvent(QResizeEvent *event);
    QFont titleFont;
    KCPreferenceSuperListContent *contents;

};

#endif // KCPREFERENCESUPERLIST_H
