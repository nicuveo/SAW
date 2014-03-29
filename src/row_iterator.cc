//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <nauths/saw/statement.hh>
#include <nauths/saw/exceptions.hh>
#include <nauths/saw/row_iterator.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // constructors

  RowIterator::RowIterator()
  {
  }

  RowIterator::RowIterator(const Statement& stmt)
    : stmt_(stmt)
  {
  }



  // internal core members

  bool
  RowIterator::equal(const RowIterator& other) const
  {
    return stmt_.raw_data() == other.stmt_.raw_data();
  }

  Row&
  RowIterator::dereference() const
  {
    if (stmt_.empty())
      throw LogicError("dereference: empty iterator");

    return stmt_.current_row();
  }

  void
  RowIterator::increment()
  {
    if (stmt_.empty())
      throw LogicError("increment: empty iterator");
    if (stmt_.ready())
      throw LogicError("increment: invalid iterator");

    *this = stmt_.next();
  }


}
