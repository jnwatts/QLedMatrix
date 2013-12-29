/*******************************************************************************
**
**  Copyright (C) 2009 Pierre-Etienne Messier <pierre.etienne.messier@gmail.com>
**                     http://pemessier.hexpresso.org/
**
**  This library is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#include "qledmatrix.h"

#include <qpainter.h>

/**
 * \internal
 */
class QLedMatrixPrivate
{
    Q_DECLARE_PUBLIC(QLedMatrix)

    public:
        bool isValid(int row, int col) const;
        void setColorAt(int row, int col, QRgb rgb, bool doUpdate);
        void drawLEDs(QPainter& painter);
        void calculateAspectRatio();

        QLedMatrix* q_ptr;
        QBrush backgroundBrush;
        Qt::BGMode backgroundMode;
        QColor darkLedColor;
        QVector< QVector<QRgb> > colorTable;
        int rowCount;
        int columnCount;
        qreal rowHeight;
        qreal columnWidth;
        qreal aspectRatio;
};

/**
 * \internal
 */
bool QLedMatrixPrivate::isValid(int row, int col) const
{
    return ( (row >= 0) &&
             (row < rowCount) &&
             (col >= 0) &&
             (col < columnCount) );
}

/**
 * \internal
 */
void QLedMatrixPrivate::setColorAt(int row, int col, QRgb rgb, bool doUpdate)
{
    Q_Q(QLedMatrix);
    if(isValid(row, col))
    {
        colorTable[col][row] = rgb;

        if(doUpdate == true)
        {
            q->update();
        }
    }
    else
    {
        qWarning("QLedMatrix::setColorAt: coordinate (row=%d, col=%d) out of range", row, col);
    }
}

/**
 * \internal
 */
void QLedMatrixPrivate::drawLEDs(QPainter& painter)
{
    Q_Q(QLedMatrix);
    for(int row=0; row < rowCount; ++row)
    {
        painter.save();
        for(int col=0; col < columnCount; ++col)
        {
            painter.setBrush(QColor(q->colorAt(row, col)));
            painter.drawEllipse(QRectF(0.0, 0.0, 8.0, 8.0));
            painter.translate(10.0, 0.0);
        }
        painter.restore();
        painter.translate(0.0, 10.0);
    }
}

/**
 * \internal
 */
void QLedMatrixPrivate::calculateAspectRatio()
{
    if(rowHeight > 0.0)
    {
        aspectRatio = columnWidth / rowHeight;
    }
}

//////////////////////////////////

/**
 * \class QLedMatrix
 *
 * \brief The QLedMatrix widget simulates a LED matrix (dot matrix) display.
 *
 * A LED matrix display is a 2-dimensional array of dots used to generate
 * characters, symbols and images. It is often seen on machines, clocks and
 * display boards.
 *
 * This generic implementation can configured for any size of rows (greater
 * than 0) and columns. The number of colors is not limited, therefore it can
 * be used to make a monochrome, bi-color or even a full RGB display.
 *
 * Individual LEDs can be addressed in the matrix by their row and column
 * position. The index (0,0) is located in the upper left corner. Columns
 * grow from left to right, and rows grow from top to bottom.
 *
 * \version 0.6
 *
 * \author Pierre-Etienne Messier  <pierre.etienne.messier\@gmail.com>
 */

/**
 * \enum QLedMatrix::LEDColor
 *
 * This type defines standard LED colors in the QRgb format, provided purely
 * for convenience.
 *
 * \sa QRgb
 */

/**
 * \var QLedMatrix::LEDColor QLedMatrix::NoColor
 * Default dark LED color (\#222222)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::Red
 * Red (\#FF0000)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::Green
 * Green (\#00FF00)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::Blue
 * Blue (\#0000FF)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::White
 * White (\#FFFFFF)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::Orange
 * Orange (\#FF8800)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::OrangeRed
 * Orange-Red (\#FF2200)
 **/

/**
 * \var QLedMatrix::LEDColor QLedMatrix::Yellow
 * Yellow (\#FFFF00)
 **/

/**
 * Constructs a LED Matrix display, sets the background color to black,
 * the background mode to opaque, the dark LED color to QLedMatrix::NoColor and
 * the number of rows and columns to 0.
 *
 * \sa setBackgroundColor(), setBackgroundMode(), setDarkLedColor(),
 *     setRowCount(), setColumnCount()
 *
 * \param parent parent QWidget
 */
