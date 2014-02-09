#ifndef KCCOLORSELECTOR_H
#define KCCOLORSELECTOR_H

#include <QSpinBox>
#include <QDialog>

class QBoxLayout;
class QSlider;
class QRadioButton;
class QLabel;
class QMouseEvent;
class QPaintEvent;
class QResizeEvent;

class KCColorDoubleBoardBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorDoubleBoardBase(QWidget *parent = 0);

public slots:
    virtual void setColor(const QString &elementName,
                          const QColor &color);
    virtual void syncColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QRadialGradient hueLevelGradient;
    QLinearGradient saturationGradient;
    QLinearGradient hsvGreyGradient;
    QLinearGradient rgbHorizontalGradient;
    QLinearGradient rgbVerticalGradient;
    QString elementName;
    enum DoubleRenderMode
    {
        hueMode,
        saturationMode,
        valueMode,
    };
    DoubleRenderMode currentMode=hueMode;
};

class KCColorRingBoard : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorRingBoard(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QConicalGradient ringGradient;
    int ringWidth=30;
};

class KCColorHSVRing : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorHSVRing(QWidget *parent = 0);

public slots:
    void setColorMode(QString elementName,
                      int value,
                      QColor color);
    void syncColor(QColor color);

private:
    KCColorDoubleBoardBase *doubleBoard;
    KCColorRingBoard *ringBoard;
};

class KCColorLevelRenderBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorLevelRenderBase(QWidget *parent = 0);

signals:
    void valueChanged(int value);

public slots:
    void renderRed(const QColor &color);
    void renderGreen(const QColor &color);
    void renderBlue(const QColor &color);
    void renderHue(const QColor &color);
    void renderSaturation(const QColor &color);
    void renderValue(const QColor &color);
    void renderLightness(const QColor &color);
    void renderCyan(const QColor &color);
    void renderMagenta(const QColor &color);
    void renderYellow(const QColor &color);
    void renderBlack(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QLinearGradient levelGradient;
    bool isPressed=false;
};

class KCColorLevelSelector : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorLevelSelector(QWidget *parent = 0);

signals:
    void requireSyncColor(QColor color);

public slots:
    void focusOnElement(QString elementName,
                        int value,
                        QColor color);
    void syncColor(QColor color);

private slots:
    void slide(int position, int maximum=255);
    void colorUpdate(int element);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    enum RenderMode
    {
        redMode,
        greenMode,
        blueMode,
        hueMode,
        saturationMode,
        lightnessMode,
        valueMode,
        cyanMode,
        magentaMode,
        yellowMode,
        blackMode
    };

    bool syncMode=false, syncSentByMe=false;
    RenderMode currentMode;
    KCColorLevelRenderBase *colorRender;
    QColor currentColor;
    QLabel *colorSelector;
};

class KCColorSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit KCColorSpinBox(QWidget *parent = 0);

signals:
    void spinPressed();

protected:
    void mousePressEvent(QMouseEvent *event);
};

class KCColorViewerBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorViewerBase(QWidget *parent = 0);

public slots:
    virtual void setOriginalColor(QColor color);
    virtual void setCurrentColor(QColor color);

protected:
    virtual void buildViewer();
    QPalette currentPalette;
    QWidget *currentViewer;
    QWidget *originalViewer;
    QBoxLayout *mainLayout;
};

class KCColorSliderItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorSliderItemBase(QWidget *parent = 0,
                                   bool autoBuild = true);
    virtual void setCaption(const QString &value);
    virtual void setMinimum(const int &value);
    virtual void setMaximum(const int &value);
    virtual void setRange(const int &minimumValue,
                          const int &maximumValue);
    int getValue();

signals:
    void requireElementChanged(QString elementName,
                               int value);
    void requireFocusOnElement(QString elementName,
                               int value);

public slots:
    virtual void syncValue(const int &value);
    virtual void setValue(int value);
    virtual void setEraseFocus();

private slots:
    void onActionClickElement();

