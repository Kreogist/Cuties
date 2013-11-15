#ifndef KCPREFERENCEEMBEDDED_H
#define KCPREFERENCEEMBEDDED_H

#include <QWidget>
#include <QString>
#include <QList>

#include "kcpreferencesuperlist.h"

#include "kcgeneralconfigure.h"
#include "kceditorconfigure.h"
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

class KCPreferenceEmbeddedEditor : public KCPreferenceSuperList
{
    Q_OBJECT
public:
    explicit KCPreferenceEmbeddedEditor(QWidget *parent = 0);

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    enum EditorTitleEnum
    {
        titleViewOptions,
        titleMultipleTabs,
        titleClipboard,
        titleCount
    };
    QString editorTitleText[titleCount];

    enum EditorBooleanEnum
    {
        booleanShowLinePanel,
        booleanUseSpaceInsteadOfTab,
        booleanItemCount
    };
    QString booleanItemCaption[booleanItemCount];

    KCEditorConfigure *instance;
};

class KCPreferenceEmbeddedCompiler : public KCPreferenceSuperList
{
    Q_OBJECT
public:
    explicit KCPreferenceEmbeddedCompiler(QWidget *parent = 0);

private:
};

class KCPreferenceEmbeddedDebugger : public KCPreferenceSuperList
{
    Q_OBJECT
public:
    explicit KCPreferenceEmbeddedDebugger(QWidget *parent = 0);

private:
};

class KCPreferenceEmbeddedFileAssociation : public KCPreferenceSuperList
{
    Q_OBJECT
public:
    explicit KCPreferenceEmbeddedFileAssociation(QWidget *parent = 0);

private:

};

#endif // KCPREFERENCEEMBEDDED_H