QLedMatrix::QLedMatrix(QWidget* parent): QWidget(parent),
    d_ptr(new QLedMatrixPrivate)
{
    Q_D(QLedMatrix);
    d->q_ptr = this;
    d->backgroundBrush = QBrush(Qt::black, Qt::SolidPattern);
    d->backgroundMode = Qt::OpaqueMode;
    d->darkLedColor = QColor(QLedMatrix::NoColor);
    d->rowCount = 0;
    d->columnCount = 0;
    d->rowHeight = 0.0;
    d->columnWidth = 0.0;
    d->aspectRatio = 0.0;
}

/**
 * Destroys the LED Matrix display.
 */
QLedMatrix::~QLedMatrix()
{
    delete d_ptr;
}

/**
 * \brief Clears the LED Matrix display.
 *
 * When the display is cleared, all the LEDs are set to the dark LED color.
 *
 * \sa darkLedColor(), setDarkLedColor()
 */
void QLedMatrix::clear()
{
    Q_D(QLedMatrix);
    for(int i=0; i < d->rowCount; ++i)
    {
        for(int j=0; j < d->columnCount; ++j)
        {
            d->colorTable[j][i] = d->darkLedColor.rgb();
        }
    }
    update();
}

/**
 * \brief Returns the background color of the widget.
 *
 * \return background color of the widget
 *
 * \sa setBackgroundColor()
 */
QColor QLedMatrix::backgroundColor() const
{
    Q_D(const QLedMatrix);
    return d->backgroundBrush.color();
}

/**
 * \brief Sets the background color of the widget to the given color.
 *
 * The background color of the widget will only be visible if the background
 * mode is set to Qt::OpaqueMode.
 *
 * \param color the background color to be set
 *
 * \sa backgroundColor(), backgroundMode(), setBackgroundMode()
 */
void QLedMatrix::setBackgroundColor(const QColor& color)
{
    Q_D(QLedMatrix);
    d->backgroundBrush.setColor(color);
    update();
}

/**
 * \brief Returns the background mode of the widget.
 *
 * \return background mode of the widget
 *
 * \sa setBackgroundMode()
 */
Qt::BGMode QLedMatrix::backgroundMode() const
{
    Q_D(const QLedMatrix);
    return d->backgroundMode;
}

/**
 * \brief Sets the background mode of the widget to the given mode.
 *
 * Qt::OpaqueMode (the default) fills the widget's background with the current
 * background color. Qt::TransparentMode doesn't draw any background color.
 *
 * \param mode the background mode to be set
 *
 * \sa backgroundMode(), backgroundColor(), setBackgroundColor()
 */
void QLedMatrix::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(QLedMatrix);
    d->backgroundMode = mode;
    update();
}

/**
 * \brief Returns the dark LED color.
 *
 * \return dark LED color
 *
 * \sa setDarkLedColor()
 */
QColor QLedMatrix::darkLedColor() const
{
    Q_D(const QLedMatrix);
    return d->darkLedColor;
}

/**
 * \brief Sets the dark LED color to the given color.
 *
 * The dark LED color is used to represent a LED in the 'off' state. It is
 * used when adding rows or cols, and when using the clear() method.
 *
 * \param color the color to be set
 *
 * \sa darkLedColor(), clear(), setRowCount(), setColumnCount()
 */
void QLedMatrix::setDarkLedColor(const QColor& color)
{
    Q_D(QLedMatrix);
    QRgb oldColor = d->darkLedColor.rgb();
    d->darkLedColor = color;

    for(int i=0; i < d->rowCount; ++i)
    {
        for(int j=0; j < d->columnCount; ++j)
        {
            if(d->colorTable[j][i] == oldColor)
            {
                d->colorTable[j][i] = d->darkLedColor.rgb();
            }
        }
    }
    update();
}

/**
 * \brief Returns the color of the LED at the specified position.
 *
 * This function uses the QRgb data format. If the specified position is
 * invalid, this function will return the current dark LED color.
 *
 * \param row the row index of the LED
 * \param col the column index of the LED
 *
 * \return the color of the LED at the given position
 *
 * \sa setColorAt(), darkLedColor()
 */
QRgb QLedMatrix::colorAt(int row, int col) const
{
    Q_D(const QLedMatrix);
    if(d->isValid(row, col))
    {
        return d->colorTable[col][row];
    }

    qWarning("QLedMatrix::colorAt: coordinate (row=%d, col=%d) out of range", row, col);
    return d->darkLedColor.rgb();
}

/**
 * \brief Sets the given color to the LED at the specified position.
 *
 * If the specified position is invalid, this function will do nothing.
 *
 * \param row the row index of the LED
 * \param col the column index of the LED
 * \param rgb the color to be set (in QRgb format)
 *
 * \sa colorAt()
 */
void QLedMatrix::setColorAt(int row, int col, QRgb rgb)
{
    Q_D(QLedMatrix);
    d->setColorAt(row, col, rgb, true);
}

