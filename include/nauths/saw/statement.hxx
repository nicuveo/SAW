//
// Copyright Antoine Leblanc 2010 - 2013
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
    return Proxy(boost::bind(static_cast<Statement& (Statement::*)(const ParameterKey&, const Value&)>(&Statement::bind), this, key, _1));
  }

  inline Statement::Proxy
  Statement::operator[](const ParameterName& name)
  {
    return Proxy(boost::bind(static_cast<Statement& (Statement::*)(const ParameterName&, const Value&)>(&Statement::bind), this, name, _1));
  }

  inline Statement::Proxy
  Statement::operator[](const ParameterIndex& index)
  {
    return Proxy(boost::bind(static_cast<Statement& (Statement::*)(const ParameterIndex&, const Value&)>(&Statement::bind), this, index, _1));
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
