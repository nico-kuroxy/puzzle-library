# Library

This is the library containing pieces of code reused for each challenge of the advent challenge.

For now, it only has the abstract BaseAdventDay class used to store the name of the file with the input data.

## How to use

Whenever a new class is created for one of the day, we have it inherit from BaseAdventDay and pass to its constructor the name of the file we need to load. Also, this new class need to define a `int run()` function to override the one declared as purely virtual in the base class.
