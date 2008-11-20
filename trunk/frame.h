// frame.h -- Names with typed values.
// 
// Copyright 2008 Per Abrahamsen and KVL.
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

#include "syntax.h"
#include <memory>
#include <vector>
#include <boost/noncopyable.hpp>

class AttributeList;
class PLF;

#ifndef FRAME_H
#define FRAME_H

class Frame : private boost::noncopyable
{
  struct Implementation;
  std::auto_ptr<Implementation> impl;

  // Old style access.
private:
  const AttributeList& alist () const;
  const Syntax& syntax () const;
  
  // Common access.
public:
  // Get a list of all entries.
  void entries (std::vector<symbol>&) const;
  unsigned int entries () const;

  // This function will check that the alist conform to the syntax.
  bool check (const Metalib&, Treelog& err) const;
  
  // Check that a numeric value is within the allowed range.
  void check (const symbol key, double value) const;

  // Check than an arbitrary attribute is valid.
  bool check (const Metalib&, const symbol key, Treelog&) const;

  // Extract type information about a specific attribute.
  bool is_const (const symbol) const;
  bool is_optional (const symbol) const;
  bool is_log (const symbol) const;
  bool is_state (const symbol) const;
  Syntax::type lookup (const symbol) const;
  const Syntax& syntax (const symbol) const;
  ::Library& library (const Metalib&, const symbol) const;
  int  size (const symbol) const;
  const symbol dimension (const symbol) const;
  const symbol domain (const symbol) const;
  const symbol range (const symbol) const;
  const symbol description (const symbol) const;
  const AttributeList& default_alist (const symbol) const;

  // Add attribute types.
public:
  void add (const symbol key,	// Generic.
	    Syntax::type t, 
	    Syntax::category cat,
	    int size,
	    const symbol description);
  void add (const symbol key,
	    Syntax::type t, 
	    Syntax::category cat,
	    const symbol description)
  { add (key, t, cat, Syntax::Singleton, description); }

  void add (const symbol key, // Number.
	    const symbol dim,
	    Syntax::category cat,
	    int size,
	    const symbol description);
  void add (const symbol key, 
	    const symbol dim,
	    Syntax::category cat,
	    const symbol description)
  { add (key, dim, cat, Syntax::Singleton, description); } 
  void add (const symbol key,
	    const symbol dim,
	    const Check& check,
	    Syntax::category cat,
	    int size,
	    const symbol description);
  void add (const symbol key, 
	    const symbol dim,
	    const Check& check,
	    Syntax::category cat,
	    const symbol description)
  { add (key, dim, check, cat, Syntax::Singleton, description); } 
  void add_fraction (const symbol key, 
		     Syntax::category cat,
		     int size,
		     const symbol description);
  void add_fraction (const symbol key, 
		     Syntax::category cat,
		     const symbol description);

  void add (const symbol key, // PLF.
	    const symbol domain,
	    const symbol range,
	    Syntax::category cat,
	    int size,
	    const symbol description);
  void add (const symbol key, 
	    const symbol domain,
	    const symbol range,
	    Syntax::category cat,
	    const symbol description)
  { add (key, domain, range, cat, Syntax::Singleton, description); } 
  void add (const symbol key,
	    const symbol domain,
	    const symbol range,
	    const Check& check,
	    Syntax::category cat,
	    int size,
	    const symbol description);
  void add (const symbol key, 
	    const symbol domain,
	    const symbol range,
	    const Check& check,
	    Syntax::category cat,
	    const symbol description)
  { add (key, domain, range, check, cat, Syntax::Singleton, description); } 

  void add (const symbol key,  // AList
	    const Syntax& syntax,
	    int size,
	    const symbol description)
  { add (key, syntax, Syntax::State, size, description); }
  void add (const symbol key,  // AList
	    const Syntax& syntax,
	    const symbol description)
  { add (key, syntax, Syntax::State, Syntax::Singleton, description); }
  void add (const symbol, const Syntax&,
	    Syntax::category cat, int size, 
	    const symbol description);
  void add (const symbol, const Syntax&, const AttributeList&,	
	    // Alist sequence with default element.
	    Syntax::category, int size, const symbol description);