protected:
    virtual void buildSlider();
    QBoxLayout *mainLayout;
    QRadioButton *elementCaption;
    KCColorSpinBox *elementSpinBox;
    QSlider *elementSlider;
    bool syncMode=false;
    bool focusSignalSent=false;
};

class KCColorSliderItemPercent : public KCColorSliderItemBase
{
    Q_OBJECT
public:
    explicit KCColorSliderItemPercent(QWidget *parent = 0);
    void setRealRange(int min, int max);
    int getOriginalValue();

public slots:
    void buildSlider();
    void syncValue(const int &value);
    void setValue(int value);
    void syncOriginalValue(const int &value);
    void setOriginalValue(int value);

private:
    int calculateValue(int percent);
    QLabel *percentCaption;
    int realMinimum=0, realMaximum=0, delta=0;
    bool signalSentByMe=false;
};

class KCColorSliderBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorSliderBase(QWidget *parent = 0);
    virtual KCColorSliderItemBase *addElement(const QString &name,
                                              const int &min,
                                              const int &max);

signals:
    void requireSyncColor(QColor color);
    void requireFocusOnElement(QString elementName,
                               int value,
                               QColor color);
    void requireClearElementsFocus();

public slots:
    virtual void syncElement(QString elementName,
                             int value)=0;
    virtual void syncColor(QColor color);
    virtual void focusRequire(QString elementName,
                              int value);

protected:
    QBoxLayout *mainLayout;
    QColor currentColor;
    bool signalSentByMe=false;
};

class KCColorSliderCMYKP : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderCMYKP(QWidget *parent = 0);
    KCColorSliderItemPercent *addElement(const QString &name,
                                         const int &min,
                                         const int &max);

public slots:
    void syncElement(QString elementName,
                     int value);
    void syncColor(QColor color);
    void focusRequire(QString elementName,
                      int value);

private:
    KCColorSliderItemPercent *cyanElement,
                             *magentaElement,
                             *yellowElement,
                             *blackElement;
};

class KCColorSliderCMYK : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderCMYK(QWidget *parent = 0);

public slots:
    void syncElement(QString elementName,
                     int value);
    void syncColor(QColor color);

private:
    KCColorSliderItemBase *cyanElement,
                          *magentaElement,
                          *yellowElement,
                          *blackElement;
};

class KCColorSliderRGB : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderRGB(QWidget *parent = 0);

public slots:
    void syncElement(QString elementName,
                     int value);
    void syncColor(QColor color);

private:
    KCColorSliderItemBase *redElement,
                          *greenElement,
                          *blueElement;
};

class KCColorSliderHSL : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderHSL(QWidget *parent = 0);

public slots:
    void syncElement(QString elementName,
                     int value);
    void syncColor(QColor color);

private:
    KCColorSliderItemBase *hueElement,
                          *saturationElement,
                          *lightnessElement;
};

class KCColorSliderHSV : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderHSV(QWidget *parent = 0);

public slots:
    void syncElement(QString elementName,
                     int value);
    void syncColor(QColor color);

private:
    KCColorSliderItemBase *hueElement,
                          *saturationElement,
                          *valueElement;
};

class KCColorSelector : public QDialog
{
    Q_OBJECT
public:
    explicit KCColorSelector(QWidget *parent = 0);
    ~KCColorSelector();
    void registerSelector(KCColorSliderBase *selector);
    void registerViewer(KCColorViewerBase *viewer);
    void registerLevelSelector(KCColorLevelSelector *levelSelector);
    void registerHSVRing(KCColorHSVRing *hsvRing);

signals:
    void requireSyncColor(QColor color);
    void requireFocusOnElement(QString elementName,
                               int value,
                               QColor color);
    void requireClearFocus();

public slots:

private slots:

private:
    QBoxLayout *mainLayout, *colorRingLayout,
               *iroriModelLayout, *yayaModelLayout;
};

#endif // KCCOLORSELECTOR_H
