//
// value.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_VALUE_HH_
# define SAW_VALUE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <string>
# include <vector>
# include <boost/variant.hpp>
# include <boost/lexical_cast.hpp>
# include <saw/types.hh>
# include <saw/blob.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class Value : public boost::variant<Null, Integer, Float, Text, Blob>
  {
    public:
      // types

      typedef boost::variant<Null, Integer, Float, Text, Blob> Super;


      // constructors

      Value(Integer x);
      Value(Float x);
      Value(Text x);
      Value(Blob x);
      Value(Null x);
      Value();


      // helper constructors

      Value(int x);         // -> Integer
      Value(float x);       // -> Float
      Value(const char* x); // -> Text


      // data info

      bool null() const;


      // data conversion

      template <typename Visitor>
      Integer as_integer(Visitor const& converter) const;
      Integer as_integer()                         const;

      template <typename Visitor>
      Float   as_float(Visitor const& converter)   const;
      Float   as_float()                           const;

      template <typename Visitor>
      Text    as_text(Visitor const& converter)    const;
      Text    as_text()                            const;

      template <typename Visitor>
      Blob    as_blob(Visitor const& converter)    const;
      Blob    as_blob()                            const;

      template <typename Result>
      Result  as()                                 const;


      // visitor entry point

      template <typename Visitor>
      typename Visitor::result_type apply(Visitor const& visitor) const;


      // default converters

      template <typename R>
      class DefaultConverter : public boost::static_visitor<R>
      {
        public:
          template <typename T>
          R operator()(T const&) const;
      };

      static Integer to_integer(Integer const&);
      static Integer to_integer(Float const&);
      static Integer to_integer(Text const&);
      static Integer to_integer(Blob const&);
      static Integer to_integer(Null const&);

      static Float to_float(Integer const&);
      static Float to_float(Float const&);
      static Float to_float(Text const&);
      static Float to_float(Blob const&);
      static Float to_float(Null const&);

      static Text to_text(Integer const&);
      static Text to_text(Float const&);
      static Text to_text(Text const&);
      static Text to_text(Blob const&);
      static Text to_text(Null const&);

      static Blob to_blob(Integer const&);
      static Blob to_blob(Float const&);
      static Blob to_blob(Text const&);
      static Blob to_blob(Blob const&);
      static Blob to_blob(Null const&);
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/value.hxx>



#endif /* !SAW_VALUE_HH_ */
