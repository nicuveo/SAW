//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_STATEMENT_HXX_
# define SAW_STATEMENT_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/statement.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // accessors

  inline bool
  Statement::busy() const
  {
    return empty() ? true : sqlite3_stmt_busy(raw_data()) != 0;
  }

  inline bool
  Statement::ready() const
  {
    return empty() ? false : sqlite3_stmt_busy(raw_data()) == 0;
  }

  inline bool
  Statement::empty() const
  {
    return not bool(*this);
  }


  inline Database
  Statement::database() const
  {
    return db_;
  }



  // parameter binding

  inline Statement::Proxy
  Statement::operator[](const ParameterKey& key)
  {
    typedef Statement& (Statement::* Fun)(const ParameterKey&, const Value&);
    return Proxy(std::bind(static_cast<Fun>(&Statement::bind), this, key, std::placeholders::_1));
  }

  inline Statement::Proxy
  Statement::operator[](const ParameterName& name)
  {
    typedef Statement& (Statement::* Fun)(const ParameterName&, const Value&);
    return Proxy(std::bind(static_cast<Fun>(&Statement::bind), this, name, std::placeholders::_1));
  }

  inline Statement::Proxy
  Statement::operator[](const ParameterIndex& index)
  {
    typedef Statement& (Statement::* Fun)(const ParameterIndex&, const Value&);
    return Proxy(std::bind(static_cast<Fun>(&Statement::bind), this, index, std::placeholders::_1));
  }


  inline Statement&
  operator<<(Statement& stmt, const Parameter& p)
  {
    return stmt.bind(p);
  }

  inline Statement&
  operator<<(Statement& stmt, const Parameters& p)
  {
    return stmt.bind(p);
  }


  inline Statement&
  Statement::bind(const Parameter& p)
  {
    return bind(p.first, p.second);
  }



  // execution

  inline void
  Statement::exec(const RowCallback& rcb, const Parameters& ps)
  {
    return bind(ps).exec(rcb);
  }


}



#endif /* !SAW_STATEMENT_HXX_ */
