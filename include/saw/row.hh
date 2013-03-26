//
// row.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_ROW_HH_
# define SAW_ROW_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <map>
# include <vector>
# include <saw/detail/cache.hh>
# include <saw/detail/flag.hh>
# include <saw/statement.hh>
# include <saw/database.hh>
# include <saw/value.hh>
# include <saw/types.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class Row : public detail::Cache<Row, Value>
  {
    public:
      // accessors

      int index() const;
      int columns_number() const;

      bool outdated() const;

      Statement statement() const;
      Database database() const;


    private:
      // constructors

      friend class SharedStatement;
      friend class Statement;

      Row();
      Row(const Statement& stmt, int index, detail::Flag flag);


      // helpers

      Value fetch(int i) const;
      void fail(int i) const;


      // data

      Statement stmt_;
      detail::Watcher watcher_;
      int index_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/row.hxx>



#endif /* !SAW_ROW_HH_ */
