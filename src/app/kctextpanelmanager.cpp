#include "kctextpanelmanager.h"

KCTextPanelManager::KCTextPanelManager(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    layout=new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setLayout(layout);
}

void KCTextPanelManager::addPanel(KCTextPanel *panel)
{
    connect(panel, &KCTextPanel::requireRepaintLineNumber,
            this, &KCTextPanelManager::requirePaintPanel);
    connect(panel, &KCTextPanel::requireUpdateAllPanel,
            this, &KCTextPanelManager::updateAllPanel);
    layout->addWidget(panel);
}

int KCTextPanelManager::resizePanel(int lineNumberPanelWidth)
{
    int panelCount=layout->count(), managerWidth=0;
    while(panelCount--)
    {
        KCTextPanel *panel=static_cast<KCTextPanel *>(layout->itemAt(panelCount)->widget());
        panel->setPanelWidth(lineNumberPanelWidth);
        managerWidth+=panel->width();
    }
    setFixedWidth(managerWidth);
    return managerWidth;
}

void KCTextPanelManager::updateAllPanel()
{
    int panelCount=layout->count();
    while(panelCount--)
    {
        layout->itemAt(panelCount)->widget()->update();
    }
}
