#Code for finding the solution for the equation _ + _ * _^2 + _^3 - _ = 399
import itertools
values = (2,3,5,7,9)
print [p for p in itertools.permutations(values) if p[0] + p[1] * p[2] * p[2] + p[3] * p[3] * p[3] - p[4] == 399]
