//SFDateTime.hpp


#ifndef SFTimezone_hpp
#define SFTimezone_hpp
#include <string>





class SFTimezone {
  SFTimezone(const char* aTimezoneAbbrev); //GMT, EST, CST, PST
  SFTimezone(const SFTimezone &aTimezone);
  
  operator const char*(); // Returns the 3 letter abbreviation of the timezone object
  
  ...other members as needed...
};


#endif /* SFTimezone_hpp */
