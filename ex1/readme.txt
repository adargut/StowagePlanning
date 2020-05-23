Different stowage models for container ships, implemented in C++, by Adar Gutman 316265065 and Nir Goren 313452781.

Running instructions: type in the path to the where Plan, Route, and all of the <cargo_name>.cargo_data files.
Note that every file must be formatted such that space seperate the strings.

Run as many simulations as you wish, then type in quit in order to terminate the program, then you will see simulation_errors.csv, 
simulation_results.csv where errors and number of operations are stored, and also <port_name>.csv for every port in route where 
the individual operations for the port are stored.

The algorithm works in the following way: for every container that needs to be unloaded at the port, first we unload all the containers above it, 
then we unload it to the port, then load again all those containers where they were, with one floor below.
