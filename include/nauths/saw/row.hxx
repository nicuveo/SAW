//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_ROW_HXX_
# define SAW_ROW_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/row.hh>



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
