// This file belongs to the "MiniCore" game engine.
// Copyright (C) 2010 Jussi Lind <jussi.lind@iki.fi>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA  02110-1301, USA.
//

#include "mcrectshape.hh"
#include "mcrectshapeimpl.hh"
#include "mcshapeview.hh"
#include "mcmathutil.hh"

MCUint MCRectShapeImpl::m_typeID = MCShape::registerType();

MCRectShapeImpl::MCRectShapeImpl(
    MCObject * pParent, MCFloat width, MCFloat height)
: MCShapeImpl(pParent)
, m_obbox(width / 2, height / 2, MCVector2d<MCFloat>())
{}

MCRectShapeImpl::~MCRectShapeImpl()
{}

MCEdge<MCFloat> MCRectShapeImpl::edgeForPoint(const MCVector2d<MCFloat> & p) const
{
    // Cache location
    const MCVector2d<MCFloat> l(m_obbox.location());

    // Translate test point to obbox's coordinates
    const MCVector2d<MCFloat> x(p - l);

    // Cache vertices
    const MCVector2d<MCFloat> v0(m_obbox.vertex(0));
    const MCVector2d<MCFloat> v1(m_obbox.vertex(1));

    // Translate vertices to obbox's coordinates
    MCVector2d<MCFloat> a(v0 - l);
    MCVector2d<MCFloat> b(v1 - l);

    // **** Find the corresponding edge  ****

    if (x * a > 0 && b * x > 0) {
        return MCEdge<MCFloat>(v1 - v0, v0);
    }

    const MCVector2d<MCFloat> v2(m_obbox.vertex(2));

    a = b;
    b = v2 - l;
    if (x * a > 0 && b * x > 0) {
        return MCEdge<MCFloat>(v2 - v1, v1);
    }

    const MCVector2d<MCFloat> v3(m_obbox.vertex(3));

    a = b;
    b = v3 - l;
    if (x * a > 0 && b * x > 0) {
        return MCEdge<MCFloat>(v3 - v2, v2);
    }

    return MCEdge<MCFloat>(v0 - v3, v3);
}

int MCRectShapeImpl::interpenetrationDepth(
    const MCVector2d<MCFloat> & p1, const MCVector2d<MCFloat> & p2) const
{
    MCEdge<MCFloat> edge(edgeForPoint(p2));
    return MCMathUtil::distanceFromVector(p1 - edge.origin, edge.edge);
}

MCRectShape::MCRectShape(
    MCObject * pParent, MCShapeView * pView, MCFloat width, MCFloat height) :
    MCShape(pParent, pView),
    m_pImpl(new MCRectShapeImpl(pParent, width, height))
{}

MCEdge<MCFloat> MCRectShape::edgeForPoint(const MCVector2d<MCFloat> & p) const
{
    return m_pImpl->edgeForPoint(p);
}

void MCRectShape::translate(const MCVector3d<MCFloat> & p)
{
    MCShape::translate(p);
    m_pImpl->m_obbox.translate(p);
}

void MCRectShape::rotate(MCUint a)
{
    MCShape::rotate(a);
    m_pImpl->m_obbox.rotate(angle());
}

MCBBox<MCFloat> MCRectShape::bbox() const
{
    return m_pImpl->m_obbox.bbox();
}

bool MCRectShape::contains(const MCVector2d<MCFloat> & p) const
{
    return m_pImpl->m_obbox.contains(p);
}

int MCRectShape::interpenetrationDepth(
    const MCVector2d<MCFloat> & p1, const MCVector2d<MCFloat> & p2) const
{
    return m_pImpl->interpenetrationDepth(p1, p2);
}

MCVector2d<MCFloat> MCRectShapeImpl::contactNormal(
    const MCVector2d<MCFloat> & p) const
{
    // Get the "nearest" edge for p and build a normal vector from it
    static const MCVector3d<MCFloat> DOWN(0, 0, -1);
    return MCVector2d<MCFloat>(
        (MCVector3d<MCFloat>(edgeForPoint(p).edge) * DOWN)).normalizedFast();
}

MCVector2d<MCFloat> MCRectShape::contactNormal(
    const MCVector2d<MCFloat> & p) const
{
    return m_pImpl->contactNormal(p);
}

MCUint MCRectShape::typeID()
{
    return MCRectShapeImpl::m_typeID;
}

MCUint MCRectShape::instanceTypeID() const
{
    return MCRectShapeImpl::m_typeID;
}

const MCOBBox<MCFloat> & MCRectShape::obbox() const
{
    return m_pImpl->m_obbox;
}

void MCRectShape::resize(MCFloat width, MCFloat height)
{
    m_pImpl->m_obbox =
        MCOBBox<MCFloat>(width / 2, height / 2, location());
    m_pImpl->m_obbox.rotate(angle());
}

MCRectShape::~MCRectShape()
{
    delete m_pImpl;
}
