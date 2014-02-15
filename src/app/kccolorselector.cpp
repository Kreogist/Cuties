
#include <QDebug>

#include <QDir>
#include <QPushButton>
#include <QDesktopWidget>
#include <QScreen>
#include <QWheelEvent>
#include <QStyleFactory>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QScopedPointer>
#include <QScrollBar>
#include <QDataStream>
#include <QComboBox>
#include <QFocusEvent>
#include <QStackedWidget>
#include <QGradient>
#include <QSignalMapper>
#include <QRadioButton>
#include <QSlider>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QBoxLayout>
#include <QApplication>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QRadialGradient>
#include <QPainter>
#include <QGridLayout>
#include <QKeyEvent>

#include "kccolorselector.h"

KCHexColorLineEdit::KCHexColorLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setMaxLength(6);
    setInputMask("HHHHHH;0");
    connect(this, &KCHexColorLineEdit::textChanged,
            this, &KCHexColorLineEdit::onTextChanged);
}

void KCHexColorLineEdit::onTextChanged(QString value)
{
    if(syncMode)
    {
        return;
    }
    QColor testColor;
    testColor.setNamedColor("#"+value);
    syncSentByMe=true;
    emit requireSyncColor(testColor);
}

void KCHexColorLineEdit::syncColor(const QColor &color)
{
    if(syncSentByMe)
    {
        syncSentByMe=false;
        return;
    }
    syncMode=true;
    QString currentValue=color.name().remove(0,1);
    setText(currentValue);
    syncMode=false;
}

KCHexColorEditor::KCHexColorEditor(QWidget *parent) :
    QWidget(parent)
{
    QBoxLayout *mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    QLabel *hashHint=new QLabel("#", this);
    mainLayout->addWidget(hashHint);
    hexColor=new KCHexColorLineEdit(this);
    connect(hexColor, SIGNAL(requireSyncColor(QColor)),
            this, SIGNAL(requireSyncColor(QColor)));
    mainLayout->addWidget(hexColor);
}

void KCHexColorEditor::syncColor(const QColor &color)
{
    hexColor->syncColor(color);
}

KCColorSlot::KCColorSlot(QWidget *parent) :
    QLabel(parent)
{
    setAutoFillBackground(true);
    setWordWrap(true);
    setAlignment(Qt::AlignCenter);
    pal=palette();
}

void KCColorSlot::setBackgroundColor(const QColor &color)
{
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void KCColorSlot::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    if(!text().isEmpty())
    {
        emit requireSyncColor(pal.color(QPalette::Window));
    }
}

KCColorDatabaseViewer::KCColorDatabaseViewer(QWidget *parent) :
    QWidget(parent)
{
    QBoxLayout *mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    colorLayout=new QGridLayout();
    colorLayout->setContentsMargins(0,0,0,0);
    colorLayout->setSpacing(0);
    mainLayout->addLayout(colorLayout, 1);
    colorScrollBar=new QScrollBar(Qt::Vertical, this);
    colorScrollBar->setVisible(false);
    mainLayout->addWidget(colorScrollBar);
    connect(colorScrollBar, &QScrollBar::valueChanged,
            this, &KCColorDatabaseViewer::updateColorLayout);
}

KCColorDatabaseViewer::~KCColorDatabaseViewer()
{
    colorLayout->deleteLater();
}

void KCColorDatabaseViewer::loadColorDataBase(const QString &fileName)
{
    QFile database(fileName);
    if(!database.open(QIODevice::ReadOnly))
    {
        //Failed.
        return;
    }
    QDataStream colorStream(&database);
    char header[4];
    colorStream.readRawData(header, 4);
    //The header should be checked later.
    if(header[0]!='8' || header[1]!='B' || header[2]!='C' || header[3]!='B')
    {
        //Failed.
        return;
    }
    colorStream>>bookVersion>>bookIdentifier;

    quint32 stringLength;

    colorStream>>stringLength;
    while(stringLength--)
    {
        quint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        bookTitle+=currentChar;
    }
    bookTitle=bookTitle.mid(bookTitle.indexOf("=")+1);

    colorStream>>stringLength;
    while(stringLength--)
    {
        quint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        bookPrefix+=currentChar;
    }
    bookPrefix=bookPrefix.mid(bookPrefix.indexOf("=")+1);

    colorStream>>stringLength;
    while(stringLength--)
    {
        quint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        bookSuffix+=currentChar;
    }
    bookSuffix=bookSuffix.mid(bookSuffix.indexOf("=")+1);

    colorStream>>stringLength;
    while(stringLength--)
    {
        quint16 currentUTF16Data;
        colorStream>>currentUTF16Data;
        QChar currentChar(currentUTF16Data);
        bookDescription+=currentChar;
    }
    bookDescription=bookDescription.mid(bookDescription.indexOf("=")+1);

    colorStream>>colorNumber>>pageSize>>pageOffset>>colorModel;
    switch(colorModel)
    {
    case 0:
    case 2:
    case 7:
        break;
    default:
        //Unknown color Model;
        return;
    }

    quint32 colorNameLength;
    int i,j,euqalTest;
    for(i=0; i<colorNumber; i++)
    {
        colorInfo currentColor;
        colorStream>>colorNameLength;
        while(colorNameLength--)
        {
            quint16 currentUTF16Data;
            colorStream>>currentUTF16Data;
            QChar currentChar(currentUTF16Data);
            currentColor.colorName+=currentChar;
        }
        euqalTest=currentColor.colorName.indexOf("=");
        if(euqalTest!=-1)
        {
            currentColor.colorName=currentColor.colorName.mid(euqalTest+1);
        }
        colorStream>>currentColor.code[0]>>currentColor.code[1]
                   >>currentColor.code[2]>>currentColor.code[3]
                   >>currentColor.code[4]>>currentColor.code[5];
        //Read color components.
        switch(colorModel)
        {
        case 0:
            quint8 dataRed, dataGreen, dataBlue;
            colorStream>>dataRed>>dataGreen>>dataBlue;
            currentColor.color.setRgb(dataRed, dataGreen, dataBlue);
            break;
        case 2:
            quint8 dataC, dataM, dataY, dataK;
            qreal c,m,y,k;
            colorStream>>dataC>>dataM>>dataY>>dataK;
            c=(qreal)(255-dataC)/2.55+0.5; // 0% thru 100%
            m=(qreal)(255-dataM)/2.55+0.5; // 0% thru 100%
            y=(qreal)(255-dataY)/2.55+0.5; // 0% thru 100%
            k=(qreal)(255-dataK)/2.55+0.5; // 0% thru 100%
            dataC=(quint8)(2.55*c);
            dataM=(quint8)(2.55*m);
            dataY=(quint8)(2.55*y);
            dataK=(quint8)(2.55*k);
            currentColor.color.setCmyk(dataC, dataM, dataY, dataK);
            break;
        case 7:
            quint8 dataL, dataA, dataB;
            qreal l, a, b;
            colorStream>>dataL>>dataA>>dataB;
            l=(qreal)dataL/2.55+0.5;
            a=(qreal)dataA-128;
            b=(qreal)dataB-128;
            currentColor.color=lab2rgb(l,a,b);
            break;
        }
        colorDatabase.append(currentColor);
    }

    //Prepare scroll bar.
    lineCount=colorNumber/pageSize;
    if(colorNumber%pageSize>0)
    {
        lineCount++;
    }

    if(lineCount<pageSize)
    {
        colorScrollBar->setVisible(false);
    }
    else
    {
        colorScrollBar->setVisible(true);
        colorScrollBar->setRange(0, lineCount-pageSize+1);
    }

    //Prepare labels.
    for(i=0;i<screenHeight;i++)
    {
        for(j=0;j<pageSize;j++)
        {
            KCColorSlot *colorSlot=new KCColorSlot(this);
            connect(colorSlot, &KCColorSlot::requireSyncColor,
                    this, &KCColorDatabaseViewer::requireSyncColor);
            colorLayout->addWidget(colorSlot,i,j,1,1);
            colorViewer.append(colorSlot);
        }
    }
    updateColorLayout(0);
}

