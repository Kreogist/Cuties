/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  kreogistcutestyle.cpp is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kreogistcutestyle.h"

KreogistCuteStyle::KreogistCuteStyle()
{
    //Set File Icon
    qicoFileIcon = new QIcon;
    qicoFileIcon->addFile(QString(":/img/image/FileMenuIcon.png"));

    style=QStyleFactory::create("fusion");
    style->setParent(this);
}

KreogistCuteStyle::~KreogistCuteStyle()
{
}

void KreogistCuteStyle::drawControl(ControlElement element,
                                    const QStyleOption *opt,
                                    QPainter *p,
                                    const QWidget *w) const
{
    switch(element)
    {
    case CE_MenuItem:
    {
        const QStyleOptionMenuItem *_opt_menu_item=
                qstyleoption_cast<const QStyleOptionMenuItem *>(opt);
        if(_opt_menu_item != nullptr)
        {
            drawMenuItem(_opt_menu_item,p,w);
        }
        break;
    }

    default:
        style->drawControl(element,opt,p,w);
        break;
    }
}

void KreogistCuteStyle::drawMenuItem(const QStyleOptionMenuItem *opt,
                                     QPainter *p,
                                     const QWidget *w) const
{
    //Wang: Ok, it's a hack-way to accomplished our design.
    //Saki: A more bug way to redraw icon.
    switch(opt->menuItemType)
    {
    case QStyleOptionMenuItem::SubMenu:
    case QStyleOptionMenuItem::Normal:
    {
        style->drawControl(CE_MenuItem,opt,p,w);
        int iRectX=opt->rect.x(),
            iRectY=opt->rect.y(),
            iRectW=opt->rect.width(),
            iRectH=opt->rect.height();

        QPen pen;
        if(!opt->icon.isNull())
        {
            qDebug()<<opt->text;
            p->drawPixmap(11,
                          iRectY + (iRectH - 30)/2,
                          30,
                          30,
                          qicoFileIcon->pixmap(30, 30));
        }
        pen.setColor(QColor(0,0,0));
        if(iRectX+iRectH -1 != opt->menuRect.y() + opt->menuRect.height())
        {
            p->drawLine(iRectX,iRectY+iRectH-1,iRectX+iRectW,iRectY+iRectH-1);
        }
        break;
    }

    default:
        style->drawControl(CE_MenuItem,opt,p,w);
    }
}

void KreogistCuteStyle::drawPrimitive(PrimitiveElement pe,
                                      const QStyleOption *opt,
                                      QPainter *p,
                                      const QWidget *w) const
{
    style->drawPrimitive(pe,opt,p,w);
}

void KreogistCuteStyle::drawComplexControl(ComplexControl cc,
                                           const QStyleOptionComplex *opt,
                                           QPainter *p,
                                           const QWidget *w) const
{
    style->drawComplexControl(cc,opt,p,w);
}

void KreogistCuteStyle::drawItemText(QPainter *painter,
                                     const QRect &rect,
                                     int flags,
                                     const QPalette &pal,
                                     bool enabled,
                                     const QString &text,
                                     QPalette::ColorRole textRole) const
{
    style->drawItemText(painter,rect,flags,pal,enabled,text,textRole);

}

QSize KreogistCuteStyle::sizeFromContents(ContentsType ct,
                                         const QStyleOption *opt,
                                         const QSize &contentsSize,
                                         const QWidget *widget) const
{

    switch(ct)
    {
        case CT_MenuItem:
        {
            QSize ret=style->sizeFromContents(ct,opt,contentsSize,widget);
            ret.setHeight(42);
            return ret;
            break;
        }
        default:
        {
            return style->sizeFromContents(ct,opt,contentsSize,widget);
        }
    }
}

int KreogistCuteStyle::pixelMetric(PixelMetric metric,
                                   const QStyleOption *option,
                                   const QWidget *widget) const
{
    int pIntValue = style->pixelMetric(metric,option,widget);
    switch (metric) {
    case QStyle::PM_SmallIconSize:
        pIntValue=40;
        break;
    case QStyle::PM_ButtonIconSize:
        pIntValue=25;
        break;
    case QStyle::PM_MenuHMargin:
    case QStyle::PM_MenuVMargin:
        pIntValue=0;
        break;
    /*case QStyle::PM_LayoutLeftMargin:
    case QStyle::PM_LayoutBottomMargin:
    case QStyle::PM_LayoutRightMargin:
    case QStyle::PM_LayoutTopMargin:
        pIntValue=0;
        break;*/
    default:
        break;
    }
    return pIntValue;
}

QRect KreogistCuteStyle::subElementRect(SubElement r,
                                        const QStyleOption *opt,
                                        const QWidget *widget) const
{
    return style->subElementRect(r,opt,widget);
}
QStyle::SubControl KreogistCuteStyle::hitTestComplexControl(ComplexControl cc,
                                                    const QStyleOptionComplex *opt,
                                                    const QPoint &pt,
                                                    const QWidget *w) const
{
    return style->hitTestComplexControl(cc,opt,pt,w);
}
QRect KreogistCuteStyle::subControlRect(ComplexControl cc,
                                        const QStyleOptionComplex *opt,
                                        SubControl sc,
                                        const QWidget *widget) const
{
    return style->subControlRect(cc,opt,sc,widget);
}
QPixmap KreogistCuteStyle::generatedIconPixmap(QIcon::Mode iconMode,
                                               const QPixmap &pixmap,
                                               const QStyleOption *opt) const
{
    return style->generatedIconPixmap(iconMode,pixmap,opt);
}
int KreogistCuteStyle::styleHint(StyleHint hint,
                                 const QStyleOption *option,
                                 const QWidget *widget,
                                 QStyleHintReturn *returnData) const
{
    return style->styleHint(hint,option,widget,returnData);
}
QRect KreogistCuteStyle::itemPixmapRect(const QRect &r,
                                        int flags,
                                        const QPixmap &pixmap) const
{
    return style->itemPixmapRect(r,flags,pixmap);
}
QIcon KreogistCuteStyle::standardIcon(StandardPixmap standardIcon,
                                      const QStyleOption *option,
                                      const QWidget *widget) const
{
    return style->standardIcon(standardIcon,option,widget);
}
QPixmap KreogistCuteStyle::standardPixmap(StandardPixmap standardPixmap,
                                          const QStyleOption *opt,
                                          const QWidget *widget) const
{
    return style->standardPixmap(standardPixmap,opt,widget);
}
void KreogistCuteStyle::drawItemPixmap(QPainter *painter, const QRect &rect,
                    int alignment, const QPixmap &pixmap) const
{
    return style->drawItemPixmap(painter,rect,alignment,pixmap);
}

void KreogistCuteStyle::polish(QWidget *widget)
{
    return style->polish(widget);
}
void KreogistCuteStyle::polish(QApplication *app)
{
    return style->polish(app);
}
void KreogistCuteStyle::polish(QPalette &pal)
{
    return style->polish(pal);
}
void KreogistCuteStyle::unpolish(QWidget *widget)
{
    return style->unpolish(widget);
}
void KreogistCuteStyle::unpolish(QApplication *app)
{
    return style->unpolish(app);
}
