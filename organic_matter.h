// organic_matter.h
// 
// Copyright 1996-2001 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001 KVL.
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


#ifndef ORGANIC_MATTER_H
#define ORGANIC_MATTER_H

#include "common.h"

class AttributeList;
class Syntax;
class Log;
class AM;
class Geometry;
class Soil;
class SoilWater;
class SoilHeat;
class SoilNO3;
class SoilNH4;
class Time;
class Treelog;

class OrganicMatter
{
  // Content.
private:
  struct Implementation;
  Implementation& impl;
  
  // Simulation.
public:
  void monthly (const Geometry& soil);
  void tick (const Soil&, const SoilWater&, const SoilHeat&, 
	     SoilNO3&, SoilNH4&);
  void output (Log&, const Geometry&) const;
  double CO2 (unsigned int i) const;	// [g C/cm�]
  void mix (const Geometry&, double from, double to, double penetration, 
	    const Time& time);
  void swap (const Geometry&, double from, double middle, double to, 
	     const Time& time);

  // Communication with external model.
  double get_smb_c_at (unsigned int i) const; // [g C/cm�]

  // Create and Destroy.
  bool check (Treelog& err) const;
  bool check_am (const AttributeList& am, Treelog& err) const;
  void add (AM&);
  AM* find_am (const string& sort, const string& part) const;
public:
  void initialize (const AttributeList&, const Soil&, Treelog&);
  static void load_syntax (Syntax&, AttributeList&);
  OrganicMatter (const AttributeList&);
  ~OrganicMatter ();
};

#endif // ORGANIC_MATTER_H