void KCColorDatabaseViewer::wheelEvent(QWheelEvent *event)
{
    colorScrollBar->setValue(colorScrollBar->value()-
                             event->angleDelta().y()/56);
    QWidget::wheelEvent(event);
}

void KCColorDatabaseViewer::updateColorLayout(const int &topLine)
{
    int i,j,currentColorOffset=0, baseIndex=topLine*pageSize, currentColorIndex;
    bool indexOverflow=false;
    QString combineColorName;
    for(i=0; i<screenHeight; i++)
    {
        if(indexOverflow)
        {
            for(j=0; j<pageSize; j++)
            {
                KCColorSlot *currentColor=colorViewer.at(currentColorOffset);
                currentColor->setVisible(false);
                currentColorOffset++;
            }
            continue;
        }
        for(j=0; j<pageSize; j++)
        {
            KCColorSlot *currentColor=colorViewer.at(currentColorOffset);
            currentColorIndex=baseIndex+currentColorOffset;
            if(indexOverflow || currentColorIndex>=colorNumber)
            {
                indexOverflow=true;
                currentColor->setVisible(false);
                currentColorOffset++;
                continue;
            }
            colorInfo currentColorInfo=colorDatabase.at(currentColorIndex);
            if(currentColorInfo.colorName.isEmpty())
            {
                currentColor->setVisible(false);
            }
            else
            {
                currentColor->setVisible(true);
                combineColorName=bookPrefix+
                        currentColorInfo.colorName+
                        bookSuffix;
                currentColor->setText(combineColorName);
                currentColor->setBackgroundColor(currentColorInfo.color);
                currentColor->setToolTip(combineColorName);
            }
            currentColorOffset++;
        }
    }
    update();
}

QColor KCColorDatabaseViewer::lab2rgb(qreal L, qreal a, qreal b)
{
    qreal X, Y, Z, fX, fY, fZ;
    qreal RR, GG, BB;
    int R, G, B;

    fY = pow((L + 16.0) / 116.0, 3.0);
    if (fY < 0.008856)
    {
        fY = L / 903.3;
    }
    Y = fY;

    if (fY > 0.008856)
    {
        fY = pow(fY, 1.0/3.0);
    }
    else
    {
        fY = 7.787 * fY + 16.0/116.0;
    }

    fX = a / 500.0 + fY;
    if (fX > 0.206893)
    {
        X = pow(fX, 3.0);
    }
    else
    {
        X = (fX - 16.0/116.0) / 7.787;
    }

    fZ = fY - b /200.0;
    if (fZ > 0.206893)
    {
        Z = pow(fZ, 3.0);
    }
    else
    {
        Z = (fZ - 16.0/116.0) / 7.787;
    }

    X *= (0.950456 * 255);
    Y *=             255;
    Z *= (1.088754 * 255);

    RR =  3.240479*X - 1.537150*Y - 0.498535*Z;
    GG = -0.969256*X + 1.875992*Y + 0.041556*Z;
    BB =  0.055648*X - 0.204043*Y + 1.057311*Z;

    R = (int)(RR < 0 ? 0 : RR > 255 ? 255 : RR);
    G = (int)(GG < 0 ? 0 : GG > 255 ? 255 : GG);
    B = (int)(BB < 0 ? 0 : BB > 255 ? 255 : BB);

    QColor tempoaryColor;
    tempoaryColor.setRgb(R, G, B);
    return tempoaryColor;
}

KCColorDatabaseBrowser::KCColorDatabaseBrowser(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(424,424);
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    databaseSelector=new QComboBox(this);
    mainLayout->addWidget(databaseSelector);
    mainLayout->addStretch();

    //Load color database.
    loadColorDatabase();
}

void KCColorDatabaseBrowser::requireShowDatabase(int databaseIndex)
{
    disconnect(syncSignal);
    if(!viewer.isNull())
    {
        //KCColorDatabaseViewer might exsist.
        if(mainLayout->count()>2)
        {
            //Remove from layout.
            mainLayout->takeAt(1);
        }
    }
    viewer.take();
    viewer.reset(new KCColorDatabaseViewer);
    viewer->loadColorDataBase(databaseList.at(databaseIndex));
    syncSignal=connect(viewer.data(), &KCColorDatabaseViewer::requireSyncColor,
                       this, &KCColorDatabaseBrowser::requireSyncColor);
    mainLayout->insertWidget(1, viewer.data(), 1);
}

void KCColorDatabaseBrowser::loadColorDatabase()
{
    databaseList.clear();
    QString databaseDirPath=qApp->applicationDirPath()+"/ColorBase";
    QStringList fileFilter;
    fileFilter<<"*.acb";
    QDir databaseDir(databaseDirPath);
    if(!databaseDir.exists())
    {
        databaseSelector->setVisible(false);
        //Display not exsist.
        return;
    }
    QFileInfoList list=databaseDir.entryInfoList(fileFilter);
    QStringList listNameList;
    for(int i=0;i<list.count();i++)
    {
        QFileInfo item=list.at(i);
        if(item.fileName().length()<4)
        {
            continue;
        }
        //Add to color database
        QString testFilePath=databaseDirPath+"/"+item.fileName();
        QFile testFile(testFilePath);
        if(!testFile.open(QIODevice::ReadOnly))
        {
            //Failed try next.
            continue;
        }

        QDataStream testData(&testFile);
        char header[4];
        testData.readRawData(header, 4);
        if(header[0]!='8' || header[1]!='B' || header[2]!='C' || header[3]!='B')
        {
            //Failed try next.
            continue;
        }
        quint16 bookVersion, bookIdentifier;
        testData>>bookVersion>>bookIdentifier;
        quint32 titleLength;
        testData>>titleLength;
        QString testString;
        while(titleLength--)
        {
            quint16 currentUTF16Data;
            testData>>currentUTF16Data;
            QChar currentChar(currentUTF16Data);
            testString+=currentChar;
        }
        testString=testString.mid(testString.indexOf("=")+1);
        if(listNameList.indexOf(testString)==-1)
        {
            //Add this file to file stream.
            databaseList.append(testFilePath);
            databaseSelector->addItem(testString);
            listNameList.append(testString);
        }
    }
    if(databaseList.count()>0)
    {
        connect(databaseSelector, SIGNAL(currentIndexChanged(int)),
                this, SLOT(requireShowDatabase(int)));
        requireShowDatabase(0);
    }
}

KCColorDoubleBoardBase::KCColorDoubleBoardBase(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(259,259);
    setAutoFillBackground(true);
    hsvGreyGradient.setStart(0,0);
}

void KCColorDoubleBoardBase::setColor(const QString &elementName,
                                      const QColor &color)
{
    if(elementName=="S:")
    {
        currentMode=saturationMode;
    }
    else if(elementName=="V:")
    {
        currentMode=valueMode;
    }
    else if(elementName=="R:")
    {
        currentMode=redMode;
    }
    else if(elementName=="G:")
    {
        currentMode=greenMode;
    }
    else if(elementName=="B:")
    {
        currentMode=blueMode;
    }
    else
    {
        currentMode=hueMode;
    }
    syncColor(color);
}

