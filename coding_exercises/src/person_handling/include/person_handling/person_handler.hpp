/**
 * @file person_handler.hpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the header of the PersonHandler class used to process lists of Persons.
 * @copyright © 2025 Nicolas Erbetti
 */

#ifndef _PERSON_HANDLER_PERSON_HANDLER_HPP_
#define _PERSON_HANDLER_PERSON_HANDLER_HPP_
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
//> Custom-made libraries
#include <person_handling/person.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> CLASS DECLARATION
class PersonHandler {
/**
 * @struct PersonHandler
 * @brief Processes the Advent of Code Day 1 problem, handling input data and computing required metrics.
 *
 */

public:
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///> CONSTRUCTORS
   /**
   * @brief Constructs a PersonHandler object.
   */
   explicit PersonHandler();
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///> DESTRUCTORS
   /**
   * @brief Destructor for the PersonHandler class, cleans up any resources allocated by Person.
   */
   virtual ~PersonHandler() = 0;
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///> FUNCTIONS
   /**
    * @brief Finds the name of the first person in the list in alphabetical order.
    *
    * @param _list_persons Reference to a vector of Person objects to search through.
    * @param _first_person_name Reference to a string where the name of the person found will be stored.
    * @return int -1 if there was an error, 0 otherwise.
    */
   static int findFirstPerson(std::vector<Person>& _list_persons, std::string& _first_person_name);
   /**
    * @brief Calculates the mean and standard deviation of ages from a list of Person objects.
    *
    * @param _list_persons Reference to a vector containing Person objects whose ages will be analyzed.
    * @param _mean Reference to a float where the computed mean age will be stored.
    * @param _dev Reference to a float where the computed standard deviation of ages will be stored.
    * @return int -1 if there was an error, 0 otherwise.
    */
   static int findMeanDevAge(std::vector<Person>& _list_persons, float& _mean, float& _dev);
   /**
    * @brief Finds the median age from a list of Person objects, as well as the name of the associated Person.
    *
    * @param _list_persons Reference to a vector containing Person objects.
    * @param _median Reference to an integer where the median value will be stored.
    * @param _name Reference to a string where the name of the median Person will be stored.
    * @return int -1 if there was an error, 0 otherwise.
    */
   static int findMedian(std::vector<Person>& _list_persons, int& _median, std::string& _name);
   /**
    * @brief Compares two Person objects for sorting or ordering purposes.
    *
    * @param _a Reference to the first Person object to compare.
    * @param _b Reference to the second Person object to compare.
    * @return bool Returns True _a is less than _b, False otherwise.
    */
   static bool comparator(const Person& _a, const Person& _b);
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _PERSON_HANDLER_PERSON_HANDLER_HPP_
