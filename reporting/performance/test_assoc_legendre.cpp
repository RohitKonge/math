//  Copyright John Maddock 2015.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER
#  pragma warning (disable : 4224)
#endif

#include <boost/math/special_functions/legendre.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include "../../test/table_type.hpp"
#include "table_helper.hpp"
#include "performance.hpp"
#include <iostream>

typedef double T;
#define SC_(x) static_cast<double>(x)

int main()
{
#  include "assoc_legendre_p.ipp"

   add_data(assoc_legendre_p);

   unsigned data_total = data.size();

   screen_data([](const std::vector<double>& v){  return boost::math::legendre_p(v[0], v[1], v[2]);  }, [](const std::vector<double>& v){ return v[3];  });


#if defined(TEST_LIBSTDCXX) && !defined(COMPILER_COMPARISON_TABLES)
   screen_data([](const std::vector<double>& v){  return std::tr1::assoc_legendre(v[0], v[1], v[2]);  }, [](const std::vector<double>& v){ return v[3];  });
#endif

   unsigned data_used = data.size();
   std::string function = "assoc_legendre[br](" + boost::lexical_cast<std::string>(data_used) + "/" + boost::lexical_cast<std::string>(data_total) + " tests selected)";

   double time;

   time = exec_timed_test([](const std::vector<double>& v){  return boost::math::legendre_p(v[0], v[1], v[2]);  });
   std::cout << time << std::endl;
   report_execution_time(time, std::string("Library Comparison with ") + std::string(BOOST_COMPILER) + std::string(" on ") + BOOST_PLATFORM, function, "Boost");
   //
   // Boost again, but with promotion to long double turned off:
   //
#if !defined(COMPILER_COMPARISON_TABLES)
   if(sizeof(long double) != sizeof(double))
   {
      time = exec_timed_test([](const std::vector<double>& v){  return boost::math::legendre_p(v[0], v[1], v[2], boost::math::policies::make_policy(boost::math::policies::promote_double<false>()));  });
      std::cout << time << std::endl;
      report_execution_time(time, std::string("Library Comparison with ") + std::string(BOOST_COMPILER) + std::string(" on ") + BOOST_PLATFORM, function, "Boost[br](no internal promotion to long double)");
   }
#endif


#if defined(TEST_LIBSTDCXX) && !defined(COMPILER_COMPARISON_TABLES)
   time = exec_timed_test([](const std::vector<double>& v){  return std::tr1::assoc_legendre(v[0], v[1], v[2]);  });
   std::cout << time << std::endl;
   report_execution_time(time, std::string("Library Comparison with ") + std::string(BOOST_COMPILER) + std::string(" on ") + BOOST_PLATFORM, function, "tr1/cmath");
#endif


   return 0;
}

