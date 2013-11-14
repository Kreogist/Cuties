#ifndef KCPREFERENCEEMBEDDED_H
#define KCPREFERENCEEMBEDDED_H

#include <QWidget>
#include <QString>
#include <QList>

#include "kcpreferencesuperlist.h"

#include "kcgeneralconfigure.h"
#include "kchistoryconfigure.h"

class KCPreferenceEmbeddedGeneral : public KCPreferenceSuperList
{
    Q_OBJECT
public:
    explicit KCPreferenceEmbeddedGeneral(QWidget *parent = 0);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    enum GeneralTitleEnum
    {
        titleEnvironment,
        titleAutomaticRemember,
        titleHistory,
        titleSearchOptions,
        titleCount
    };
    QString generalTitleText[titleCount];

    enum GeneralComboItem
    {
        comboDefaultProgrammingLanguage,
        comboSearchEngine,
        comboItemCount
    };
    QString comboItemCaption[comboItemCount];
    QList<QString> comboItemText[comboItemCount];

    enum GeneralBooleanItem
    {
        booleanUseDefaultLanguageOnOpen,
        booleanUseDefaultLanguageOnSave,
        booleanAutoOpenUnclosed,
        booleanItemCount
    };
    QString booleanItemCaption[booleanItemCount];

    enum GeneralIntItem
    {
        intItemHistoryMax,
        intItemCount
    };
    QString intItemCaption[intItemCount];

    KCGeneralConfigure *instance;
};

#endif // KCPREFERENCEEMBEDDED_H