void KCColorDoubleBoardBase::syncColor(const QColor &color)
{
    baseColor=color;
    QColor color0, color16, color33, color50, color66, color83, color100;
    switch(currentMode)
    {
    case saturationMode:
        saturationGradient=QLinearGradient(0,0,width(),0);
        color0.setHsv(0, color.saturation(), 255);
        color16.setHsv(60, color.saturation(), 255);
        color33.setHsv(120, color.saturation(), 255);
        color50.setHsv(180, color.saturation(), 255);
        color66.setHsv(240, color.saturation(), 255);
        color83.setHsv(300, color.saturation(), 255);
        color100.setHsv(0, color.saturation(), 255);
        saturationGradient.setColorAt(0.00, color0);
        saturationGradient.setColorAt(0.16, color16);
        saturationGradient.setColorAt(0.33, color33);
        saturationGradient.setColorAt(0.50, color50);
        saturationGradient.setColorAt(0.66, color66);
        saturationGradient.setColorAt(0.83, color83);
        saturationGradient.setColorAt(1.00, color100);
        hsvGreyGradient.setColorAt(0, QColor(0,0,0,0));
        hsvGreyGradient.setColorAt(1, QColor(0,0,0,255));
        break;
    case valueMode:
        saturationGradient=QLinearGradient(0,0,width(),0);
        color0.setHsv(0, 255, 255);
        color16.setHsv(60, 255, 255);
        color33.setHsv(120, 255, 255);
        color50.setHsv(180, 255, 255);
        color66.setHsv(240, 255, 255);
        color83.setHsv(300, 255, 255);
        color100.setHsv(0, 255, 255);
        saturationGradient.setColorAt(0.00, color0);
        saturationGradient.setColorAt(0.16, color16);
        saturationGradient.setColorAt(0.33, color33);
        saturationGradient.setColorAt(0.50, color50);
        saturationGradient.setColorAt(0.66, color66);
        saturationGradient.setColorAt(0.83, color83);
        saturationGradient.setColorAt(1.00, color100);
        hsvGreyGradient.setColorAt(0, QColor(255,255,255,0));
        hsvGreyGradient.setColorAt(1, QColor(255,255,255,255));
        valueColor=QColor(0,0,0,255-color.value());
        break;
    case redMode:
        rgbHorizontalGradient=QLinearGradient(0,0,width(),0);
        rgbHorizontalGradient.setColorAt(0,QColor(color.red(),0,0));
        rgbHorizontalGradient.setColorAt(1,QColor(color.red(),0,255));
        rgbVerticalGradient=QLinearGradient(0,0,0,width());
        rgbVerticalGradient.setColorAt(0,QColor(0,255,0));
        rgbVerticalGradient.setColorAt(1,QColor(0,0,0));
        break;
    case greenMode:
        rgbHorizontalGradient=QLinearGradient(0,0,width(),0);
        rgbHorizontalGradient.setColorAt(0,QColor(0,color.green(),0));
        rgbHorizontalGradient.setColorAt(1,QColor(0,color.green(),255));
        rgbVerticalGradient=QLinearGradient(0,0,0,width());
        rgbVerticalGradient.setColorAt(0,QColor(255,0,0));
        rgbVerticalGradient.setColorAt(1,QColor(0,0,0));
        break;
    case blueMode:
        rgbHorizontalGradient=QLinearGradient(0,0,width(),0);
        rgbHorizontalGradient.setColorAt(0,QColor(0,0,color.blue()));
        rgbHorizontalGradient.setColorAt(1,QColor(255,0,color.blue()));
        rgbVerticalGradient=QLinearGradient(0,0,0,width());
        rgbVerticalGradient.setColorAt(0,QColor(0,255,0));
        rgbVerticalGradient.setColorAt(1,QColor(0,0,0));
        break;
    default:
        hueLevelGradient=QLinearGradient(0,0,width(),0);
        color0.setHsv(color.hue(), 0, 255);
        color100.setHsv(color.hue(), 255, 255);
        hueLevelGradient.setColorAt(0, color0);
        hueLevelGradient.setColorAt(1, color100);
        hsvGreyGradient.setColorAt(0, QColor(0,0,0,0));
        hsvGreyGradient.setColorAt(1, QColor(0,0,0,255));
    }
    setColorCursor(color);
    update();
}

void KCColorDoubleBoardBase::setColorCursor(const QColor &color)
{
    cursorX=2;cursorY=2;
    switch(currentMode)
    {
    case saturationMode:
        //Horizontal: Hue, Vertical: Value
        cursorX+=color.hue()*51/72;
        cursorY+=255-color.value();
        break;
    case valueMode:
        //Horizontal: Hue, Vertical: Saturation
        cursorX+=color.hue()*51/72;
        cursorY+=255-color.saturation();
        break;
    case redMode:
        //Horizontal: Blue, Vertical: Green
        cursorX+=color.blue();
        cursorY+=255-color.green();
        break;
    case greenMode:
        //Horizontal: Blue, Vertical: Red
        cursorX+=color.blue();
        cursorY+=255-color.red();
        break;
    case blueMode:
        //Horizontal: Red, Vertical: Green
        cursorX+=color.red();
        cursorY+=255-color.green();
        break;
    default:
        //Horizontal: Saturation, Vertical: Value
        cursorX+=color.saturation();
        cursorY+=255-color.value();
        break;
    }
}

void KCColorDoubleBoardBase::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect renderRect(2,2,255,255);
    painter.setPen(Qt::NoPen);
    switch(currentMode)
    {
    case saturationMode:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(saturationGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(hsvGreyGradient));
        painter.drawRect(renderRect);
        break;
    case valueMode:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(saturationGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(hsvGreyGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(valueColor));
        painter.drawRect(renderRect);
        break;
    case redMode:
    case greenMode:
    case blueMode:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(rgbHorizontalGradient));
        painter.drawRect(renderRect);
        painter.setCompositionMode(QPainter::CompositionMode_Plus);
        painter.setBrush(QBrush(rgbVerticalGradient));
        painter.drawRect(renderRect);
        break;
    default:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(hueLevelGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(hsvGreyGradient));
        painter.drawRect(renderRect);
    }
    //Update cursor:
    int cursorWidth=cursorSize*2,
        positionX=cursorX-cursorSize,
        positionY=cursorY-cursorSize;
    painter.setBrush(QBrush(QColor(0,0,0,0)));
    painter.setPen(QPen(QColor(0,0,0)));
    painter.drawEllipse(positionX,
                        positionY,
                        cursorWidth,
                        cursorWidth);
    cursorWidth-=2;
    painter.setPen(QPen(QColor(255,255,255)));
    painter.drawEllipse(positionX+1,
                        positionY+1,
                        cursorWidth,
                        cursorWidth);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect());
}

void KCColorDoubleBoardBase::resizeEvent(QResizeEvent *event)
{
    int widthElement=event->size().width(),
        heightElement=event->size().height();
    if(widthElement!=heightElement)
    {
        int minimumElement=heightElement<widthElement?
                    heightElement:
                    widthElement;
        event->ignore();
        resize(minimumElement,minimumElement);
        return;
    }
    hueLevelGradient.setFinalStop(widthElement,0);
    hsvGreyGradient.setFinalStop(0,widthElement);
    saturationGradient.setFinalStop(widthElement,0);
    rgbHorizontalGradient.setFinalStop(widthElement, 0);
    rgbVerticalGradient.setFinalStop(0, widthElement);
    QWidget::resizeEvent(event);
}

void KCColorDoubleBoardBase::mousePressEvent(QMouseEvent *event)
{
    isPressed=true;
    valueProcess(event->pos().x(),event->pos().y());
    update();
    QWidget::mousePressEvent(event);
}

void KCColorDoubleBoardBase::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed=false;
    QWidget::mouseReleaseEvent(event);
}

void KCColorDoubleBoardBase::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        valueProcess(event->pos().x(),event->pos().y());
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void KCColorDoubleBoardBase::enterEvent(QEvent *event)
{
    setCursor(QCursor(Qt::CrossCursor));
    QWidget::enterEvent(event);
}

