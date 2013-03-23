//
// row_iterator.cc for saw
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <saw/statement.hh>
#include <saw/row_iterator.hh>



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
      std::abort();

    return stmt_.current_row();
  }

  void
  RowIterator::increment()
  {
    if (stmt_.empty() or stmt_.ready())
      std::abort();

    *this = stmt_.next();
  }


}
