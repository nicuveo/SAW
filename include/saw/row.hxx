//
// row.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_ROW_HXX_
# define SAW_ROW_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/row.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // accessors

  inline int
  Row::index() const
  {
    return index_;
  }

  inline int
  Row::columns_number() const
  {
    return stmt_.columns_number();
  }


  inline bool
  Row::outdated() const
  {
    return watcher_.obsolete();
  }


  inline Statement
  Row::statement() const
  {
    return stmt_;
  }

  inline Database
  Row::database() const
  {
    return stmt_.database();
  }


}



#endif /* !SAW_ROW_HXX_ */
