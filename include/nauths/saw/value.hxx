//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_VALUE_HXX_
# define SAW_VALUE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/value.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // data info

  inline bool
  Value::null() const
  {
    return which() == 0;
  }



  // data conversion

  template <typename Visitor>
  inline Integer
  Value::as_integer(Visitor const& converter) const
  {
    return apply(converter);
  }

  inline Integer
  Value::as_integer() const
  {
    return apply(DefaultConverter<Integer>());
  }


  template <typename Visitor>
  inline Float
  Value::as_float(Visitor const& converter) const
  {
    return apply(converter);
  }

  inline Float
  Value::as_float() const
  {
    return apply(DefaultConverter<Float>());
  }


  template <typename Visitor>
  inline Text
  Value::as_text(Visitor const& converter) const
  {
    return apply(converter);
  }

  inline Text
  Value::as_text() const
  {
    return apply(DefaultConverter<Text>());
  }


  template <typename Visitor>
  inline Blob
  Value::as_blob(Visitor const& converter) const
  {
    return apply(converter);
  }

  inline Blob
  Value::as_blob() const
  {
    return apply(DefaultConverter<Blob>());
  }


  template <typename Result>
  inline Result
  Value::as() const
  {
    return apply(DefaultConverter<Result>());
  }



  // visitor entry point

  template <typename Visitor>
  inline typename Visitor::result_type
  Value::apply(Visitor const& visitor) const
  {
    return boost::apply_visitor(visitor, *this);
  }



  // default converters

  inline Integer
  Value::to_integer(Integer const& x)
  {
    return x;
  }

  inline Integer
  Value::to_integer(Float const& x)
  {
    return x;
  }

  inline Integer
  Value::to_integer(Text const& x)
  {
    return boost::lexical_cast<Integer>(x);
  }

  inline Integer
  Value::to_integer(Blob const& x)
  {
    return to_integer(to_text(x));
  }

  inline Integer
  Value::to_integer(Null const&)
  {
    return Integer(0);
  }


  inline Float
  Value::to_float(Integer const& x)
  {
    return x;
  }

  inline Float
  Value::to_float(Float const& x)
  {
    return x;
  }

  inline Float
  Value::to_float(Text const& x)
  {
    return boost::lexical_cast<Float>(x);
  }

  inline Float
  Value::to_float(Blob const& x)
  {
    return to_float(to_text(x));
  }

  inline Float
  Value::to_float(Null const&)
  {
    return Float(0);
  }


  inline Text
  Value::to_text(Integer const& x)
  {
    return boost::lexical_cast<Text>(x);
  }

  inline Text
  Value::to_text(Float const& x)
  {
    return boost::lexical_cast<Text>(x);
  }

  inline Text
  Value::to_text(Text const& x)
  {
    return x;
  }

  inline Text
  Value::to_text(Blob const& x)
  {
    return Text((const char*) &x[0], x.size());
  }

  inline Text
  Value::to_text(Null const&)
  {
    return Text();
  }


  inline Blob
  Value::to_blob(Integer const& x)
  {
    return to_blob(to_text(x));
  }

  inline Blob
  Value::to_blob(Float const& x)
  {
    return to_blob(to_text(x));
  }

  inline Blob
  Value::to_blob(Text const& x)
  {
    return Blob(x);
  }

  inline Blob
  Value::to_blob(Blob const& x)
  {
    return x;
  }

  inline Blob
  Value::to_blob(Null const&)
  {
    return Blob();
  }



  // default converters

  template <>
  template <typename T>
  Integer
  Value::DefaultConverter<Integer>::operator()(T const& x) const
  {
    return to_integer(x);
  }

  template <>
  template <typename T>
  Float
  Value::DefaultConverter<Float>::operator()(T const& x) const
  {
    return to_float(x);
  }

  template <>
  template <typename T>
  Text
  Value::DefaultConverter<Text>::operator()(T const& x) const
  {
    return to_text(x);
  }

  template <>
  template <typename T>
  Blob
  Value::DefaultConverter<Blob>::operator()(T const& x) const
  {
    return to_blob(x);
  }


}



#endif /* !SAW_VALUE_HXX_ */
