#include "kcpreferenceembedded.h"
#include "kclanguageconfigure.h"

KCPreferenceEmbeddedGeneral::KCPreferenceEmbeddedGeneral(QWidget *parent) :
    KCPreferenceSuperList(parent)
{
    //Get translate
    retranslate();

    //Get configure settings
    instance=KCGeneralConfigure::getInstance();

    generalTitles[titleEnvironment]=addTitle(generalTitleText[titleEnvironment]);
    generalCombos[comboDefaultProgrammingLanguage]=
        addItemCombo(comboItemCaption[comboDefaultProgrammingLanguage],
                     comboItemText[comboDefaultProgrammingLanguage],
                     instance->getDefaultLanguageMode());
    generalBooleans[booleanUseDefaultLanguageOnOpen]=
        addItemBoolean(booleanItemCaption[booleanUseDefaultLanguageOnOpen],
                       instance->getUseDefaultLanguageWhenOpen());
    generalBooleans[booleanUseDefaultLanguageOnSave]=
        addItemBoolean(booleanItemCaption[booleanUseDefaultLanguageOnSave],
                       instance->getUseDefaultLanguageWhenSave());
    generalTitles[titleAutomaticRemember]=addTitle(generalTitleText[titleAutomaticRemember]);
    generalBooleans[booleanAutoOpenUnclosed]=
        addItemBoolean(booleanItemCaption[booleanAutoOpenUnclosed],
                       instance->getRememberUnclosedFile());
    generalTitles[titleHistory]=addTitle(generalTitleText[titleHistory]);
    generalInts[intItemHistoryMax]=
        addItemInt(intItemCaption[intItemHistoryMax],
                   KCHistoryConfigure::getInstance()->getMaxRecentFilesSize(),
                   100,
                   4);
    generalTitles[titleSearchOptions]=addTitle(generalTitleText[titleSearchOptions]);
    generalCombos[comboSearchEngine]=
        addItemCombo(comboItemCaption[comboSearchEngine],
                     comboItemText[comboSearchEngine],
                     instance->getSearchEngineIndex());
    addStretch();
}

void KCPreferenceEmbeddedGeneral::retranslate()
{
    generalTitleText[titleEnvironment]=QString(" " + tr("Envronment"));
    generalTitleText[titleAutomaticRemember]=QString(" " + tr("Automatic Remember"));
    generalTitleText[titleHistory]=QString(" " + tr("History"));
    generalTitleText[titleSearchOptions]=QString(" " + tr("Search Options"));

    comboItemCaption[comboDefaultProgrammingLanguage]=tr("Default Programming Language:");
    comboItemText[comboDefaultProgrammingLanguage].clear();
    comboItemText[comboDefaultProgrammingLanguage].append(tr("Plain Text"));
    comboItemText[comboDefaultProgrammingLanguage].append(tr("C"));
    comboItemText[comboDefaultProgrammingLanguage].append(tr("C++"));
    comboItemText[comboDefaultProgrammingLanguage].append(tr("Pascal"));

    comboItemCaption[comboSearchEngine]=tr("Online Search Engine:");
    comboItemText[comboSearchEngine].clear();
    QList<searchEngine> searchEngines=KCGeneralConfigure::getInstance()->getSearchEngineList();
    for(int i=0; i<searchEngines.count(); i++)
    {
        comboItemText[comboSearchEngine].append(searchEngines[i].name);
    }

    booleanItemCaption[booleanUseDefaultLanguageOnOpen]=tr("Auto select default language file suffix when opening files:");
    booleanItemCaption[booleanUseDefaultLanguageOnSave]=tr("Auto select default language file suffix when saving a file:");
    booleanItemCaption[booleanAutoOpenUnclosed]=tr("Restore files when quitting and re-opening files:");

    intItemCaption[intItemHistoryMax]=tr("Maximum History Tracking Items:");
}

void KCPreferenceEmbeddedGeneral::retranslateAndSet()
{
    //Re-translate strings.
    retranslate();

    //Reset title strings.
    int i;
    for(i=titleEnvironment; i<titleCount; i++)
    {
        generalTitles[titleEnvironment]->setText(generalTitleText[i]);
    }

    //Reset combo items.
    for(i=comboDefaultProgrammingLanguage; i<comboItemCount; i++)
    {
        generalCombos[i]->setComboCaptionText(comboItemCaption[i]);
        generalCombos[i]->setComboTextList(comboItemText[i]);
        generalCombos[i]->refreshComboText();
    }

    //Reset
}

void KCPreferenceEmbeddedGeneral::applyPreference()
{
    //Set each value
    //Default Language
    instance->setDefaultLanguageMode(generalCombos[comboDefaultProgrammingLanguage]->getCurrentValue().toInt());
    //Default use default language suffix
    instance->setUseDefaultLanguageWhenOpen(generalBooleans[booleanUseDefaultLanguageOnOpen]->getCurrentValue().toBool());
    instance->setUseDefaultLanguageWhenSave(generalBooleans[booleanUseDefaultLanguageOnSave]->getCurrentValue().toBool());
    //Set automatic remember
    instance->setRememberUnclosedFile(generalBooleans[booleanAutoOpenUnclosed]->getCurrentValue().toBool());
    //Set history max
    KCHistoryConfigure::getInstance()->setMaxRecentFilesSize(generalInts[intItemHistoryMax]->getCurrentValue().toInt());
}


