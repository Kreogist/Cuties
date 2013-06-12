#include "highlightrulesprovider.h"

highlightRulesProvider* highlightRulesProvider::instance=nullptr;

highlightRulesProvider* highlightRulesProvider::getInstance()
{
    if(instance == nullptr)
    {
        return instance=new highlightRulesProvider;
    }
    else
    {
        return instance;
    }
}

highlightRulesProvider::highlightRulesProvider()
{

}
