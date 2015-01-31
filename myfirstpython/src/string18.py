'''
Created on Nov 1, 2009

@author: jin
'''
import re
def multiple_replace(text, adict):
    print '|'.join(map(re.escape, adict))
    rx = re.compile('|'.join(map(re.escape, adict)))
    def one_xlat(match):
        print match.group(0)
        return adict[match.group(0)]
    return rx.sub(one_xlat, text)

import re
def make_xlat(*args, **kwds):
    adict = dict(*args, **kwds)
    rx = re.compile('|'.join(map(re.escape, adict)))
    def one_xlat(match):
        return adict[match.group(0)]
    def xlat(text):
        return rx.sub(one_xlat, text)
    #sub( pattern, repl, string[, count]) 
    return xlat

text = "Larry Wall is the creator of Perl"
adict = {
  "Larry Wall" : "Guido van Rossum",
  "creator" : "Benevolent Dictator for Life",
  "Perl" : "Python",
}
print multiple_replace(text, adict)
translate = make_xlat(adict)
print translate(text)

rx = re.compile(r'\b%s\b' % r'\b|\b'.join(map(re.escape, adict)))

class make_xlat2:
    def __init__(self, *args, **kwds):
        self.adict = dict(*args, **kwds)
        self.rx = self.make_rx( )
    def make_rx(self):
        return re.compile('|'.join(map(re.escape, self.adict)))
    def one_xlat(self, match):
        return self.adict[match.group(0)]
    def __call__(self, text):
        return self.rx.sub(self.one_xlat, text)

print make_xlat(adict)(text)