KCPreferenceEmbeddedEditor::KCPreferenceEmbeddedEditor(QWidget *parent):
    KCPreferenceSuperList(parent)
{
    //Get Translate
    retranslate();

    //Get configure settings
    instance=KCEditorConfigure::getInstance();

    addTitle(editorTitleText[titleViewOptions]);
    addItemBoolean(booleanItemCaption[booleanShowLinePanel],
                   instance->getLineNumVisible());

    KCPreferenceItemBooleanGroup *tabSpacingItem=
    addItemBooleanGroup(booleanItemCaption[booleanUseSpaceInsteadOfTab],
                        instance->usingBlankInsteadTab());
    tabSpacingItem->addTrueValueGroupItem(addItemInt(intItemCaption[intSpacePerTab],
                                                     instance->getSpacePerTab()));
    tabSpacingItem->addFalseValueGroupItem(addItemInt(intItemCaption[intTabSpacing],
                                                      instance->getTabWidth()));
    addItemCombo(comboItemCaption[comboWordWrapMode],
                 comboItemText[comboWordWrapMode],
                 instance->getWrapModeInt());
    addItemInt(intItemCaption[intCursorWidth],
               instance->getCursorWidth());

    addTitle(editorTitleText[titleMultipleTabs]);
    addItemBoolean(booleanItemCaption[booleanTabMoveable],
                   instance->getTabMoveable());
    addItemBoolean(booleanItemCaption[booleanTabCloseable],
                   instance->getTabCloseable());

    addTitle(editorTitleText[titleClipboard]);
    addItemInt(intItemCaption[intClipboardTrackingMax],
               KCClipboard::getInstance()->getMaxDataCount(),
               100,
               5);
    addStretch();
}

void KCPreferenceEmbeddedEditor::retranslate()
{
    editorTitleText[titleViewOptions]=QString(" " + tr("View Option"));
    editorTitleText[titleMultipleTabs]=QString(" " + tr("Multiple Tabs Option"));
    editorTitleText[titleClipboard]=QString(" " + tr("Clipboard"));

    booleanItemCaption[booleanShowLinePanel]=tr("Show code line panel:");
    booleanItemCaption[booleanUseSpaceInsteadOfTab]=tr("Use space instead of tab:");
    booleanItemCaption[booleanTabMoveable]=tr("Tab moving:");
    booleanItemCaption[booleanTabCloseable]=tr("Tab closing:");

    intItemCaption[intTabSpacing]=tr("Tab Spacing:");
    intItemCaption[intSpacePerTab]=tr("Space per tab:");
    intItemCaption[intCursorWidth]=tr("Cursor Width:");
    intItemCaption[intClipboardTrackingMax]=tr("Maximum Clipboard Tracking Items:");

    comboItemCaption[comboWordWrapMode]=tr("Word Wrap Mode:");
    comboItemText[comboWordWrapMode].clear();
    comboItemText[comboWordWrapMode].append(tr("No word wrapped"));
    comboItemText[comboWordWrapMode].append(tr("Wrapped at word boundaries"));
    comboItemText[comboWordWrapMode].append(tr("Wrapped at any point"));
    comboItemText[comboWordWrapMode].append(tr("Wrapping at word boundary or anywhere"));
}

void KCPreferenceEmbeddedEditor::retranslateAndSet()
{
    retranslate();
}

void KCPreferenceEmbeddedEditor::applyPreference()
{

}

KCPreferenceEmbeddedCompiler::KCPreferenceEmbeddedCompiler(QWidget *parent) :
    KCPreferenceSuperList(parent)
{
    //Get translate
    retranslate();

    //Get configure instance
    instance=KCCompilerConfigure::getInstance();

    addTitle(compilerTitleText[titleCompilerPath]);
    compilerPathItems[pathGPPCompiler]=
        addItemPath(pathItemCaption[pathGPPCompiler],
                    instance->getGppPath());
    compilerPathItems[pathGPPCompiler]->setDialogTitle(pathItemTitleCaption[pathGPPCompiler]);
    compilerPathItems[pathGCCCompiler]=
        addItemPath(pathItemCaption[pathGCCCompiler],
                    instance->getGccPath());
    compilerPathItems[pathGCCCompiler]->setDialogTitle(pathItemTitleCaption[pathGCCCompiler]);
    compilerPathItems[pathFPCCompiler]=
        addItemPath(pathItemCaption[pathFPCCompiler],
                    instance->getFpcPath());
    compilerPathItems[pathFPCCompiler]->setDialogTitle(pathItemTitleCaption[pathFPCCompiler]);
    addStretch();
}

void KCPreferenceEmbeddedCompiler::retranslate()
{
    compilerTitleText[titleCompilerPath]=tr("Compiler Path");

    pathItemCaption[pathGPPCompiler]=tr("g++ Compiler:");
    pathItemCaption[pathGCCCompiler]=tr("gcc Compiler:");
    pathItemCaption[pathFPCCompiler]=tr("FPC Compiler:");

    pathItemTitleCaption[pathGPPCompiler]=tr("Browse g++ compiler");
    pathItemTitleCaption[pathGCCCompiler]=tr("Browse gcc compiler");
    pathItemTitleCaption[pathFPCCompiler]=tr("Browse fpc compiler");
}

void KCPreferenceEmbeddedCompiler::retranslateAndSet()
{
    retranslate();
}

void KCPreferenceEmbeddedCompiler::applyPreference()
{

}

KCPreferenceEmbeddedDebugger::KCPreferenceEmbeddedDebugger(QWidget *parent) :
    KCPreferenceSuperList(parent)
{
    ;
}

void KCPreferenceEmbeddedDebugger::applyPreference()
{

}

KCPreferenceEmbeddedFileAssociation::KCPreferenceEmbeddedFileAssociation(QWidget *parent) :
    KCPreferenceSuperList(parent)
{
    ;
}

void KCPreferenceEmbeddedFileAssociation::applyPreference()
{

}
