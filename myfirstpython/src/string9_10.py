'''
Created on Oct 30, 2009

@author: jin
'''


import string
def translator(frm='', to='', delete='', keep=None):
    if len(to) == 1:
        to = to * len(frm)
    trans = string.maketrans(frm, to)
    if keep is not None:
        allchars = string.maketrans('', '')
        delete = allchars.translate(allchars, keep.translate(allchars, delete))
    def translate(s):
        return s.translate(trans, delete)
    return translate


digits_only = translator(keep=string.digits)
print digits_only('Chris Perkins : 224-7992') #'2247992'
no_digits = translator(delete=string.digits)
print no_digits('Chris Perkins : 224-7992') #'Chris Perkins : -'

digits_to_hash = translator(frm=string.digits, to='#')
print digits_to_hash('Chris Perkins : 224-7992') #'Chris Perkins : ###-####'

trans = translator(delete='abcd', keep='cdef')
print trans('abcdefg') #'ef'

#Recipe 1.10. Filtering a String for a Set of Characters
# Make a reusable string of all characters, which does double duty
# as a translation table specifying "no translation whatsoever"
allchars = string.maketrans('', '')
def makefilter(keep):
    """ Return a function that takes a string and returns a partial copy
        of that string consisting of only the characters in 'keep'.
        Note that `keep' must be a plain string.
    """
    # Make a string of all characters that are not in 'keep': the "set
    # complement" of keep, meaning the string of characters we must delete
    delchars = allchars.translate(allchars, keep)
    # Make and return the desired filtering function (as a closure)
    def thefilter(s):
        return s.translate(allchars, delchars)
    return thefilter

just_vowels = makefilter('aeiouy')
print just_vowels('four score and seven years ago')
# emits: ouoeaeeyeaao
print just_vowels('tiger, tiger burning bright')
# emits: ieieuii


def canonicform(s):
    """ Given a string s, return s's characters as a canonic-form string:
        alphabetized and without duplicates. """
    return makefilter(s)(allchars)

print canonicform('aeiouy')
print canonicform('four score and seven years ago')

#unicode
import sets
class Keeper(object):
    def __init__(self, keep):
        self.keep = sets.Set(map(ord, keep))
    def __getitem__(self, n):
        if n not in self.keep:
            return None
        return unichr(n)
    def __call__(self, s):
        return unicode(s).translate(self)
makefilter = Keeper

just_vowels = makefilter('aeiouy')
print just_vowels(u'four score and seven years ago')
# emits: ouoeaeeyeaao
print just_vowels(u'tiger, tiger burning bright')
# emits: ieieuii
#if __name__ == '__main__':
#    pass