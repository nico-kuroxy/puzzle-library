# Person Handling

The class implementing some functions to process lists of Persons.

The **findFirstPerson()** function consists in finding the name of the person in the population which comes first in alphabetical order.

The **findMeanDevAge()** function aims at computing the mean and standard deviation of the age distribution within the population given as input.

Finally, the **findMedian()** function looks for the median age in the population as well as the name of the associated person.

## How to test

As explained in the [Readme](../../README.md/#how-to-test) of the project, just use `ctest --test-dir build` to run all the GTest test case defined for this project.

## Solution

The **findFirstPerson()** function has a spatial complexity of **O(1)** and a temporal complexity of **O(n*p)**. n is the number of people in the list passed as argument of the function, while p is the average minimum length between two persons' name... We could argue that p is negligible before n when the population is very large, since someone's name is limited.

The **findMeanDevAge()** function has a spatial complexity of **O(1)** and a temporal complexity of **O(n)**. n is the number of people in the list passed as argument of the function.

Finally, the **findMedian()** function has a spatial complexity of **O(1)** and a temporal complexity of **O(n)**. n is, once again, the number of people in the list passed as argument. It should be noted that the **nth_element()** function used in this case has a spatial complexity of **O(n)** on average case.
