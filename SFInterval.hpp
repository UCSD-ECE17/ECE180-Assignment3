//SFInterval.hpp


#ifndef SFInterval_hpp
#define SFInterval_hpp
#include <string>


class SFInterval {
  int years;
  int months;
  int days;
  int hours;
  int minutes;
  int seconds;  
  
  operator const char*(); // Returns the interval of the form "Y years, M months, D days, H hours, M minutes and S seconds"
                          // Ex. 5 years, 3 months, 2 days, 6 hours, 7 minutes and 10 seconds
};



#endif /* SFInterval_hpp */
