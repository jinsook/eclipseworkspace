'''
Created on Nov 1, 2009

@author: jin
'''
from __future__ import division           # ensure / does NOT truncate
import string
text_characters = "".join(map(chr, range(32, 127))) + "\n\r\t\b"
_null_trans = string.maketrans("", "")
def istext(s, text_characters=text_characters, threshold=0.30):
    # if s contains any null, it's not text:
    if "\0" in s:
        return False
    # an "empty" string is "text" (arbitrary but reasonable choice):
    if not s:
        return True
    # Get the substring of s made up of non-text characters
    t = s.translate(_null_trans, text_characters)
    # s is 'text' if less than 30% of its characters are non-text ones:
    return len(t)/len(s) <= threshold

print istext("dkdkdkd")
print istext("")

def istextfile(filename, blocksize=512, **kwds):
    return istext(open(filename).read(blocksize), **kwds)

little = "abcdef"
big = "ABCDEf"
print little.upper() #ABCDEF
print big.lower()    #abcdef
print little.capitalize() #Abcdef
print big.capitalize()  #Abcdef

print 'one tWo thrEe'.capitalize( )
#One two three
titled='one tWo thrEe'.title( )
print titled
#One Two Three

print little.isupper();
print big.islower();
print titled.istitle();

def iscapitalized1(s):
    return s == s.capitalize( )

import string
notrans = string.maketrans('', '')  # identity "translation"
def containsAny(str, strset):
    return len(strset) != len(strset.translate(notrans, str))
def iscapitalized(s):
    return s == s.capitalize( ) and containsAny(s, string.letters)