void KCColorDoubleBoardBase::valueProcess(const int &x, const int &y)
{
    if(x<2)
    {
        cursorX=0;
    }
    else if(x>257)
    {
        cursorX=255;
    }
    else
    {
        cursorX=x-2;
    }
    if(y<2)
    {
        cursorY=0;
    }
    else if(y>257)
    {
        cursorY=255;
    }
    else
    {
        cursorY=y-2;
    }
    //Emit signal:
    QColor currentColor;
    switch(currentMode)
    {
    case saturationMode:
        currentColor.setHsv(cursorX*72/51,
                            baseColor.saturation(),
                            255-cursorY);
        break;
    case valueMode:
        currentColor.setHsv(cursorX*72/51,
                            255-cursorY,
                            baseColor.value());
        break;
    case redMode:
        currentColor.setRgb(baseColor.red(),
                            255-cursorY,
                            cursorX);
        break;
    case greenMode:
        currentColor.setRgb(255-cursorY,
                            baseColor.green(),
                            cursorX);
        break;
    case blueMode:
        currentColor.setRgb(cursorX,
                            255-cursorY,
                            baseColor.blue());
        break;
    default:
        currentColor.setHsv(baseColor.hue(),
                            cursorX,
                            255-cursorY);
        break;
    }
    emit requireUpdateColor(currentColor);
}

KCColorRingBoard::KCColorRingBoard(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(424,424);
    ringGradient.setColorAt(0.00, QColor(255,0,0));
    ringGradient.setColorAt(0.16, QColor(255,255,0));
    ringGradient.setColorAt(0.33, QColor(0,255,0));
    ringGradient.setColorAt(0.50, QColor(0,255,255));
    ringGradient.setColorAt(0.66, QColor(0,0,255));
    ringGradient.setColorAt(0.83, QColor(255,0,255));
    ringGradient.setColorAt(1.00, QColor(255,0,0));
}

void KCColorRingBoard::syncColor(const QColor &color)
{
    currentColor=color;
    double angle=(double)(color.hue()+90)*3.141/180;
    cursorX=cursorCenter+(double)cursorRing*sin(angle);
    cursorY=cursorCenter+(double)cursorRing*cos(angle);
    update();
}

void KCColorRingBoard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QRect paintRect(2,2,width()-4,width()-4);
    QPainter painter(this);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    painter.drawEllipse(0,0,width()-1,width()-1);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(ringGradient));
    painter.drawEllipse(paintRect);
    painter.setBrush(QBrush(palette().color(QPalette::Window)));
    paintRect.setTopLeft(QPoint(ringWidth-1, ringWidth-1));
    paintRect.setBottomRight(QPoint(width()-ringWidth+1,
                                    width()-ringWidth+1));
    painter.drawEllipse(paintRect);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    paintRect.setTopLeft(QPoint(ringWidth, ringWidth));
    paintRect.setBottomRight(QPoint(width()-ringWidth,
                                    width()-ringWidth));
    painter.drawEllipse(paintRect);
    //Update cursor:
    int cursorWidth=cursorSize*2,
        positionX=cursorX-cursorSize,
        positionY=cursorY-cursorSize;
    painter.setBrush(QBrush(QColor(0,0,0,0)));
    painter.setPen(QPen(QColor(0,0,0)));
    painter.drawEllipse(positionX,
                        positionY,
                        cursorWidth,
                        cursorWidth);
    cursorWidth-=2;
    painter.setPen(QPen(QColor(255,255,255)));
    painter.drawEllipse(positionX+1,
                        positionY+1,
                        cursorWidth,
                        cursorWidth);
}

void KCColorRingBoard::resizeEvent(QResizeEvent *event)
{
    int widthElement=event->size().width(),
        heightElement=event->size().height();
    if(widthElement!=heightElement)
    {
        int minimumElement=heightElement<widthElement?
                    heightElement:
                    widthElement;
        event->ignore();
        resize(minimumElement,minimumElement);
        return;
    }
    ringGradient.setCenter(widthElement/2,
                           widthElement/2);
    QWidget::resizeEvent(event);
}

void KCColorRingBoard::mousePressEvent(QMouseEvent *event)
{
    int centerLength=calculateLength(event->pos().x(),
                                     event->pos().y());
    if(centerLength>182 && centerLength<212)
    {
        isPressed=true;
        currentColor.setHsv(calculateHue(event->pos().x(),
                                         event->pos().y()),
                            currentColor.saturation(),
                            currentColor.value());
        emit requireSyncColor(currentColor);
    }
    QWidget::mousePressEvent(event);
}

void KCColorRingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed=false;
    QWidget::mouseReleaseEvent(event);
}

void KCColorRingBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        currentColor.setHsv(calculateHue(event->pos().x(),
                                         event->pos().y()),
                            currentColor.saturation(),
                            currentColor.value());
        emit requireSyncColor(currentColor);
    }
    QWidget::mouseMoveEvent(event);
}

int KCColorRingBoard::calculateLength(int posX, int posY)
{
    int paramX=posX-cursorCenter, paramY=posY-cursorCenter;
    paramX*=paramX;
    paramY*=paramY;
    double distance=sqrt((double)paramX+(double)paramY);
    return (int)distance;
}

int KCColorRingBoard::calculateHue(int posX, int posY)
{
    int paramX=posX-cursorCenter,
        paramY=posY-cursorCenter,
        paramL=calculateLength(posX, posY),
        paramAbsX=paramX>0?paramX:-paramX,
        paramAbsY=paramY>0?paramY:-paramY;
    if(paramL==0)
    {
        paramL=1;
    }
    qreal sineValue,coseValue;
    qreal halfAngle;
    if(paramAbsX<paramAbsY)
    {
        sineValue=double(paramX)/double(paramL);
        halfAngle=asin(sineValue)*180/3.141;
        if(posX>cursorCenter)
        {
            if(posY<cursorCenter)
            {
                //It is at I.
                return (int)90-halfAngle;
            }
            //It is at IIII.
            return (int)270+halfAngle;
        }
        if(posY<cursorCenter)
        {
            //It is at II.
            return (int)90-halfAngle;
        }
        return (int)270+halfAngle;
    }
    coseValue=double(paramY)/double(paramL);
    halfAngle=acos(coseValue)*180/3.141;
    if(posX>cursorCenter)
    {
        if(posY>cursorCenter)
        {
            //It is at IIII.
            return (int)270+halfAngle;
        }
        //It is at I.
        return (int)halfAngle-90;
    }
    return (int)270-halfAngle;
}

KCColorHSVRing::KCColorHSVRing(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setFixedSize(424,424);
    ringBoard=new KCColorRingBoard(this);
    doubleBoard=new KCColorDoubleBoardBase(this);
    connect(doubleBoard, SIGNAL(requireUpdateColor(QColor)),
            this, SIGNAL(requireUpdateColor(QColor)));
    connect(ringBoard, SIGNAL(requireSyncColor(QColor)),
            this, SIGNAL(requireUpdateColor(QColor)));
    doubleBoard->move(83,83);
}

void KCColorHSVRing::setColorMode(QString elementName,
                                  int value,
                                  QColor color)
{
    Q_UNUSED(value);
    doubleBoard->setColor(elementName,
                          color);
    ringBoard->syncColor(color);
}

void KCColorHSVRing::syncColor(QColor color)
{
    ringBoard->syncColor(color);
    doubleBoard->syncColor(color);
}

/*!
 *\brief KCColorLevelRenderBase is a color slider.
 */
KCColorLevelRenderBase::KCColorLevelRenderBase(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(260,25);
    levelGradient.setStart(0,0);
    levelGradient.setFinalStop(width(),
                               height());
}

