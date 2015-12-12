tiles = ((22, '-', 9, '*'),
        ('+', 4, '-', 18),
        (4, '*', 11, '*'),
        ('*', 8 , '-', 1))

SIZE = 4
MAX_INT = 32768

directions = ('N', 'E', 'S', 'W')

directionMapper = {'N': (1,0), 'S': (-1,0), 'E': (0,1), 'W': (0,-1)}
operationMapper = {'+': (lambda x, y: (x+y) % MAX_INT ), '-': (lambda x, y: (x-y) % MAX_INT ), '*': (lambda x, y: (x*y) % MAX_INT )}

target = 30

def isValidPos(pos):
    return pos[0] >= 0 and pos[0] < SIZE and pos[1] >= 0 and pos[1] < SIZE


#return (minsteps, path)
def findShortest(pos, value, operation, steps, path, maxSteps):
    if steps >= maxSteps:
        return (-1, '')

    if(not isValidPos(pos)):
        return (-1, '')

    if(pos == (0,0) and steps > 0):
        return (-1, '')

    if isinstance(tiles[pos[0]][pos[1]], int):
        value = operationMapper[operation](value, tiles[pos[0]][pos[1]])
        
    else:
        operation = tiles[pos[0]][pos[1]]

    if pos == (3,3):
        #print 'reached vault:', value, path, steps
        if value == target:
            print 'path found:', steps, path
            return (steps, path)
        else:
            return (-1, '')

    found = False
    minresult = (maxSteps, '')
    for d in directions:
        p = tuple([pos[i] + directionMapper[d][i] for i in xrange(2)])
        r = findShortest(p, value, operation, steps+1, path + d, minresult[0])
        if r[0] >= 0 and r[0] <= minresult[0]:
            minresult = r
            found = True
    
    if found:
        return minresult
    else:
        return (-1, '')

for i in xrange(30):
    print findShortest((0,0), 0, '+', 0, '', i)
