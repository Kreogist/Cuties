#ifndef KCPREFERENCEEMBEDDED_H
#define KCPREFERENCEEMBEDDED_H

#include <QWidget>

#include "kcpreferencesuperlist.h"

class KCPreferenceEmbeddedGeneral : public KCPreferenceSuperList
{
    Q_OBJECT
public:
    explicit KCPreferenceEmbeddedGeneral(QWidget *parent = 0);

signals:

public slots:

};

#endif // KCPREFERENCEEMBEDDED_H
