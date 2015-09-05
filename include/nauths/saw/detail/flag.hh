//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_FLAG_HH_
# define SAW_FLAG_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <memory>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  namespace detail
  {

    class Flag : private std::shared_ptr<int>
    {
      public:
        friend class Watcher;

        bool raised() const;

        void raise();
        void lower();
    };

    class Watcher : private std::weak_ptr<int>
    {
      public:
        Watcher();
        Watcher(Flag f);

        bool valid() const;
        bool obsolete() const;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/detail/flag.hxx>



#endif /* !SAW_FLAG_HH_ */
