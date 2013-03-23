//
// database.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_DATABASE_HH_
# define SAW_DATABASE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/detail/owner.hh>
# include <saw/parameter.hh>
# include <saw/types.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class Database : protected detail::Owner<SharedDatabase>
  {
    public:
      // constructors

      Database();
      Database(const char* database);


      // accessors

      bool connected() const;

      Statement make(const char* query) const;

      sqlite3* raw_data() const;


      // mutators

      void connect(const char* db);
      void disconnect();


      // execution

      Rows exec(const char* query) const;
      Rows exec(const char* query, const Parameters& params) const;
      void exec(const char* query, const RowCallback& callback) const;
      void exec(const char* query, const RowCallback& callback, const Parameters& params) const;

      RowRange result(const char* query) const;
      RowRange result(const char* query, const Parameters& params) const;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/database.hxx>



#endif /* !SAW_DATABASE_HH_ */
