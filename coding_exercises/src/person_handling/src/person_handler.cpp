/**
 * @file person_handler.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the source of the PersonHandler class used to process lists of Persons.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> Custom-made libraries
#include <person_handling/person_handler.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int PersonHandler::findFirstPerson(std::vector<Person>& _list_persons, std::string& _first_person_name) {
    // Safeguard : check if the input vector is not empty.
    if (_list_persons.size() == 0) {
        // Log the error.
        std::cerr << "The provided list of person is empty ! Please provide at least one person." << std::endl;
        // Return an error code.
        return -1;
    }
    // Initialize the first person name.
    _first_person_name = _list_persons[0].name_;
    // Iterate through each person.
    for (int i = 1; i < _list_persons.size(); i++) {
        // Update the first person name if it comes before in alphabetical order.
        if (_list_persons[i].name_ < _first_person_name) _first_person_name = _list_persons[i].name_;
    }
    // Return 0 if no error was detected.
    return 0;
}
int PersonHandler::findMeanDevAge(std::vector<Person>& _list_persons, float& _mean, float& _dev) {
    // Safeguard : check if the input vector is not empty.
    if (_list_persons.size() == 0) {
        // Log the error.
        std::cerr << "The provided list of person is empty ! Please provide at least one person." << std::endl;
        // Return an error code.
        return -1;
    }
    // Initialize the function variables.
    _mean = 0;
    _dev = 0;
    // Iterate through each person to compute the mean.
    for (const auto person : _list_persons) {
        // Update the mean.
        _mean += (static_cast<float>(person.age_) / _list_persons.size());
    }
    // Iterate through each person to compute the standard deviation.
    for (const auto person : _list_persons) {
        // Update the standard deviation.
        _dev += (pow(static_cast<float>(person.age_) - _mean, 2) / _list_persons.size());
    }
    _dev = sqrt(_dev);
    // Return 0 if no error was detected.
    return 0;
}
int PersonHandler::findMedian(std::vector<Person>& _list_persons, int& _median, std::string& _name) {
    // Safeguard : check if the input vector is not an even number.
    if (_list_persons.size() % 2 == 0) {
        // Log the error.
        std::cerr << "The provided list should have an odd number of people ! Please provide a proper list." << std::endl;
        // Return an error code.
        return -1;
    }
    // Rearrange so that nums[mid] is the element that would be there if sorted
    nth_element(_list_persons.begin(), _list_persons.begin() + _list_persons.size() / 2, _list_persons.end(), PersonHandler::comparator);
    // Find the median age.
    _median = _list_persons[_list_persons.size() / 2].age_;
    // Iterate through each person.
    for (const auto person : _list_persons) {
        // Update the name of the person having the median age.
        if (person.age_ == _median) _name = person.name_;
    }
    // Return 0 if no error was detected.
    return 0;
}
bool PersonHandler::comparator(const Person& _a, const Person& _b) {
    // Return true if the first person is younger than the second.
    return _a.age_ < _b.age_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////