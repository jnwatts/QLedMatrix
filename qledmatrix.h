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

#ifndef QLEDMATRIX_H
#define QLEDMATRIX_H

#include <QtGui/qwidget.h>
#include <QtDesigner/QDesignerExportWidget>

class QLedMatrixPrivate;
class QDESIGNER_WIDGET_EXPORT QLedMatrix: public QWidget
{
    Q_OBJECT
    Q_ENUMS(LEDColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(Qt::BGMode backgroundMode READ backgroundMode WRITE setBackgroundMode)
    Q_PROPERTY(QColor darkLedColor READ darkLedColor WRITE setDarkLedColor)
    Q_PROPERTY(int rows READ rowCount WRITE setRowCount)
    Q_PROPERTY(int columns READ columnCount WRITE setColumnCount)

    public:
        QLedMatrix(QWidget* parent = 0);
        virtual ~QLedMatrix();

        enum LEDColor
        {
            NoColor   = 0xFF222222,

            Red       = 0xFFFF0000,
            Green     = 0xFF00FF00,
            Blue      = 0xFF0000FF,

            White     = 0xFFFFFFFF,
            Orange    = 0xFFFF8800,
            OrangeRed = 0xFFFF2200,
            Yellow    = 0xFFFFFF00
        };

        void clear();

        QColor backgroundColor() const;
        void setBackgroundColor(const QColor& color);

        Qt::BGMode backgroundMode() const;
        void setBackgroundMode(Qt::BGMode mode);

        QColor darkLedColor() const;
        void setDarkLedColor(const QColor& color);

        QRgb colorAt(int row, int col) const;
        void setColorAt(int row, int col, QRgb rgb);

        int rowCount() const;
        void setRowCount(int rows);

        int columnCount() const;
        void setColumnCount(int columns);

        QSize sizeHint() const;

    protected:
        QLedMatrixPrivate* const d_ptr;
        void paintEvent(QPaintEvent* event);

    private:
        Q_DISABLE_COPY(QLedMatrix)
        Q_DECLARE_PRIVATE(QLedMatrix)
};

#endif // QLEDMATRIX_H
