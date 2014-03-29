//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_SHARED_STATEMENT_HXX_
# define SAW_SHARED_STATEMENT_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "shared/shared_statement.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // accessors

  inline int
  SharedStatement::current_row_index() const
  {
    return row_index_;
  }

  inline Row&
  SharedStatement::current_row()
  {
    return row_;
  }


  inline sqlite3_stmt*
  SharedStatement::data() const
  {
    return data_;
  }


}



#endif /* !SAW_SHARED_STATEMENT_HXX_ */