/**
 * \brief Returns the number of rows in the LED matrix display.
 *
 * \return the number of rows in the LED matrix display
 *
 * \sa setRowCount(), columnCount()
 */
int QLedMatrix::rowCount() const
{
    Q_D(const QLedMatrix);
    return d->rowCount;
}

/**
 * \brief Sets the number of rows in the LED matrix display.
 *
 * This function will do nothing if the new number of rows is less than 0
 * or if it is equal to the current number of rows. If the new number of
 * rows is less than the current number of rows, the display will be
 * cropped to the new value. Otherwise, if the new number of rows is
 * greater than the current number of rows, the new LEDs will be
 * initialized using the dark LED color.
 * 
 * \param rows the new number of rows
 *
 * \sa rowsCount(), setColumnCount(), darkLedColor()
 */
void QLedMatrix::setRowCount(int rows)
{
    Q_D(QLedMatrix);
    if((rows >= 0) && (rows != d->rowCount))
    {
        int previousRowCount = d->rowCount;
        d->rowCount = rows;
        d->rowHeight = 10.0 * rows;
        d->calculateAspectRatio();

        for(int i=0; i < d->columnCount; ++i)
        {
            d->colorTable[i].resize(rows);
            if(rows > previousRowCount)
            {
                for(int j=previousRowCount; j < rows; ++j)
                {
                    d->setColorAt(j, i, d->darkLedColor.rgb(), false);
                }
            }
        }

        update();
    }
}

/**
 * \brief Returns the number of columns in the LED matrix display.
 *
 * \return the number of columns in the LED matrix display
 *
 * \sa setColumnCount(), rowCount()
 */
int QLedMatrix::columnCount() const
{
    Q_D(const QLedMatrix);
    return d->columnCount;
}

/**
 * \brief Sets the number of columns in the LED matrix display.
 *
 * This function will do nothing if the new number of columns is less than 0
 * or if it is equal to the current number of columns. If the new number of
 * columns is less than the current number of columns, the display will be
 * cropped to the new value. Otherwise, if the new number of columns is
 * greater than the current number of columns, the new LEDs will be
 * initialized using the dark LED color.
 * 
 * \param columns the new number of columns
 *
 * \sa columnCount(), setRowCount(), darkLedColor()
 */
void QLedMatrix::setColumnCount(int columns)
{
    Q_D(QLedMatrix);
    if((columns >= 0) && (columns != d->columnCount))
    {
        int previousColumnsCount = d->columnCount;
        d->columnCount = columns;
        d->columnWidth = 10.0 * columns; 
        d->calculateAspectRatio();

        d->colorTable.resize(columns);
        if(columns > previousColumnsCount)
        {
            for(int i=previousColumnsCount; i<columns; ++i)
            {
                d->colorTable[i].resize(d->rowCount);
                for(int j=0; j < d->rowCount; ++j)
                {
                    d->setColorAt(j, i, d->darkLedColor.rgb(), false);
                }
            }
        }

        update();
    }
}

/**
 * \internal
 * Reimplemented from QWidget::sizeHint()
 */
QSize QLedMatrix::sizeHint() const
{
    Q_D(const QLedMatrix);
    if((d->rowCount > 0) && (d->columnCount > 0))
    {
        return QSizeF(d->columnWidth, d->rowHeight).toSize();
    }
    else
    {
        qWarning("QLedMatrix::sizeHint: no rows or columns to display, defaulting size to (10,10)");
        return QSize(10, 10);
    }
}

/**
 * \internal
 * Reimplemented from QWidget::paintEvent()
 */
void QLedMatrix::paintEvent(QPaintEvent* /* event */)
{
    Q_D(QLedMatrix);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    if(d->backgroundMode == Qt:: OpaqueMode)
    {
        painter.setBrush(d->backgroundBrush);
        painter.drawRect(0, 0, width(), height());
    }

    if((d->rowHeight > 0.0) && (d->columnWidth > 0.0))
    {
        const qreal w = width();
        const qreal h = height();
        const qreal currentAspectRatio  = w / h;

        painter.translate(w / 2.0, h / 2.0);

        // Set the scale factor to keep the aspect ratio
        if(currentAspectRatio > d->aspectRatio)
        {
            qreal side = h / d->rowHeight;
            painter.scale(side, side);
        }
        else if(currentAspectRatio < d->aspectRatio)
        {
            qreal side = w / d->columnWidth;
            painter.scale(side, side);
        }
        else
        {
            painter.scale(w / d->columnWidth, h / d->rowHeight);
        }

        painter.translate(1.0 - (d->columnWidth/2), 1.0 - (d->rowHeight/2));
        d->drawLEDs(painter);
    }
}
