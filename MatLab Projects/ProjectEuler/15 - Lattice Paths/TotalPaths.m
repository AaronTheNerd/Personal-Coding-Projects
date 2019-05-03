function lattice_paths = TotalPaths(size)
% This function finds the total amount of possible paths for a size x size
% grid where you can only move right and down. Due to this we need to move
% right size times and down size times. The different paths are obtained by
% different orderings of these moves. This could be calculated through
% multiset permutation where the total set is 2 * size and each choice
% needs a multiplicity of size.

lattice_paths = factorial(2*size)/(factorial(size)^2);
end

