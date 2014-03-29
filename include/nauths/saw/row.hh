//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_ROW_HH_
# define SAW_ROW_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <map>
# include <vector>
# include <nauths/saw/detail/cache.hh>
# include <nauths/saw/detail/flag.hh>
# include <nauths/saw/statement.hh>
# include <nauths/saw/database.hh>
# include <nauths/saw/value.hh>
# include <nauths/saw/types.hh>



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

# include <nauths/saw/row.hxx>



#endif /* !SAW_ROW_HH_ */
