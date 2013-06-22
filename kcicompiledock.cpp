#include "kcicompiledock.h"

kcicompiledock::kcicompiledock(QWidget *parent):
    QDockWidget(parent)
{
    QTreeView *trevwCompileInfo=new QTreeView(this);
    setContentsMargins(0,0,0,0);
    setWidget(trevwCompileInfo);
}
