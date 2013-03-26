//
// shared_statement.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_SHARED_STATEMENT_HH_
# define SAW_SHARED_STATEMENT_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <sqlite3.h>
# include <saw/detail/cache.hh>
# include <saw/detail/flag.hh>
# include <saw/database.hh>
# include <saw/types.hh>
# include <saw/row.hh>



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
