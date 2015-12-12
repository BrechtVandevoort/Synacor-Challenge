#Solution for the value of register 8
import resource,sys,itertools
resource.setrlimit(resource.RLIMIT_STACK, (resource.RLIM_INFINITY, resource.RLIM_INFINITY))
sys.setrecursionlimit(10**8)

MAX_INT = 32768

d = {}
register = 1
m1 = 4
n1 = 1

def ackermann(m,n):
    global d, register
    if (m,n) in d:
        return d[(m,n)]
    
    #print "calculating ", m, n

    if m == 0:
        value = n+1
    elif n == 0:
        value = ackermann(m-1, register)
    else:
        value = ackermann(m-1, ackermann(m, n-1))

    value = value % MAX_INT
    d[(m,n)] = value
    return value

result = -1
for register in itertools.count():
    d = {}
    v = ackermann(m1,n1)
    if v == 6:
        result = register
    print register, ':', v, '\t\t', result