void KCColorLevelRenderBase::renderRed(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    levelGradient.setColorAt(0.0, QColor(0,color.green(),color.blue()));
    levelGradient.setColorAt(1.0, QColor(255,color.green(),color.blue()));
    update();
}

void KCColorLevelRenderBase::renderGreen(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    levelGradient.setColorAt(0.0, QColor(color.red(),0,color.blue()));
    levelGradient.setColorAt(1.0, QColor(color.red(),255,color.blue()));
    update();
}

void KCColorLevelRenderBase::renderBlue(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    levelGradient.setColorAt(0.0, QColor(color.red(),color.green(),0));
    levelGradient.setColorAt(1.0, QColor(color.red(),color.green(),255));
    update();
}

void KCColorLevelRenderBase::renderHue(const QColor &color)
{
    Q_UNUSED(color);
    levelGradient=QLinearGradient(0,0,width(),height());
    levelGradient.setColorAt(0.00, QColor(255,0,0));
    levelGradient.setColorAt(0.16, QColor(255,255,0));
    levelGradient.setColorAt(0.33, QColor(0,255,0));
    levelGradient.setColorAt(0.50, QColor(0,255,255));
    levelGradient.setColorAt(0.66, QColor(0,0,255));
    levelGradient.setColorAt(0.83, QColor(255,0,255));
    levelGradient.setColorAt(1.00, QColor(255,0,0));
    update();
}

void KCColorLevelRenderBase::renderSaturation(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setHsv(color.hue(), 0, color.value());
    endColor.setHsv(color.hue(), 255, color.value());
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::renderValue(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setHsv(color.hue(), color.saturation(), 0);
    endColor.setHsv(color.hue(), color.saturation(), 255);
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::renderLightness(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setHsl(color.hue(), color.saturation(), 0);
    endColor.setHsl(color.hue(), color.saturation(), 255);
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::renderCyan(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setCmyk(0, color.magenta(), color.yellow(), color.black());
    endColor.setCmyk(255, color.magenta(), color.yellow(), color.black());
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::renderMagenta(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setCmyk(color.cyan(), 0, color.yellow(), color.black());
    endColor.setCmyk(color.cyan(), 255, color.yellow(), color.black());
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::renderYellow(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setCmyk(color.cyan(), color.magenta(), 0, color.black());
    endColor.setCmyk(color.cyan(), color.magenta(), 255, color.black());
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::renderBlack(const QColor &color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    QColor startColor, endColor;
    startColor.setCmyk(color.cyan(), color.magenta(), color.yellow(), 0);
    endColor.setCmyk(color.cyan(), color.magenta(), color.yellow(), 255);
    levelGradient.setColorAt(0.0, startColor);
    levelGradient.setColorAt(1.0, endColor);
    update();
}

void KCColorLevelRenderBase::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    painter.drawRect(QRect(0,0,259,23));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(levelGradient));
    painter.drawRect(QRect(2,2,256,20));
}

void KCColorLevelRenderBase::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    levelGradient.setFinalStop(width(),
                               height());
}

void KCColorLevelRenderBase::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit sliderPressed();
    isPressed=true;
    int haruka=event->pos().x()-2;
    if(haruka>-1 && haruka<257)
    {
        emit valueChanged(haruka);
    }
}

void KCColorLevelRenderBase::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(isPressed)
    {
        int haruka=event->pos().x()-2;
        if(haruka<0)
        {
            emit valueChanged(0);
        }
        else if(haruka>255)
        {
            emit valueChanged(255);
        }
        else
        {
            emit valueChanged(haruka);
        }
    }
}

void KCColorLevelRenderBase::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    isPressed=false;
    emit sliderReleased();
}

KCColorLevelSelector::KCColorLevelSelector(QWidget *parent) :
    QWidget(parent)
{
    colorRender=new KCColorLevelRenderBase(this);
    colorRender->move(2,8);
    QPixmap colorPointer(":/img/image/ColorPointer.png");
    colorSelector=new QLabel(this);
    colorSelector->setPixmap(colorPointer);
    setFixedSize(264,colorPointer.height());

    //Selector will update it self when the parent call the update itself.

    connect(colorRender, &KCColorLevelRenderBase::sliderPressed,
            this, &KCColorLevelSelector::sliderPressed);
    connect(colorRender, &KCColorLevelRenderBase::sliderReleased,
            this, &KCColorLevelSelector::sliderReleased);
    connect(colorRender, &KCColorLevelRenderBase::valueChanged,
            this, &KCColorLevelSelector::valueUpdate);
}

void KCColorLevelSelector::focusOnElement(QString elementName)
{
    if(elementName=="H:")
    {
        currentMode=hueMode;
    }
    else if(elementName=="R:")
    {
        currentMode=redMode;
    }
    else if(elementName=="G:")
    {
        currentMode=greenMode;
    }
    else if(elementName=="B:")
    {
        currentMode=blueMode;
    }
    else if(elementName=="S:")
    {
        currentMode=saturationMode;
    }
    else if(elementName=="V:")
    {
        currentMode=valueMode;
    }
    else if(elementName=="C:")
    {
        currentMode=cyanMode;
    }
    else if(elementName=="M:")
    {
        currentMode=magentaMode;
    }
    else if(elementName=="Y:")
    {
        currentMode=yellowMode;
    }
    else if(elementName=="K:")
    {
        currentMode=blackMode;
    }
}

void KCColorLevelSelector::colorUpdate(const QColor &color)
{
    currentColor=color;
    switch(currentMode)
    {
    case redMode:
        colorRender->renderRed(color);
        slide(color.red());
        break;
    case greenMode:
        colorRender->renderGreen(color);
        slide(color.green());
        break;
    case blueMode:
        colorRender->renderBlue(color);
        slide(color.blue());
        break;
    case hueMode:
        colorRender->renderHue(color);
        slide(color.hue());
        break;
    case saturationMode:
        colorRender->renderSaturation(color);
        slide(color.saturation());
        break;
    case valueMode:
        colorRender->renderValue(color);
        slide(color.value());
        break;
    case cyanMode:
        colorRender->renderCyan(color);
        slide(color.cyan());
        break;
    case magentaMode:
        colorRender->renderMagenta(color);
        slide(color.magenta());
        break;
    case yellowMode:
        colorRender->renderYellow(color);
        slide(color.yellow());
        break;
    case blackMode:
        colorRender->renderBlack(color);
        slide(color.black());
        break;
    }
}

void KCColorLevelSelector::setValue(int value)
{
    slide(value);
}

int KCColorLevelSelector::getValue()
{
    int outPosition=colorSelector->x();
    if(maximum!=255)
    {
        outPosition=outPosition*maximum/255;
    }
    return outPosition;
}

void KCColorLevelSelector::slide(int position)
{
    int innerPosition=position;
    if(maximum!=255)
    {
        innerPosition=position*255/maximum;
    }
    colorSelector->move(innerPosition, 0);
}

void KCColorLevelSelector::valueUpdate(int element)
{
    int outPosition=element;
    if(maximum!=255)
    {
        outPosition=outPosition*maximum/255;
    }
    emit valueChanged(outPosition);
}

void KCColorLevelSelector::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
int KCColorLevelSelector::getMaximum() const
{
    return maximum;
}

void KCColorLevelSelector::setMaximum(int value)
{
    maximum = value;
}

KCColorSpinBox::KCColorSpinBox(QWidget *parent) :
    QSpinBox(parent)
{
    setFixedWidth(50);
}

void KCColorSpinBox::focusInEvent(QFocusEvent *event)
{
    QSpinBox::focusInEvent(event);
    emit spinGetFocus();
}

