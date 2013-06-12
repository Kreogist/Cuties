#ifndef HIGHLIGHTRULESPROVIDER_H
#define HIGHLIGHTRULESPROVIDER_H

#include <QObject>
#include <QList>

//This is a Single Ton



class highlightRulesProvider : public QObject
{
    Q_OBJECT

public:
    highlightRulesProvider* getInstance();
    
signals:
    void highlightRuleChanged();
    
public slots:

private:
    highlightRulesProvider();

    static highlightRulesProvider *instance;

    void generateCppRules();
};

#endif // HIGHLIGHTRULESPROVIDER_H
