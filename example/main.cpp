/*******************************************************************************
**
**  Copyright (C) 2009 Pierre-Etienne Messier <pierre.etienne.messier@gmail.com>
**                     http://pemessier.hexpresso.org/
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#include <QApplication>
#include <QImage>

#include <qledmatrix.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QLedMatrix matrix;
    matrix.setColumnCount(64);
    matrix.setRowCount(16);
    matrix.show();

    QImage img(":/HelloWorld.png");
    for(int row=0; row < matrix.rowCount(); ++row)
    {
        for(int col=0; col < matrix.columnCount(); ++col)
        {
            // Monochrome display
            if(img.pixel(col, row) == 0xFFFFFFFF)
            {
                // White pixels will be shown as red LEDs
                matrix.setColorAt(row, col, QLedMatrix::Red);
            }
            else
            {
                // Other pixels shown as dark LEDs
                matrix.setColorAt(row, col, QLedMatrix::NoColor);
            }
        }
    }

    return app.exec();
}
