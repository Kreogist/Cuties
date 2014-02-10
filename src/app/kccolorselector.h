#ifndef KCCOLORSELECTOR_H
#define KCCOLORSELECTOR_H

#include <QLineEdit>
#include <QSpinBox>
#include <QDialog>

class QBoxLayout;
class QSlider;
class QRadioButton;
class QLabel;
class QMouseEvent;
class QKeyEvent;
class QPaintEvent;
class QResizeEvent;

class KCHexColorLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KCHexColorLineEdit(QWidget *parent = 0);

signals:
    void requireSyncColor(QColor color);

public slots:
    void syncColor(const QColor &color);

private slots:
    void onTextChanged(QString value);

private:
    bool syncSentByMe=false;
    bool syncMode=false;
};

class KCHexColorEditor : public QWidget
{
    Q_OBJECT
public:
    explicit KCHexColorEditor(QWidget *parent = 0);

signals:
    void requireSyncColor(QColor color);

public slots:
    void syncColor(const QColor &color);

private:
    KCHexColorLineEdit *hexColor;
};

class KCColorDoubleBoardBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorDoubleBoardBase(QWidget *parent = 0);

signals:
    void requireUpdateColor(QColor color);

public slots:
    virtual void setColor(const QString &elementName,
                          const QColor &color);
    virtual void syncColor(const QColor &color);
    virtual void setColorCursor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);

private:
    void valueProcess(const int &x, const int &y);
    QLinearGradient hueLevelGradient;
    QLinearGradient saturationGradient;
    QLinearGradient hsvGreyGradient;
    QLinearGradient rgbHorizontalGradient;
    QLinearGradient rgbVerticalGradient;
    int cursorX=2, cursorY=2;
    int cursorSize=5;
    bool isPressed=false;
    QColor valueColor, baseColor;
    QString elementName;
    enum DoubleRenderMode
    {
        redMode,
        greenMode,
        blueMode,
        hueMode,
        saturationMode,
        valueMode,
        cyanMode,
        magentaMode,
        yellowMode,
        blackMode
    };
    DoubleRenderMode currentMode=hueMode;
};

class KCColorRingBoard : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorRingBoard(QWidget *parent = 0);

signals:
    void requireSyncColor(QColor color);

public slots:
    void syncColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int calculateLength(int posX, int posY);
    int calculateHue(int posX, int posY);
    QConicalGradient ringGradient;
    QColor currentColor;
    bool isPressed=false;
    int ringWidth=30, cursorRing=197, cursorCenter=212;
    int cursorX=409, cursorY=212;
    int cursorSize=5;
};

class KCColorHSVRing : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorHSVRing(QWidget *parent = 0);

signals:
    void requireUpdateColor(QColor color);

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
    void sliderPressed();
    void sliderReleased();

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
    int getMaximum() const;
    void setMaximum(int value);

signals:
    void requireSyncColor(QColor color);
    void sliderPressed();
    void sliderReleased();
    void valueChanged(int value);

public slots:
    void focusOnElement(QString elementName);
    void colorUpdate(const QColor &color);
    void setValue(int value);
    int getValue();

private slots:
    void slide(int position);
    void valueUpdate(int element);

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
        valueMode,
        cyanMode,
        magentaMode,
        yellowMode,
        blackMode
    };

    bool syncMode=false, syncSentByMe=false;
    int maximum=255;
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
    virtual int getValue();
    void setMaximum(const int &value);

signals:
    void requireElementChanged(QString elementName,
                               int value);
    void requireFocusOnElement(QString elementName,
                               int value);

public slots:
    virtual void syncValue(const int &value,
                           const QColor &color);
    virtual void setValue(int value);
    virtual void setEraseFocus();

private slots:
    void onActionClickElement();

protected:
    virtual void buildSlider();
    QBoxLayout *mainLayout;
    QRadioButton *elementCaption;
    KCColorSpinBox *elementSpinBox;
    KCColorLevelSelector *levelSelector;
    bool valueSetMode=false, syncMode=false;
    bool syncRequireSentByMe=false;
    bool focusSignalSent=false;
};

class KCColorSliderItemPercent : public KCColorSliderItemBase
{
    Q_OBJECT
public:
    explicit KCColorSliderItemPercent(QWidget *parent = 0);

public slots:
    void buildSlider();
    void syncValue(const int &value,
                   const QColor &color);
    void setValue(int value);
    void setValueFromLevel(int value);

private:
    QLabel *percentCaption;
    int realMinimum=0, realMaximum=0, delta=0;
    bool signalSentByMe=false;
};

class KCColorSliderBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCColorSliderBase(QWidget *parent = 0);
    virtual KCColorSliderItemBase *addElement(const QString &name);

signals:
    void requireSyncColor(QColor color);
    void requireFocusOnElement(QString elementName,
                               int value,
                               QColor color);
    void requireClearElementsFocus();

public slots:
    virtual void onElementChanged(QString elementName,
                             int value)=0;
    virtual void syncColor(QColor color);
    virtual void focusRequire(QString elementName,
                              int value);

protected:
    virtual void syncElement()=0;
    QBoxLayout *mainLayout;
    QColor currentColor;
    bool signalSentByMe=false;
};

class KCColorSliderCMYKP : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderCMYKP(QWidget *parent = 0);
    KCColorSliderItemPercent *addElement(const QString &name);

public slots:
    void onElementChanged(QString elementName,
                     int value);
    void syncColor(QColor color);
    void focusRequire(QString elementName,
                      int value);

protected:
    void syncElement();

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
    void onElementChanged(QString elementName,
                     int value);
    void syncColor(QColor color);

protected:
    void syncElement();

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
    void onElementChanged(QString elementName,
                     int value);
    void syncColor(QColor color);

protected:
    void syncElement();

private:
    KCColorSliderItemBase *redElement,
                          *greenElement,
                          *blueElement;
};

class KCColorSliderHSV : public KCColorSliderBase
{
    Q_OBJECT
public:
    explicit KCColorSliderHSV(QWidget *parent = 0);

public slots:
    void onElementChanged(QString elementName,
                     int value);
    void syncColor(QColor color);

protected:
    void syncElement();

private:
    KCColorSliderItemBase *hueElement,
                          *saturationElement,
                          *valueElement;
    bool ignoreHue=false;
};

class KCColorSelector : public QDialog
{
    Q_OBJECT
public:
    explicit KCColorSelector(QWidget *parent = 0);
    ~KCColorSelector();
    void setOriginalColor(const QColor &color);
    void registerSelector(KCColorSliderBase *selector);
    void registerViewer(KCColorViewerBase *viewer);
    void registerLevelSelector(KCColorLevelSelector *levelSelector);
    void registerHSVRing(KCColorHSVRing *hsvRing);
    void registerHexEditor(KCHexColorEditor *editor);

signals:
    void requireSyncColor(QColor color);
    void requireSetOriginalColor(QColor color);
    void requireFocusOnElement(QString elementName,
                               int value,
                               QColor color);
    void requireClearFocus();

public slots:

private slots:

private:
    QBoxLayout *mainLayout, *colorRingLayout,
               *yayaModelLayout, *iroriModelLayout;
};

#endif // KCCOLORSELECTOR_H
