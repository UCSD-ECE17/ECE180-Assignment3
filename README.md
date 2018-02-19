# ECE-180 Assignment #3
Due: Feb 26, 11:15p (PST)

## Preface

We can all remember the simpler days (last week) when homework assignments involved building one simple class. That was fun, right?  Sadly, very few real-world software problems can be implemented so easily. Therefore, this assignment involves multiples classes that have to work together to accomplish the given task. 

## JobCo Plans to Go PUBLIC!

IPO! WOOT WOOT!  It's very exciting when your cool little startup grows up, and is ready to go public. Sure, lots of early employees stand to make a lot of money on their stock grants. But it's not all fun and games you know. The process of "going public" takes a tremendous amount of work, making sure that all of your internal processes are up to the standards necessary to meet public scrutiny. As it turns out, JobCo has more than a few problems, and you've been placed on the "going public" software team. Good luck!

### Calendrical Computations

"Ok everyone, settle down", Chloe says, smiling softly. "As you've all heard, JobCo is going public...", she begins, then stops abruptly as the room explodes into cheers and shouting. Waiting for nearly a minute, she finally continues, "Ok, ok, before you all rush out and buy yourself a Tesla, we have some work to do." 

"For starters", says Chloe, "we have to get all our internal records into order". She continues, "That means we have to clean up all the information in the databases. As you know, we have had operations in California and in Paris. And they each tracked time using their local time, rather than a standard universal time like GMT."  She shrugs. "So", she continues, "it's up to us to fix all that."

Chloe divides the teams up into smaller groups. You get assigned to the team who has to build some time-related classes that the project can use to fix the all the times. You're going to have to be able to deal with times, dates, timezones and intervals. Most importantly, you'll have to be able to convert dates from London, New York and other locations to California time (PST), and back again. 

"Oh", said Chloe, one more thing."  You wince waiting for more bad news.  "We're on a VERY short timeline here."

## Assignment Details

In this assignment, you are going to build a series of classes that support calendrical computations. Dates, times, timezones, and intervals. Your solution will be used to do things like creating timers in application code, or handling timezone conversions. All of your classes will be declared within a namespace called "SoftwareFoundations".

At a minimum, you will implement five classes:

```
class SFDate;
class SFTime;
class SFDateTime;
class SFTimezone;
class SFInterval;
```

Note that you are free to create any other classes you need in order to support your solution. Presumably, if you add other classes it is to provide functionality to your solution that you have deemed "worthy" to be part of your solution. Totally up to you. Our testing framework will only interact with the five classes we have outlined above.

### About Your Classes

You are free to implement your `Date` class any way you see fit. It must, however, fulfill certain requirements:

#### The SFDate Class 

- You must be able to construct a `SFDate` class without any arguments, in which case it refers to the current date
- You must be able to construct a `SFDate` class using 3 integers (int month, int day, int year)
- You must be able to construct a `SFDate` class using a well-formed string ("Jan 4, 1961") or ("January 4, 1961")
- You must be able to copy construct a `SFDate` from another `SFDate` class, or convert/construct from a `SFDateTime` class
- You must provide a conversion operator from your `SFDate` class to a const char*. 

Your `Date` class must also support basic operations to change the date incrementally, relational operations, as well as methods to get/set various properties of the date. Here's a summary of your interface:

```

class SFDate {
  SFDate();                             //default to today
  SFDate(const char *aDateTimeString);  //must parse the given string of the form MM/DD/YYYY
  SFDate(int month, int day, int year); //build date from individual parts
  SFDate(const SFDate &aCopy);  
  SFDate(const SFDateTime &aCopy);

  operator ++(); //advance by one day
  operator --(); //back up by one day...

  SFInterval operator-(const SFDate &other) const; //determine interval between two dates...
  SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...

  SFDate& adjustByDays(int n) -- to add or subtract N days from the given date
  SFDate& adjustByWeeks(int n) -- to add or subtract N weeks from the given date
  SFDate& adjustByMonths(int n) -- to add or subtract N months from the given date
  SFDate& adjustByYears(int n) -- to add or subtract N years from the given date
  
  SFDate& setDay(int aDay)      //set the current day of the given date object; aDay must be in valid range
  SFDate& setMonth(int aMonth)  //set the current month of the given date object aMonth must be in valid range
  SFDate& setYear(int aYear)    //set the current year; must be in valid range
  
  int   getDay()    //if date is 12/15/2018, the day is the 15th
  int   getMonth()  //if date is 12/15/2018, the month is 12 (dec)
  int   getYear()   //if date is 12/15/2018, the year is 2018
  
  int   getWeekOfYear() //if date is 01/10/2018, the week of year is 2 (range is 1..52)
  int   getDayOfYear()  //if date is 01/04/1961, the day of year is 4 (range is 1..365)
  int   getDayOfweek()  //range (0..6 -- 0==sunday) 
  int   daysInMonth()   //based on month/year, return # of days in the month 
  
  SFDate& startOfMonth(); //if date is 12/15/2018, return 12/01/2018 
  SFDate& endOfMonth();   //if date is 12/15/2018, return 12/31/2018

  SFDate& startOfYear();  //if date is 12/15/2018, return 01/01/2018 
  SFDate& endOfYear();    //if date is 12/15/2018, return 12/31/2018

  std::string toDateString();  //Return a string of the form MM/DD/YYYY

    //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==

  ... other members here as necessary...

}
```