  void add_object (const symbol key,// Object
                   const char *const lib, 
                   const symbol description)
  { add_object (key, lib, Syntax::State, Syntax::Singleton, description); }
  void add_object (const symbol, const char* lib,
                   Syntax::category, int size, const symbol description);
  void add_object (const symbol, symbol lib,
                   Syntax::category, int size, const symbol description);

  void add_library (const symbol, symbol lib);

  typedef void (*load_syntax_fun) (Syntax& syntax, AttributeList& alist);
  void add_submodule (const symbol name, AttributeList& alist,
		      Syntax::category cat, const symbol description,
		      load_syntax_fun load_syntax);
  void add_submodule_sequence (const symbol name, Syntax::category cat, 
			       const symbol description,
			       load_syntax_fun load_syntax);

  // Additional type constraints for a single attribute value. 
  void add_check (const symbol name, const VCheck& vcheck);

  // It is possible to impose an order on the syntax entries, which
  // will allow the input module to parse the entries without the user
  // having to specify the names of the entries.  It is recommended
  // *not* to use this in general, as it makes it more difficult to
  // add new entries.
public:
  void order (const std::vector<symbol>&);
  void order (const symbol);
  void order (const symbol, const symbol);
  void order (const symbol, const symbol, const symbol);
  void order (const symbol, const symbol, const symbol,
	      const symbol);
  void order (const symbol, const symbol, const symbol,
	      const symbol,
	      const symbol);

  // Extract the imposed order.
  bool ordered () const;
  const std::vector<symbol>& order () const;
  int order_index (const symbol name) const; // Return index in order, or -1
  bool total_order () const;	// True iff all members are ordered.

  // Additional constraints involving multiple attributes.
public:
  void add_check (Syntax::check_fun);
  void add_object_check (Syntax::check_object);

  // Is 'key' an element of this alist?
  bool check (const symbol key) const;

  // Extract attribute values.
public:
  double number (const symbol) const;
  double number (const symbol, double default_value) const;
  symbol name (const symbol) const;
  symbol name (const symbol, const symbol default_value) const;
  bool flag (const symbol) const;
  bool flag (const symbol, bool default_value) const;
  const PLF& plf (const symbol) const;
  AttributeList& alist (const symbol) const;
  int integer (const symbol) const;
  int integer (const symbol, int default_value) const;
  const std::vector<double>& number_sequence (const symbol) const;
  const std::vector<symbol>& name_sequence (const symbol key) const;
  const std::vector<bool>& flag_sequence (const symbol key) const;
  const std::vector<int>& integer_sequence (const symbol key) const;
  const std::vector<const PLF*>& plf_sequence (const symbol key) const;
  const std::vector<const AttributeList*>& 
  /**/ alist_sequence (const symbol key) const;

  // Set attribute values.
public:
  void add (const symbol, double);
  void add (const symbol, double, const symbol);
  void add (const symbol, const char*);
  void add (const symbol, const symbol);
  void add (const symbol, bool);
  void add (const symbol, int);
  void add (const symbol, const AttributeList&);
  void add (const symbol, const PLF&);
  void add (const symbol, const std::vector<double>&);
  void add (const symbol, const std::vector<symbol>&);
  void add_strings (const symbol key, const symbol a);
  void add_strings (const symbol key,
                    const symbol a, const symbol b);
  void add_strings (const symbol key,
                    const symbol a, const symbol b,
                    const symbol c);
  void add (const symbol, const std::vector<bool>&);
  void add (const symbol, const std::vector<int>&);
  void add (const symbol, const std::vector<const AttributeList*>&);
  void add (const symbol, const std::vector<const PLF*>&);

  // Create and Destroy.
public:
  enum parent_relationship_t { parent_inherit };
  Frame (const Frame&, parent_relationship_t);
  Frame ();
  ~Frame ();
};

#endif // FRAME_H