KCColorViewerBase::KCColorViewerBase(QWidget *parent) :
    QWidget(parent)
{
    currentViewer=new QWidget(this);
    currentViewer->setAutoFillBackground(true);
    currentViewer->setFixedHeight(33);
    originalViewer=new QWidget(this);
    originalViewer->setAutoFillBackground(true);
    originalViewer->setFixedHeight(33);
    currentPalette=currentViewer->palette();
    buildViewer();
}

void KCColorViewerBase::buildViewer()
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    QLabel *currentColor=new QLabel(tr("Current Color"), this);
    mainLayout->addWidget(currentColor,0,Qt::AlignCenter);
    mainLayout->addSpacing(2);
    mainLayout->addWidget(currentViewer);
    mainLayout->addWidget(originalViewer);
    QLabel *originalColor=new QLabel(tr("Original Color"), this);
    mainLayout->addSpacing(2);
    mainLayout->addWidget(originalColor,0,Qt::AlignCenter);
}

void KCColorViewerBase::setOriginalColor(QColor color)
{
    QPalette pal=originalViewer->palette();
    pal.setColor(QPalette::Window, color);
    originalViewer->setPalette(pal);
}

void KCColorViewerBase::setCurrentColor(QColor color)
{
    currentPalette.setColor(QPalette::Window, color);
    currentViewer->setPalette(currentPalette);
}

void KCColorViewerBase::updateCurrentColor()
{
    emit requireSetCurrentColor(currentPalette.color(QPalette::Window));
}

KCColorSliderItemBase::KCColorSliderItemBase(QWidget *parent,
                                             bool autoBuild) :
    QWidget(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(3);
    setLayout(mainLayout);

    elementCaption=new QRadioButton(this);
    elementCaption->setFixedWidth(40);
    elementSpinBox=new KCColorSpinBox(this);
    elementSpinBox->setRange(0, 255);
    levelSelector=new KCColorLevelSelector(this);

    connect(elementCaption, SIGNAL(clicked()),
            this, SLOT(onActionClickElement()));

    if(autoBuild)
    {
        buildSlider();
    }
}

void KCColorSliderItemBase::buildSlider()
{
    mainLayout->addWidget(elementCaption);
    mainLayout->addWidget(elementSpinBox);
    mainLayout->addWidget(levelSelector);
    connect(elementSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setValue(int)));
    connect(levelSelector, SIGNAL(valueChanged(int)),
            this, SLOT(setValue(int)));
    connect(elementSpinBox, &KCColorSpinBox::spinGetFocus,
            this, &KCColorSliderItemBase::onActionClickElement);
    connect(levelSelector, SIGNAL(sliderPressed()),
            this, SLOT(onActionClickElement()));
}

void KCColorSliderItemBase::setCaption(const QString &value)
{
    elementCaption->setText(value);
    levelSelector->focusOnElement(value);
}

int KCColorSliderItemBase::getValue()
{
    return levelSelector->getValue();
}

void KCColorSliderItemBase::setMaximum(const int &value)
{
    elementSpinBox->setRange(0, value);
    levelSelector->setMaximum(value);
}

void KCColorSliderItemBase::syncValue(const int &value,
                                      const QColor &color)
{
    //The new color must rerender.
    levelSelector->colorUpdate(color);
    //Sync all the value.
    syncMode=true;
    setValue(value);
    syncMode=false;
}

void KCColorSliderItemBase::setValue(int value)
{
    if(valueSetMode)
    {
        return;
    }
    valueSetMode=true;
    elementSpinBox->setValue(value);
    levelSelector->setValue(value);
    if(!syncMode)
    {
        emit requireElementChanged(elementCaption->text(),
                                   value);
    }
    valueSetMode=false;
}

void KCColorSliderItemBase::setEraseFocus()
{
    if(focusSignalSent)
    {
        focusSignalSent=false;
    }
    else
    {
        elementCaption->setChecked(false);
    }
}

void KCColorSliderItemBase::onActionClickElement()
{
    elementCaption->setChecked(true);
    focusSignalSent=true;
    emit requireFocusOnElement(elementCaption->text(),
                               elementSpinBox->value());
}

KCColorSliderItemPercent::KCColorSliderItemPercent(QWidget *parent) :
    KCColorSliderItemBase(parent, false)
{
    elementSpinBox->setRange(0, 100);
    buildSlider();
}

void KCColorSliderItemPercent::buildSlider()
{
    percentCaption=new QLabel("%", this);
    mainLayout->addWidget(elementCaption);
    mainLayout->addWidget(elementSpinBox);
    mainLayout->addWidget(percentCaption);
    mainLayout->addWidget(levelSelector);
    levelSelector->setVisible(false);
    connect(elementSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setValue(int)));
    connect(levelSelector, SIGNAL(valueChanged(int)),
            this, SLOT(setValueFromLevel(int)));
    connect(elementSpinBox, SIGNAL(spinGetFocus()),
            this, SLOT(onActionClickElement()));
    connect(levelSelector, SIGNAL(sliderPressed()),
            this, SLOT(onActionClickElement()));
}

void KCColorSliderItemPercent::syncValue(const int &value,
                                         const QColor &color)
{
    syncMode=true;
    levelSelector->colorUpdate(color);
    setValueFromLevel(value);
    syncMode=false;
}

void KCColorSliderItemPercent::setValue(int value)
{
    /*
     * This value is greater than 0 and smaller than 100, translate this value
     * to 0-255, set to levelSelector.
     * All the signal will be the 255 mode, so save the result at the beginning.
     */
    if(valueSetMode)
    {
        return;
    }
    int irori=value*51/20;
    valueSetMode=true;
    elementSpinBox->setValue(value);
    levelSelector->setValue(irori);
    if(!syncMode)
    {
        emit requireElementChanged(elementCaption->text(),
                                   irori);
    }
    valueSetMode=false;
}

void KCColorSliderItemPercent::setValueFromLevel(int value)
{
    /*
     * This value is greater than 0 and smaller than 255, translate this value
     * to 0-100, set to elementSpinBox.
     * emit value as the param of the signal.
     */
    if(valueSetMode)
    {
        return;
    }
    valueSetMode=true;
    elementSpinBox->setValue(value*20/51);
    levelSelector->setValue(value);
    if(!syncMode)
    {
        emit requireElementChanged(elementCaption->text(),
                                   value);
    }
    valueSetMode=false;
}

KCColorSliderBase::KCColorSliderBase(QWidget *parent) :
    QWidget(parent)
{
    ;
}

KCColorSliderItemBase *KCColorSliderBase::addElement(const QString &name)
{
    KCColorSliderItemBase *currentElement=new KCColorSliderItemBase(this);
    currentElement->setCaption(name);
    connect(currentElement, &KCColorSliderItemBase::requireFocusOnElement,
            this, &KCColorSliderBase::focusRequire);
    connect(this, &KCColorSliderBase::requireClearElementsFocus,
            currentElement, &KCColorSliderItemBase::setEraseFocus);
    return currentElement;
}

void KCColorSliderBase::syncColor(QColor color)
{
    //Just save the color, all the other things should do in the inhreit class.
    currentColor=color;
}

void KCColorSliderBase::focusRequire(QString elementName,
                                     int value)
{
    emit requireFocusOnElement(elementName, value, currentColor);
}

KCColorSliderCMYKP::KCColorSliderCMYKP(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    cyanElement=addElement("C:");
    magentaElement=addElement("M:");
    yellowElement=addElement("Y:");
    blackElement=addElement("K:");

    connect(cyanElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::onElementChanged);
    connect(magentaElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::onElementChanged);
    connect(yellowElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::onElementChanged);
    connect(blackElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::onElementChanged);

    mainLayout->addWidget(cyanElement);
    mainLayout->addWidget(magentaElement);
    mainLayout->addWidget(yellowElement);
    mainLayout->addWidget(blackElement);
}

