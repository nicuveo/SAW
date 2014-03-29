//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_SHARED_STATEMENT_HH_
# define SAW_SHARED_STATEMENT_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <sqlite3.h>
# include <nauths/saw/detail/cache.hh>
# include <nauths/saw/detail/flag.hh>
# include <nauths/saw/database.hh>
# include <nauths/saw/types.hh>
# include <nauths/saw/row.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class SharedStatement : public detail::Cache<SharedStatement, std::string>
  {
    public:
      // -tors

      SharedStatement(Database db, const char* statement);
      ~SharedStatement();


      // accessors

      int current_row_index() const;
      Row& current_row();

      sqlite3_stmt* data() const;


      // mutators

      bool step(const Statement& stmt);
      int reset();


    private:
      // helpers

      std::string fetch(int i) const;
      void fail(int i) const;


      // data

      Row row_;
      int row_index_;
      detail::Flag row_invalidity_;

      sqlite3_stmt* data_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "shared_statement.hxx"



#endif /* !SAW_SHARED_STATEMENT_HH_ */
