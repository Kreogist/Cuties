/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kreogistcutestyle.h"

KreogistCuteStyle::KreogistCuteStyle()
{
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
    case CE_TabBarTab:
    {
        const QStyleOptionTab *_opt_tab_item=
                qstyleoption_cast<const QStyleOptionTab *>(opt);
        if(_opt_tab_item != nullptr)
        {
            drawTabItem(_opt_tab_item,p,w);
        }
        break;

    }
    default:
        style->drawControl(element,opt,p,w);
        break;
    }
}

void KreogistCuteStyle::drawTabItem(const QStyleOptionTab *opt,
                                    QPainter *p,
                                    const QWidget *w) const
{
    if(opt->state & QStyle::State_Selected)
    {
        QStyleOptionTab tmp=*opt;
        tmp.text=QString(opt->text.length(),QChar(' '));
        style->drawControl(CE_TabBarTab,&tmp,p,w);
        int alignment = Qt::AlignCenter | Qt::TextShowMnemonic;
        if (!proxy()->styleHint(SH_UnderlineShortcut, opt, w))
        {
            alignment |= Qt::TextHideMnemonic;
        }
        style->drawItemText(p,
                            subElementRect(SE_TabBarTabText, opt, w),
                            alignment,
                            opt->palette,
                            true,
                            opt->text,
                            QPalette::HighlightedText);
    }
    else
    {
        style->drawControl(CE_TabBarTab,opt,p,w);
    }
}

void KreogistCuteStyle::drawMenuItem(const QStyleOptionMenuItem *opt,
                                     QPainter *p,
                                     const QWidget *w) const
{
    switch(opt->menuItemType)
    {
    case QStyleOptionMenuItem::SubMenu:
    case QStyleOptionMenuItem::Normal:
    {
        //Ok, it's a hack-way to accomplished our design.

        QStyleOptionMenuItem tmp=*opt;
        tmp.icon=QIcon();

        style->drawControl(CE_MenuItem,&tmp,p,w);
        int iRectX=opt->rect.x(),
            iRectY=opt->rect.y(),
            iRectW=opt->rect.width(),
            iRectH=opt->rect.height();

        QPen pen;
        if(!opt->icon.isNull())
        {
            p->drawPixmap(11,
                          iRectY + (iRectH - 30)/2,
                          30,
                          30,
                          opt->icon.pixmap(30, 30));
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
    switch(pe)
    {
    case PE_IndicatorTabClose: {
        QIcon tabBarcloseButtonIcon;
        tabBarcloseButtonIcon.addPixmap(QPixmap(
                    QLatin1String(":/toolbutton/image/TabCloseNormal.png")),
                    QIcon::Normal, QIcon::Off);
        tabBarcloseButtonIcon.addPixmap(QPixmap(
                    QLatin1String(":/toolbutton/image/TabCloseDown.png")),
                    QIcon::Normal, QIcon::On);
        tabBarcloseButtonIcon.addPixmap(QPixmap(
                    QLatin1String(":/toolbutton/image/TabCloseHover.png")),
                    QIcon::Active, QIcon::Off);
        int size = proxy()->pixelMetric(QStyle::PM_SmallIconSize);
        QIcon::Mode mode = opt->state & State_Enabled ?
                            (opt->state & State_Raised ? QIcon::Active : QIcon::Normal)
                            : QIcon::Disabled;
        if (!(opt->state & State_Raised)
            && !(opt->state & State_Sunken)
            && !(opt->state & QStyle::State_Selected))
            mode = QIcon::Disabled;

        QIcon::State state = opt->state & State_Sunken ? QIcon::On : QIcon::Off;
        QPixmap pixmap = tabBarcloseButtonIcon.pixmap(size, mode, state);
        proxy()->drawItemPixmap(p, opt->rect, Qt::AlignCenter, pixmap);
        break;
    }
    default:
        style->drawPrimitive(pe,opt,p,w);
    }
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
            const QStyleOptionMenuItem* _opt_menu_item=qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
            QSize ret=style->sizeFromContents(ct,opt,contentsSize,widget);
            if(_opt_menu_item->menuItemType != QStyleOptionMenuItem::Separator)
            {
                ret.setHeight(42);
            }
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
    switch(standardIcon)
    {
    case QStyle::SP_TitleBarCloseButton:
        return QIcon(QString(":/toolbutton/image/Close.png"));
    case QStyle::SP_TitleBarMaxButton:
        return QIcon(QString(":/toolbutton/image/Maxmized.png"));
    case QStyle::SP_TitleBarNormalButton:
        return QIcon(QString(":/toolbutton/image/Normalmized.png"));
    default:
        return style->standardIcon(standardIcon,option,widget);
    }
}
QPixmap KreogistCuteStyle::standardPixmap(StandardPixmap standardPixmap,
                                          const QStyleOption *opt,
                                          const QWidget *widget) const
{
    switch(standardPixmap)
    {

    default:
        return style->standardPixmap(standardPixmap,opt,widget);
    }
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
