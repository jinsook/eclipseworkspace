'''
Created on Nov 1, 2009

@author: jin
'''
import itertools
def anyTrue(predicate, sequence):
    return True in itertools.imap(predicate, sequence)
def endsWith(s, *endings):
    return anyTrue(s.endswith, endings)

import os
filenames = ['aa.jpg', 'bb.gif' ,'cc.cc' ,'dd.jpeg']
#for filename in os.listdir('.'):
for filename in filenames:
    if endsWith(filename, '.jpg', '.jpeg', '.gif'):
       print ' ' + filename

#Recipe 1.20. Handling International Text with Unicode 
german_ae = unicode('\xc3\xa4', 'utf8')
sentence = "This is a " + german_ae
sentence2 = "Easy!"
para = ". ".join([sentence, sentence2])
print german_ae
print sentence
print para
