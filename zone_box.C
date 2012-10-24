// zone_box.C - A zone defined by intervals on each axis.
// 
// Copyright 2006, 2012 Per Abrahamsen and KVL.
//
// This file is part of Daisy.
// 
// Daisy is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
// 
// Daisy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.
// 
// You should have received a copy of the GNU Lesser Public License
// along with Daisy; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#define BUILD_DLL
#include "zone.h"
#include "bound.h"
#include "librarian.h"
#include "block_model.h"

class Bound;

struct ZoneBox : public Zone
{
  std::auto_ptr<Bound> bottom;
  std::auto_ptr<Bound> top;
  std::auto_ptr<Bound> left;
  std::auto_ptr<Bound> right;
  std::auto_ptr<Bound> front;
  std::auto_ptr<Bound> back;

  // Use.
  static bool in_interval (const double point, 
                           const Bound& from, const Bound& to);
  bool contain_point (double z, double x, double y) const;

  // Create and Destroy.
  ZoneBox (const BlockModel& al);
  ~ZoneBox ();
};

bool 
ZoneBox::in_interval (const double point, const Bound& from, const Bound& to)
{
  if (from.type () == Bound::finite
      && point <= from.value ())
    // Point before interval.
    return false;
  if (to.type () == Bound::finite
      && point > to.value ())
    // Point after interval.
    return false;

  // Point in interval.
  return true;
}

bool 
ZoneBox::contain_point (double z, double x, double y) const
{ return in_interval (z, *bottom, *top)
    && in_interval (x, *left, *right)
    && in_interval (y, *front, *back);
}

ZoneBox::ZoneBox (const BlockModel& al)
  : Zone (al),
    bottom (Librarian::build_item<Bound> (al, "bottom")),
    top (Librarian::build_item<Bound> (al, "top")),
    left (Librarian::build_item<Bound> (al, "left")),
    right (Librarian::build_item<Bound> (al, "right")),
    front (Librarian::build_item<Bound> (al, "front")),
    back (Librarian::build_item<Bound> (al, "back"))
{ }
  
ZoneBox::~ZoneBox ()
{ }

static struct Zone_BoxSyntax : public DeclareModel
{
  Model* make (const BlockModel& al) const
  { return new ZoneBox (al); }
  Zone_BoxSyntax ()
    : DeclareModel (Zone::component, "box", "\
A zone defined by intervals on each axis.\n\
By default, the intervals fill the entire axis.  You can modify this by\n\
setting the parameters.")
  { }
  void load_frame (Frame& frame) const
  {
    frame.declare_object ("bottom", Bound::component, 
                          Attribute::State, Attribute::Singleton,
                          "Lower boundary on the z-axis.");
    frame.set ("bottom", "empty");
    frame.declare_object ("top", Bound::component,
                          Attribute::State, Attribute::Singleton,
                          "Upper boundary on the z-axis.");
    frame.set ("top", "empty");
    frame.declare_object ("left", Bound::component,
                          Attribute::State, Attribute::Singleton,
                          "Lower boundary on the x-axis.");
    frame.set ("left", "empty");
    frame.declare_object ("right", Bound::component,
                          Attribute::State, Attribute::Singleton,
                          "Upper boundary on the x-axis.");
    frame.set ("right", "empty");
    frame.declare_object ("front", Bound::component,
                          Attribute::State, Attribute::Singleton,
                          "Lower boundary on the y-axis.");
    frame.set ("front", "empty");
    frame.declare_object ("back", Bound::component,
                          Attribute::State, Attribute::Singleton,
                          "Upper boundary on the y-axis.");
    frame.set ("back", "empty");
  }
} ZoneBox_syntax;

// zone_box.C ends here.