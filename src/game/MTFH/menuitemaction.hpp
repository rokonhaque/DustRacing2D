// This file is part of Dust Racing (DustRAC).
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
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

#ifndef MENUITEMACTION_HPP
#define MENUITEMACTION_HPP

namespace MTFH {

//! Base class for menu item actions triggered when
//! the item gets selected.
class MenuItemAction
{
public:

    //! Constructor.
    MenuItemAction();

    //! Called on select.
    virtual void fire()
    {
        // Do nothing by default.
    }

    //! Destructor.
    virtual ~MenuItemAction();

private:
};

} // namespace MTFH

#endif // MENUITEMACTION_HPP