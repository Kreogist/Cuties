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

#ifndef KREOGISTCUTESTYLE_H
#define KREOGISTCUTESTYLE_H

#include <QCommonStyle>
#include <QStyleOptionMenuItem>
#include <QStyle>
#include <QStyleFactory>
#include <QPainter>
#include <QIcon>
#include <QDebug>

class KreogistCuteStyle : public QCommonStyle
{
    Q_OBJECT
public:
    explicit KreogistCuteStyle();
    ~KreogistCuteStyle();

    void drawControl(ControlElement element,
                     const QStyleOption *opt,
                     QPainter *p,
                     const QWidget *w) const;

    void drawPrimitive(PrimitiveElement pe,
                       const QStyleOption *opt,
                       QPainter *p,
                       const QWidget *w) const;

    void drawComplexControl(ComplexControl cc,
                            const QStyleOptionComplex *opt,
                            QPainter *p,
                            const QWidget *w) const;

    QSize sizeFromContents(ContentsType ct,
                          const QStyleOption *opt,
                          const QSize &contentsSize,
                          const QWidget *widget) const;

    virtual int pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const;
    QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = 0) const;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                     const QPoint &pt, const QWidget *w = 0) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt,
                         SubControl sc, const QWidget *widget) const;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap,
                                const QStyleOption *opt) const;
    int styleHint(StyleHint hint, const QStyleOption *option = 0, const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;
    QRect itemPixmapRect(const QRect &r, int flags, const QPixmap &pixmap) const;
    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *option = 0,
                       const QWidget *widget = 0) const;
    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt,
                           const QWidget *widget = 0) const;
    void drawItemPixmap(QPainter *painter, const QRect &rect,
                        int alignment, const QPixmap &pixmap) const;
    void drawItemText(QPainter *painter, const QRect &rect,
                      int flags, const QPalette &pal, bool enabled,
                      const QString &text, QPalette::ColorRole textRole = QPalette::NoRole) const;
    void polish(QWidget *widget);
    void polish(QApplication *app);
    void polish(QPalette &pal);
    void unpolish(QWidget *widget);
    void unpolish(QApplication *app);

private:
    void drawMenuItem(const QStyleOptionMenuItem *opt,
                      QPainter *p,
                      const QWidget *w) const;
    void drawTabItem(const QStyleOptionTab *opt,
                     QPainter *p,
                     const QWidget *w) const;
    QStyle *style;
};

#endif // KREOGISTCUTESTYLE_H