#### The SFTime Class 

This class is much simpler, as shown below:

```
class SFTime {
  SFTime();                             //default to now(HH:MM:SS) 
  SFTime(const char *aTimeString);      //must parse the given string of the form "HH:MM:SS"
  SFTime(int anHour, int aMinutes, int aSeconds); //build time from individual parts
  SFTime(const SFTime &aCopy);  
  SFTime(const SFDateTime &aCopy);

  SFTime& adjustByMinutes(int n) -- to +/- N minutes from the given time
  SFTime& adjustByHours(int n) -- to +/- N hours from the given time. 11:15pm + 2hours is 1:15a (rolls over)

  SFInterval operator-(const SFTime &other) const; //determine interval between two times...
  SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...

  int   getHour()
  int   getMinutes()
  int   getSeconds()  

  SFTime& startOfDay(); change time to (00:00:00)
  SFTime& endOfDay();   change time to (23:59:59)
  
  std::string toTimeString();  //Returns string of the form HH:MM:SS

    //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==

  ... more members here as necessary...

}
```

#### The SFDateTime Class 

You are free to implement your `SFDateTime` class any way you see fit. In general, the `SFDateTime` class combines features of the `SFDate` class with features of the `SFTime` class. In addition, the `DateTime` class must also support timezones and relational operators.  Anything you can do with date or time classes, you can do here too.

```
class SFDateTime {

  SFDateTime(Timezone *aTimezone=nullptr); //init a new datetime based on GMT, unless a valid timezone is provided
  SFDateTime(const SFDateTime &aCopy); //copy construct
  SFDateTime(int aMonth, int aDay, int aYear, int anHour=0, int aMinutes=0, int aSeconds=0, Timezone *aTimezone=nullptr); 
  SFDateTime(const char* aString, SFTimezone *aTimezone=nullptr); //parse the given string of the form "MM/DD/YYYY HH:MM:SS"
  SFDateTime(const SFDate &aDate, const SFTime &aTime, SFTimezone *aTimezone=nullptr); 
             
  SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...
             
  SFTimezone&  getTimezone(); //retrieve timezone currently associated with this object
  SFDateTime&  setTimezone(SFTimezone &aTimezone); //change timezone

    //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==

  operator const char*();   //Returns string of the form "MON DATE, YEAR HH:MM:SS TIMEZONE" Ex. Jan 4, 1961 09:15:00 PST
  operator SFDate(); 
  operator SFTime();
  operator SFTimezone();             
             
  std::string toDateTimeString();   //Jan 4, 1961 09:15:00 PST (always this format)
             
  ... more members here as necessary...

}
```

#### The SFTimezone Class 

Timezones can be tricky, so we're keeping the requirements to a minimum. The baseline timezone for your solution is "GMT" -- which refers to Greenwich Mean Time, clock time at the Royal Observatory in Greenwich, London. It is the same all year round and is not affected by Summer Time or Daylight Saving Time. It isn't a requirement, but you might consider making singletons for each timezone.

Although there a more than 20 _actual_ timezones, we will only ever ask you to support four, using an abbreviation:

1. GMT (GMT as described above)
2. EST (US Eastern standard time)
3. CST (US Central standard time)
4. PST (US Pacific standard time)

Your timezone class must support default construction, copy construction, and construction from one of the four abbreviations listed above. We will also ask your Timezone class to provide a const char* conversion operator in case a caller wants to be able to print out the string value of the current timezone.

```
class SFTimezone {
  SFTimezone(const char* aTimezoneAbbrev); //GMT, EST, CST, PST
  SFTimezone(const SFTimezone &aTimezone);
  
  operator const char*(); // Returns the 3 letter abbreviation of the timezone object
  
  ...other members as needed...
};
```