KCColorSliderItemPercent *KCColorSliderCMYKP::addElement(const QString &name)
{
    KCColorSliderItemPercent *currentElement=new KCColorSliderItemPercent(this);
    currentElement->setCaption(name);
    connect(currentElement, &KCColorSliderItemPercent::requireFocusOnElement,
            this, &KCColorSliderCMYKP::focusRequire);
    connect(this, SIGNAL(requireClearElementsFocus()),
            currentElement, SLOT(setEraseFocus()));
    return currentElement;
}

void KCColorSliderCMYKP::onElementChanged(QString elementName, int value)
{
    if(elementName=="C:")
    {
        currentColor.setCmyk(value,
                             magentaElement->getValue(),
                             yellowElement->getValue(),
                             blackElement->getValue());
    }
    else if(elementName=="M:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             value,
                             yellowElement->getValue(),
                             blackElement->getValue());
    }
    else if(elementName=="Y:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             magentaElement->getValue(),
                             value,
                             blackElement->getValue());
    }
    else if(elementName=="K:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             magentaElement->getValue(),
                             yellowElement->getValue(),
                             value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    syncElement();
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderCMYKP::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    syncElement();
}

void KCColorSliderCMYKP::focusRequire(QString elementName, int value)
{
    emit requireFocusOnElement(elementName,
                               value,
                               currentColor);
}

void KCColorSliderCMYKP::syncElement()
{
    currentColor=currentColor.toCmyk();
    cyanElement->syncValue(currentColor.cyan(), currentColor);
    magentaElement->syncValue(currentColor.magenta(), currentColor);
    yellowElement->syncValue(currentColor.yellow(), currentColor);
    blackElement->syncValue(currentColor.black(), currentColor);
}

KCColorSliderCMYK::KCColorSliderCMYK(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    cyanElement=addElement("C:");
    magentaElement=addElement("M:");
    yellowElement=addElement("Y:");
    blackElement=addElement("K:");

    connect(cyanElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::onElementChanged);
    connect(magentaElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::onElementChanged);
    connect(yellowElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::onElementChanged);
    connect(blackElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::onElementChanged);

    mainLayout->addWidget(cyanElement);
    mainLayout->addWidget(magentaElement);
    mainLayout->addWidget(yellowElement);
    mainLayout->addWidget(blackElement);
}

void KCColorSliderCMYK::onElementChanged(QString elementName, int value)
{
    if(elementName=="C:")
    {
        currentColor.setCmyk(value,
                             magentaElement->getValue(),
                             yellowElement->getValue(),
                             blackElement->getValue());
    }
    else if(elementName=="M:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             value,
                             yellowElement->getValue(),
                             blackElement->getValue());
    }
    else if(elementName=="Y:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             magentaElement->getValue(),
                             value,
                             blackElement->getValue());
    }
    else if(elementName=="K:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             magentaElement->getValue(),
                             yellowElement->getValue(),
                             value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    //Update self element.
    syncElement();
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderCMYK::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    syncElement();
}

void KCColorSliderCMYK::syncElement()
{
    cyanElement->syncValue(currentColor.cyan(), currentColor);
    magentaElement->syncValue(currentColor.magenta(), currentColor);
    yellowElement->syncValue(currentColor.yellow(), currentColor);
    blackElement->syncValue(currentColor.black(), currentColor);
}

KCColorSliderRGB::KCColorSliderRGB(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    redElement=addElement("R:");
    greenElement=addElement("G:");
    blueElement=addElement("B:");

    connect(redElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderRGB::onElementChanged);
    connect(greenElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderRGB::onElementChanged);
    connect(blueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderRGB::onElementChanged);

    mainLayout->addWidget(redElement);
    mainLayout->addWidget(greenElement);
    mainLayout->addWidget(blueElement);
}

void KCColorSliderRGB::onElementChanged(QString elementName, int value)
{
    if(elementName=="R:")
    {
        currentColor.setRed(value);
    }
    else if(elementName=="G:")
    {
        currentColor.setGreen(value);
    }
    else if(elementName=="B:")
    {
        currentColor.setBlue(value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    syncElement();
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderRGB::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    syncElement();
}

void KCColorSliderRGB::syncElement()
{
    redElement->syncValue(currentColor.red(), currentColor);
    greenElement->syncValue(currentColor.green(), currentColor);
    blueElement->syncValue(currentColor.blue(), currentColor);
}

KCColorSliderHSV::KCColorSliderHSV(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    hueElement=addElement("H:");
    hueElement->setMaximum(359);
    saturationElement=addElement("S:");
    valueElement=addElement("V:");

    connect(hueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSV::onElementChanged);
    connect(saturationElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSV::onElementChanged);
    connect(valueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSV::onElementChanged);

    mainLayout->addWidget(hueElement);
    mainLayout->addWidget(saturationElement);
    mainLayout->addWidget(valueElement);;
}

void KCColorSliderHSV::onElementChanged(QString elementName, int value)
{
    if(elementName=="H:")
    {
        currentColor.setHsv(value,
                            saturationElement->getValue(),
                            valueElement->getValue());
    }
    else if(elementName=="S:")
    {
        currentColor.setHsv(hueElement->getValue(),
                            value,
                            valueElement->getValue());
        ignoreHue=true;
    }
    else if(elementName=="V:")
    {
        currentColor.setHsv(hueElement->getValue(),
                            saturationElement->getValue(),
                            value);
        ignoreHue=true;
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    syncElement();
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderHSV::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    syncElement();
}

void KCColorSliderHSV::syncElement()
{
    if(ignoreHue)
    {
        ignoreHue=false;
    }
    else
    {
        hueElement->syncValue(currentColor.hue(), currentColor);
    }
    saturationElement->syncValue(currentColor.saturation(), currentColor);
    valueElement->syncValue(currentColor.value(), currentColor);
}

KCColorFunctionButton::KCColorFunctionButton(const QString &focusPixmapPath,
                                             const QString &noFocusPixmapPath,
                                             QWidget *parent) :
    QToolButton(parent)
{
    setCheckable(true);
    setAutoRaise(true);
    noFocusIcon=QIcon(noFocusPixmapPath);
    focusIcon=QIcon(focusPixmapPath);
    setIcon(noFocusIcon);
}

void KCColorFunctionButton::setChecked(bool value)
{
    QToolButton::setChecked(value);
    if(value)
    {
        setIcon(focusIcon);
    }
    else
    {
        setIcon(noFocusIcon);
    }
}

KCColorFunctionSelector::KCColorFunctionSelector(QWidget *parent) :
    QWidget(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    mapper=new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)),this, SLOT(focusOnFunction(int)));
    addFunctionButton(":/img/image/ColorRingModeSelect.png",
                      ":/img/image/ColorRingMode.png");
    addFunctionButton(":/img/image/ColorDatabaseModeSelect.png",
                      ":/img/image/ColorDatabaseMode.png");
    mainLayout->addStretch();
}

void KCColorFunctionSelector::focusOnFunction(int index)
{
    emit requireLostFocus(false);
    KCColorFunctionButton *button=static_cast<KCColorFunctionButton *>(mapper->mapping(index));
    button->setChecked(true);
    emit requireFocusOn(index);
}

KCColorFunctionButton *KCColorFunctionSelector::addFunctionButton(const QString &focusPixmapPath,
                                                                  const QString &noFocusPixmapPath)
{
    KCColorFunctionButton *button=new KCColorFunctionButton(focusPixmapPath,
                                                            noFocusPixmapPath,
                                                            this);
    mainLayout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(this, &KCColorFunctionSelector::requireLostFocus,
            button, &KCColorFunctionButton::setChecked);
    mapper->setMapping(button, buttonCounter);
    if(buttonCounter==0)
    {
        button->setChecked(true);
    }
    buttonCounter++;
    return button;
}

