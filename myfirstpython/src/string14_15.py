'''
Created on Nov 1, 2009

@author: jin
'''

def reindent(s, numSpaces):
    leading_space = numSpaces * ' '
    lines = [ leading_space + line.strip( )
              for line in s.splitlines( ) ]
    return '\n'.join(lines)

str = """    hello
      this is some line
         and another line
"""
 
print str
print reindent(str, 4)

def addSpaces(s, numAdd):
    white = " "*numAdd
    return white + white.join(s.splitlines(True))
def numSpaces(s):
    return [len(line)-len(line.lstrip( )) for line in s.splitlines( )]
def delSpaces(s, numDel):
    if numDel > min(numSpaces(s)):
        raise ValueError, "removing more spaces than there are!"
    return '\n'.join([ line[numDel:] for line in s.splitlines( ) ])

def unIndentBlock(s):
    return delSpaces(s, min(numSpaces(s)))

print unIndentBlock(str)

#Recipe 1.15. Expanding and Compressing Tabs
str = """\thello
\t\tthis is some line
\t\t\tand another line
"""
print str

def unexpand(astring, tablen=8):
    import re
    # split into alternating space and non-space sequences
    pieces = re.split(r'( +)', astring.expandtabs(tablen))
    # keep track of the total length of the string so far
    lensofar = 0
    for i, piece in enumerate(pieces):
        thislen = len(piece)
        lensofar += thislen
        if piece.isspace( ):
            # change each space sequences into tabs+spaces
            numblanks = lensofar % tablen
            numtabs = (thislen-numblanks+tablen-1)/tablen
            pieces[i] = '\t'*numtabs + ' '*numblanks
    return ''.join(pieces)

print ''.join([ unexpand(s) for s in str.splitlines(True) ])

def expand_at_linestart(P, tablen=8):
    import re
    def exp(mo):
        return mo.group( ).expandtabs(tablen)
    return ''.join([ re.sub(r'^\s+', exp, s) for s in P.splitlines(True) ])

print expand_at_linestart(str)
