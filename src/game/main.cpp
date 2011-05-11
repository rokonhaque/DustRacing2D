// This file is part of Dust Rallycross (DustRAC).
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
//
// DustRAC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// DustRAC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DustRAC. If not, see <http://www.gnu.org/licenses/>.

#include <QApplication>
#include <QGraphicsView>
#include "MiniWidgets/mwscene.h"
#include "MiniWidgets/mwtext.h"
#include "MiniWidgets/mwselector.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    MWScene scene(840, 400);
    QGraphicsView view;
    view.setScene(&scene);
    MWWidget dummy(QSizeF(840, 400));
    dummy.setPos(420, 200);
//    MWText text("TEST TEST TEST!!!", QSizeF(400, 40), &dummy);
    MWSelector text(QSizeF(400, 40), &dummy);
    text.setBgColor(QColor(0, 0, 128, 196));
    text.setFgColor(QColor(128, 128, 128, 196));
    text.setClickable(true);
    scene.addItem(&dummy);
    scene.addItem(&text);
    view.show();
    return app.exec();
}
