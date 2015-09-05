//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_ROW_ITERATOR_HH_
# define SAW_ROW_ITERATOR_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/iterator/iterator_facade.hpp>
# include <nauths/saw/types.hh>
# include <nauths/saw/row.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class RowIterator : public boost::iterator_facade<RowIterator, Row, boost::single_pass_traversal_tag>
  {
    public:
      // types

      typedef boost::iterator_facade<RowIterator, Row, boost::single_pass_traversal_tag> Super;


      // constructors

      RowIterator();


    private:
      // internal constructors

      friend class Statement;

      RowIterator(const Statement& stmt);


      // internal core members

      friend class boost::iterator_core_access;

      bool equal(const RowIterator&) const;
      Row& dereference() const;
      void increment();


      // data

      Statement stmt_;
  };

}



#endif /* !SAW_ROW_ITERATOR_HH_ */
