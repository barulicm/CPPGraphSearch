%GraphSearch                         {#mainpage}
============

The %GraphSearch library provides implementations of common graph search 
algorithms. You can use it to solve just about any problem that can be framed
as a graph search problem.

## Implemented Algorithms

The following algorithms are currently implemented in this library.

* [ A* (AStar) ](@ref GraphSearch::AStar)
* [ Breadth-First Search (BFS) ](@ref GraphSearch::BFS)
* [ Depth-First Search (DFS) ](@ref GraphSearch::DFS)

## How to Use 

The first step to defining a search problem for this library is choosing types
to represent states and actions in your search domain. You can use any types you want to, but it is recommended 
that you use types which follow 
[value semantics](https://akrzemi1.wordpress.com/2012/02/03/value-semantics/).
Once you've selected these two types, you can give them to the search algorithm 
via template parameters.

For example, if you're trying to find a path through a 2-dimensional grid you 
might define a Location type to track <x,y> pairs and a Move type to represent 
taking a step in some direction on the grid. You can then pass these types to
any algorithm in the library:

```cpp
auto path = GraphSearch::BFS<Location, Move>(...);
```

Next, you'll need to provide a set of values and functions to define the 
specifics of the search problem. Each search algorithm will require a different 
set of parameters, but they tend to follow some patterns.

Some parts of a search problem can be described with a simple value. For 
example, you can tell the algorithm where to start the search from by providing
an instance of your StateType with the right values. 

```cpp
auto startLocation = Location(0,0);
```

Other parts of a search problem are better described with a function mapping
some information to other information. For example, you might think we could 
represent the goal state of our search problem with another value, but some 
problems have multiple valid goal states. Instead, the goal conditions are 
defined with a function which evaluates whether a given state meets whatever the
goal conditions are. You might have a 2D search problem where any position with
a Y value greater than 10 is in the goal area:

```cpp
auto isGoal = [](const Location &loc) { return loc.y > 10; };
``` 

You can use any callable entity for these parameters, including member  
functions, free functions, callable objects, or lambdas.

For a complete example of a 2D search through a grid map, check out the 
11x11grid example in the examples directory.
