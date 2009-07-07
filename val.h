// val.h -- Attribute values.
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

#ifndef VAL_H
#define VAL_H

#include "symbol.h"
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class PLF;
class FrameModel;
class FrameSubmodel;

class Val : public boost::noncopyable
{
public:
  virtual int size () const;
  virtual double number () const;
  virtual symbol name () const;
  virtual bool flag () const;
  virtual const PLF& plf () const;
  virtual const FrameModel& model () const;
  virtual const FrameSubmodel& submodel () const;
  virtual int integer () const;
  virtual const std::vector<double>& number_sequence () const;
  virtual const std::vector<symbol>& name_sequence () const;
  virtual const std::vector<bool>& flag_sequence () const;
  virtual const std::vector<int>& integer_sequence () const;
  virtual const std::vector<boost::shared_ptr<const PLF>/**/>& plf_sequence () const;
  virtual const std::vector<boost::shared_ptr<const FrameModel>/**/>& model_sequence () const;
  virtual const std::vector<boost::shared_ptr<const FrameSubmodel>/**/>& submodel_sequence () const;

protected:
  Val ();
public: 
  virtual ~Val ();
};

class ValNumber : public Val
{
  const double value;
  double number () const;
public:
  ValNumber (const double v);
};

class ValReference : public Val
{
  const symbol value;
  int size () const;
public:
  ValReference (const symbol v);
};

class ValScalar : public Val
{
  const double number_;
  const symbol name_;
  double number () const;
  symbol name () const;
public:
  ValScalar (const double v, const symbol s);
};

class ValString : public Val
{
  const symbol value;
  symbol name () const;
public:
  ValString (const symbol v);
};

class ValBoolean : public Val
{
  const bool value;
  bool flag () const;
public:
  ValBoolean (const bool v);
};

class ValPLF : public Val
{
  boost::shared_ptr<const PLF> value;
  const PLF& plf () const;
public:
  ValPLF (boost::shared_ptr<const PLF> v);
};

class ValObject : public Val
{
  boost::shared_ptr<const FrameModel> value;
  const FrameModel& model () const;
public:
  ValObject (boost::shared_ptr<const FrameModel> f);
};

class ValAList : public Val
{
  boost::shared_ptr<const FrameSubmodel> value;
  const FrameSubmodel& submodel () const;
public:
  ValAList (boost::shared_ptr<const FrameSubmodel> f);
};

class ValInteger : public Val
{
  const int value;
  int integer () const;
public:
  ValInteger (const int v);
};

class ValNumberSeq : public Val
{
  const std::vector<double> value;
  int size () const;
  const std::vector<double>& number_sequence () const;
public:
  ValNumberSeq (const std::vector<double>& v);
};

class ValStringSeq : public Val
{
  const std::vector<symbol> value;
  int size () const;
  const std::vector<symbol>& name_sequence () const;
public:
  ValStringSeq (const std::vector<symbol>& v);
};

class ValBooleanSeq : public Val
{
  const std::vector<bool> value;
  int size () const;
  const std::vector<bool>& flag_sequence () const;
public:
  ValBooleanSeq (const std::vector<bool>& v);
};

class ValIntegerSeq : public Val
{
  const std::vector<int> value;
  int size () const;
  const std::vector<int>& integer_sequence () const;
public:
  ValIntegerSeq (const std::vector<int>& v);
};

class ValPLFSeq : public Val
{
  const std::vector<boost::shared_ptr<const PLF>/**/> value;
  int size () const;
  const std::vector<boost::shared_ptr<const PLF>/**/>& plf_sequence () const;
public:
  ValPLFSeq (const std::vector<boost::shared_ptr<const PLF>/**/>& v);
};

class ValObjectSeq : public Val
{
  const std::vector<boost::shared_ptr<const FrameModel>/**/> value;
  int size () const;
  const std::vector<boost::shared_ptr<const FrameModel>/**/>& model_sequence () const;
public:
  ValObjectSeq (const std::vector<boost::shared_ptr<const FrameModel>/**/>& v);
};

class ValAListSeq : public Val
{
  const std::vector<boost::shared_ptr<const FrameSubmodel>/**/> value;
  int size () const;
  const std::vector<boost::shared_ptr<const FrameSubmodel>/**/>& submodel_sequence () const;
public:
  ValAListSeq (const std::vector<boost::shared_ptr<const FrameSubmodel>/**/>& v);
};

#endif // VAL_H