KCColorPicker::KCColorPicker(QWidget *parent) :
    QToolButton(parent)
{
    setIcon(QIcon(":/img/image/straw.png"));
}

void KCColorPicker::mousePressEvent(QMouseEvent *event)
{
    QToolButton::mousePressEvent(event);
    isPressed=true;
    setCursor(QCursor(Qt::CrossCursor));
    getPositionColor();
}

void KCColorPicker::mouseMoveEvent(QMouseEvent *event)
{
    QToolButton::mouseMoveEvent(event);
    if(isPressed)
    {
        getPositionColor();
    }
}

void KCColorPicker::mouseReleaseEvent(QMouseEvent *event)
{
    QToolButton::mouseReleaseEvent(event);
    isPressed=false;
    getPositionColor();
}

void KCColorPicker::getPositionColor()
{
    int posX = QCursor::pos().x();
    int posY = QCursor::pos().y();
    QPixmap snapshot=QPixmap::grabWindow(QApplication::desktop()->winId(),
                                         posX,
                                         posY,
                                         1,
                                         1);
    if(!snapshot.isNull())
    {
        QImage image = snapshot.toImage();
        if(!image.isNull())
        {
            if(image.valid(0,0))
            {
                QColor color=image.pixel(0, 0);
                emit requireSyncColor(color);
            }
        }
    }
}

KCColorSelector::KCColorSelector(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Color Selector"));

    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    setLayout(mainLayout);

    colorFunctionsLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    KCColorFunctionSelector *functionList=new KCColorFunctionSelector(this);
    colorFunctionsLayout->addWidget(functionList);
    QStackedWidget *functionStack=new QStackedWidget(this);
    functionStack->setFixedSize(424,424);
    colorFunctionsLayout->addWidget(functionStack);
    KCColorHSVRing *colorRing=new KCColorHSVRing(this);
    registerHSVRing(colorRing);
    functionStack->addWidget(colorRing);
    KCColorDatabaseBrowser *databaseBrower=new KCColorDatabaseBrowser(this);
    registerColorDatabase(databaseBrower);
    functionStack->addWidget(databaseBrower);
    connect(functionList, SIGNAL(requireFocusOn(int)),
            functionStack, SLOT(setCurrentIndex(int)));
    mainLayout->addLayout(colorFunctionsLayout);

    yayaLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    yayaLayout->setContentsMargins(0,0,0,0);
    yayaLayout->setSpacing(0);
    KCColorSliderHSV *hsv=new KCColorSliderHSV(this);
    registerSelector(hsv);
    yayaLayout->addWidget(hsv);
    KCColorSliderRGB *rgb=new KCColorSliderRGB(this);
    registerSelector(rgb);
    yayaLayout->addWidget(rgb);
    KCColorSliderCMYK *cmyk=new KCColorSliderCMYK(this);
    registerSelector(cmyk);
    yayaLayout->addWidget(cmyk);
    yayaLayout->addStretch();
    mainLayout->addLayout(yayaLayout);

    iroriLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    okButton=new QPushButton(tr("&Ok"), this);
    okButton->setDefault(true);
    iroriLayout->addWidget(okButton);
    cancelButton=new QPushButton(tr("&Cancel"), this);
    iroriLayout->addWidget(cancelButton);
    KCColorViewerBase *viewer=new KCColorViewerBase(this);
    registerViewer(viewer);
    iroriLayout->addWidget(viewer);
    KCColorPicker *picker=new KCColorPicker(this);
    registerColorPicker(picker);
    iroriLayout->addWidget(picker, 0, Qt::AlignCenter);
    iroriLayout->addStretch();
    KCHexColorEditor *hexEditor=new KCHexColorEditor(this);
    registerHexEditor(hexEditor);
    iroriLayout->addWidget(hexEditor);
    KCColorSliderCMYKP *cmykp=new KCColorSliderCMYKP(this);
    registerSelector(cmykp);
    iroriLayout->addWidget(cmykp);

    mainLayout->addLayout(iroriLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(onActionOkPressed()));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(onActionCancelPressed()));

    emit requireSyncColor(QColor(0,0,0));
}

KCColorSelector::~KCColorSelector()
{
    colorFunctionsLayout->deleteLater();
    yayaLayout->deleteLater();
    iroriLayout->deleteLater();
}

void KCColorSelector::setOriginalColor(const QColor &color)
{
    emit requireSetOriginalColor(color);
    emit requireSyncColor(color);
    setCurrentColor(color);
}

void KCColorSelector::registerSelector(KCColorSliderBase *selector)
{
    //**Ask every one to sync color to the selector, and apply others require**
    connect(selector, &KCColorSliderBase::requireSyncColor,
            this, &KCColorSelector::requireSyncColor);
    connect(this, &KCColorSelector::requireSyncColor,
            selector, &KCColorSliderBase::syncColor);
    connect(this, &KCColorSelector::requireSetOriginalColor,
            selector, &KCColorSliderBase::syncColor);

    //**Ask every one to focus on the the element, and apply others require**
    connect(selector, &KCColorSliderBase::requireFocusOnElement,
            this, &KCColorSelector::requireFocusOnElement);
    connect(selector, SIGNAL(requireFocusOnElement(QString,int,QColor)),
            this, SIGNAL(requireClearFocus()));
    connect(this, &KCColorSelector::requireClearFocus,
            selector, &KCColorSliderBase::requireClearElementsFocus);
}

void KCColorSelector::registerViewer(KCColorViewerBase *viewer)
{
    connect(this, &KCColorSelector::requireSyncColor,
            viewer, &KCColorViewerBase::setCurrentColor);
    connect(this, &KCColorSelector::requireSetOriginalColor,
            viewer, &KCColorViewerBase::setOriginalColor);
    connect(viewer, &KCColorViewerBase::requireSetCurrentColor,
            this, &KCColorSelector::setCurrentColor);
    connect(this, &KCColorSelector::requireGetCurrentColor,
            viewer, &KCColorViewerBase::updateCurrentColor);
}

void KCColorSelector::registerHSVRing(KCColorHSVRing *hsvRing)
{
    connect(this, &KCColorSelector::requireFocusOnElement,
            hsvRing, &KCColorHSVRing::setColorMode);
    connect(this, &KCColorSelector::requireSyncColor,
            hsvRing, &KCColorHSVRing::syncColor);
    connect(hsvRing, SIGNAL(requireUpdateColor(QColor)),
            this, SIGNAL(requireSyncColor(QColor)));
}

void KCColorSelector::registerHexEditor(KCHexColorEditor *editor)
{
    connect(this, &KCColorSelector::requireSyncColor,
            editor, &KCHexColorEditor::syncColor);
    connect(editor, &KCHexColorEditor::requireSyncColor,
            this, &KCColorSelector::requireSyncColor);
}

void KCColorSelector::registerColorDatabase(KCColorDatabaseBrowser *browser)
{
    connect(browser, &KCColorDatabaseBrowser::requireSyncColor,
            this, &KCColorSelector::requireSyncColor);
}

void KCColorSelector::registerColorPicker(KCColorPicker *picker)
{
    connect(picker, SIGNAL(requireSyncColor(QColor)),
            this, SIGNAL(requireSyncColor(QColor)));
}

QColor KCColorSelector::getCurrentColor() const
{
    return currentColor;
}

void KCColorSelector::setCurrentColor(QColor color)
{
    currentColor=color;
}

void KCColorSelector::onActionOkPressed()
{
    emit requireGetCurrentColor();
    close();
}

void KCColorSelector::onActionCancelPressed()
{
    close();
}
