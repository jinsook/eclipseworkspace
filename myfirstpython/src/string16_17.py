'''
Created on Nov 1, 2009

@author: jin
'''
#Recipe 1.16. Interpolating Variables in a String
def expand(format, d, marker='"', safe=False):
    if safe:
        def lookup(w): return d.get(w, w.join(marker*2))
    else:
        def lookup(w): return d[w]
    parts = format.split(marker)
    parts[1::2] = map(lookup, parts[1::2])
    return ''.join(parts)

print expand('just "a" test', {'a': 'one'})
print expand('just "b" test', {'a': 'one'},safe=True)
print expand('just "a" ""little"" test', {'a' : 'one', '' : '"'})
print expand('just "b" ""little"" test', {'a' : 'one', '' : '"'}, safe=True)

#Recipe 1.17. Interpolating Variables in a String in Python 2.4
import string
# make a template from a string where some identifiers are marked with $
new_style = string.Template('this is $thing')
# use the substitute method of the template with a dictionary argument:
print new_style.substitute({'thing':5})      # emits: this is 5
print new_style.substitute({'thing':'test'}) # emits: this is test
# alternatively, you can pass keyword-arguments to 'substitute':
print new_style.substitute(thing=5)          # emits: this is 5
print new_style.substitute(thing='test')     # emits: this is test
form_letter = '''Dear $customer,
I hope you are having a great time.
If you do not find Room $room to your satisfaction,
let us know. Please accept this $$5 coupon.
            Sincerely,
            $manager
            ${name}Inn'''
letter_template = string.Template(form_letter)
print letter_template.substitute({'name':'Sleepy', 'customer':'Fred Smith',
                                  'manager':'Barney Mills', 'room':307,
                                 })

msg = string.Template('the square of $number is $square')
for number in range(10):
    square = number * number
    print msg.substitute(locals( ))
    
msg = string.Template('the square of $number is $square')
for i in range(10):
    print msg.substitute(number=i, square=i*i)
    
msg = string.Template('the square of $number is $square')
for number in range(10):
    print msg.substitute(locals( ), square=number*number)

#In case of any conflict between entries in the dictionary and the values explicitly passed as keyword arguments, the keyword arguments take precedence. For example:
msg = string.Template('an $adj $msg')
adj = 'interesting'
print msg.substitute(locals( ), msg='message')
# emits an interesting message