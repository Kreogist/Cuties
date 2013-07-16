#ifndef KCICCGERNERAL_H
#define KCICCGERNERAL_H

#include <QWidget>

namespace Ui {
class kciCCGerneral;
}

class kciCCGerneral : public QWidget
{
    Q_OBJECT
    
public:
    explicit kciCCGerneral(QWidget *parent = 0);
    ~kciCCGerneral();
    
private:
    Ui::kciCCGerneral *ui;
};

#endif // KCICCGERNERAL_H
