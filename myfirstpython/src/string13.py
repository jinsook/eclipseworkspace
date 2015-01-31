'''
Created on Nov 1, 2009

@author: jin
'''
theline = "choi jin sook"
afield = theline[5:8]
print afield #jin

theline = "choiixxxjinsookseatcssss"
import struct
# Get a 5-byte string, skip 3, get two 8-byte strings, then all the rest:
baseformat = "5s 3x 8s 8s"
# by how many bytes does theline exceed the length implied by this
# base-format (24 bytes in this case, but struct.calcsize is general)
numremain = len(theline) - struct.calcsize(baseformat)
# complete the format with the appropriate 's' field, then unpack
format = "%s %ds" % (baseformat, numremain)
l, s1, s2, t = struct.unpack(format, theline)

print l, s1, s2, t #choii jinsooks eatcssss

l, s1, s2 = struct.unpack(baseformat, theline[:struct.calcsize(baseformat)])
print l, s1, s2,

#If you need to split at five-byte boundaries, you can easily code a list comprehension (LC) of slices:
fivers = [theline[k:k+5] for k in xrange(0, len(theline), 5)]

#Chopping a string into individual characters is of course easier: 
chars = list(theline)



#If you prefer to think of your data as being cut up at specific columns, slicing with LCs is generally handier:

cuts = [8, 14, 20, 26, 30]
pieces = [ theline[i:j] for i, j in zip([0]+cuts, cuts+[None]) ]


def fields(baseformat, theline, lastfield=False):
    # by how many bytes does theline exceed the length implied by
    # base-format (struct.calcsize computes exactly that length)
    numremain = len(theline)-struct.calcsize(baseformat)
    # complete the format with the appropriate 's' or 'x' field, then unpack
    format = "%s %d%s" % (baseformat, numremain, lastfield and "s" or "x")
    return struct.unpack(format, theline)

print fields(baseformat, theline)#choii jinsooks eatcssss ('choii', 'jinsooks', 'eatcssss')

def fields2(baseformat, theline, lastfield=False, _cache={  }):
    # build the key and try getting the cached format string
    key = baseformat, len(theline), lastfield
    format = _cache.get(key)
    if format is None:
        # no format string was cached, build and cache it
        numremain = len(theline)-struct.calcsize(baseformat)
        _cache[key] = format = "%s %d%s" % (
            baseformat, numremain, lastfield and "s" or "x")
    return struct.unpack(format, theline)

print fields(baseformat, theline)#('choii', 'jinsooks', 'eatcssss')

def split_by(theline, n, lastfield=False):
    # cut up all the needed pieces
    pieces = [theline[k:k+n] for k in xrange(0, len(theline), n)]
    # drop the last piece if too short and not required
    if not lastfield and len(pieces[-1]) < n:
        pieces.pop( )
    return pieces

print split_by(theline, 5) #['choii', 'xxxji', 'nsook', 'seatc']

def split_at(theline, cuts, lastfield=False):
    # cut up all the needed pieces
    pieces = [ theline[i:j] for i, j in zip([0]+cuts, cuts+[None]) ]
    # drop the last piece if not required
    if not lastfield:
        pieces.pop( )
    return pieces

print split_at(theline, [3,5, 7, 9]) #['cho', 'ii', 'xx', 'xj']

def split_at2(the_line, cuts, lastfield=False):
    last = 0
    for cut in cuts:
        yield the_line[last:cut]
        last = cut
    if lastfield:
        yield the_line[last:]
        


def split_by2(the_line, n, lastfield=False):
    return split_at(the_line, xrange(n, len(the_line), n), lastfield)

list_of_fields = list(split_by(theline, 5))
print list_of_fields #['choii', 'xxxji', 'nsook', 'seatc']