#### The SFInterval Class 

Date intervals are used to determine the calendrical distance between two calendrical classes. SFTime, SFDate and SFDateTime all offer a conversion operator that returns an SFInterval. For `SFTime` classes, only time relevant properties are set (h,min,sec). For `SFDate` class, only date-relevant properties are set (m,d,y). For `SFDateTime` instances, date and time properties are all set. 

```
class SFInterval {
  int years;
  int months;
  int days;
  int hours;
  int minutes;
  int seconds;  
  
  operator const char*(); // Returns the interval of the form "Y years, M months, D days, H hours, M minutes and S seconds"
                          // Ex. 5 years, 3 months, 2 days, 6 hours, 7 minutes and 10 seconds
}
```

### The Testing Interface

In our last assignment, we provided you with a specific class interface. In this assignment, the interface is up to you. Instead, we are providing you with a "boilerplate" test-harness that you'll use to test your implementation. You MUST make sure that your test harness tests EVERY method on EACH of your major classes `SFDate`, `SFTime`, `SFDateTime`, `SFTimezone`, and `SFInterval`. Some of the tests you write will require that more that one type of object is used in the test, like getting the interval between a SFDate and an SFDateTime, or setting a SFDateTime timezone by passing a SFTimezone object.

The testing harness looks like this, and writing the actual test code is left as an exercise for the reader.  Vlad-the-compiler will use his _own_ test harness.

```
class SFTestHarness {
public:
  static int runDateTests() {
    //test all your constructors; can you make one from a time string?
    //test all your date methods...
  }
  
  static int runTimeTests() {
    //test all your constructors
    //test all your time methods...
  }

static int runDateTimeTests() {
    //test all your constructors; can you make one from a date-time string "02/15/2018 09:15:25"?
    //test all your datetime methods...
  }
  
  static int runIntervalTests() {
    //compute interval between dates, dates and datetimes, times, etc...
  }
 
  static int runTimezoneTests() {
    //make a datetime in timezoneA, convert to timezoneB, then convert back to timezoneA. Did it convert correctly?
    //other tests as necessary
  }
  
  static int runAllTests() {
    runDateTests();
    runTimeTests();
    runDateTimeTests();
    runIntervaltests();
    runTimezoneTests();
  }
};
```


## Code Style Guide

This isn’t your first class on software or programming, and you’re probably wondering how we expect your code to be structured and formatted.  From the perspective of our auto-grader, structure and format are completely irrelevant. However, your instructors also will be viewing your code as well, so you would be wise to adhere to a few rules of thumb. 

### Format and Clarity

Your code should be formatted to be easily readable by anyone with more than 1 year of programming experience.  Here are some guidelines for things that matter:

- Avoid dense and complicated code
- Be consistent!  Choose a coding standard for yourself and stick with it
- Partition your logic into class methods as needed to maintain clarity
- Document your code with comments that clearly indicate what you’re doing at a high level

Unsure if you’ve got it right?  Take a look at sample code in your textbook. Look at C++ code examples from github. Ask a friend to take a look. Most of all, use your judgement to estimate whether others can make sense of what you’re doing.  We’re being intentionally vague, so you get to learn what works and what doesn’t. 

## Submitting Your Work

You’ll recall that your work is due by 11:15pm (PST).  We strongly recommend that you aim for 6p (PST) as to avoid the last minute mishaps that frequently occur when panic related to an impending deliverable begins, and we all tend to make silly mistakes.  

As usual, you'll turn your work in via Github. Make sure to turn in all the required classes, the testing harness, and properly update your personal information the student.json file as we have done in previous assignments.

## Caveats and Warnings

When you work on your assignments, many of you will create an IDE-based project. IDE’s will likely speed up your process, and give you additional tools, like an integrated debugger. 

It is important to note that Vlad-the-Compiler doesn’t use IDE projects. He uses makefiles to test and grade your homework.  Each of your assignments will include a makefile for this purpose. We strongly recommend that before you turn in your assignments, you attempt to build and run your code using this makefile.  

The files we provide for you by default in your assignment project folders will compile with the given makefile. They just won’t do much, until you add your own code to the solution. In general, you can feel free to change the files we provide you, and to add new files as necessary to solve the assigned problems. Note, however, that some of the files we provide for you have portions that are marked "DO NOT CHANGE".  We ask that you follow that advice carefully.

NOTE: It is **YOUR RESPONSIBILITY** to ensure your solution can be built correctly by the **make** command.

