# A python study
#trying to fix some concepts that you do not learn when you're coding python in
#need basis

import decimal 
from fractions import Fraction


#Numbers
a=0b1010
b=0xA
c=0o12
d=8-6j
print(" %d, %d, %d, %d" % (a,b,c,abs(d)))

a = 13
if 10<a<14:
   print("Pre-adolescent")
else:
    print("Dunno")

#if the number needs more than 2 decimal places "it seems not work" (really?)
decimal.getcontext().prec=2
a = decimal.Decimal(1)
b = decimal.Decimal(9)
print(a/b)

a = Fraction(3,4)+Fraction(0.25)
print(a)

a = (0.5).as_integer_ratio()
print(a)
a = Fraction(*a)
print(a)


#sets - > assumimg python 2.X
a = set([1,2,3])
b = set([2,3,4,5])
print a-b,b-a,a|b,a&b,a^b
print 2 in a

#=============================================
# STRINGS 
#
print('this is a "string" , believe me ')
print("this is also a \n 'string'")
print (r"this is not a \newline char")
print (u"Unicode string ?  This is a pencil \uE400")

print """ This is long string string. It starts here ....
Oh wait! There still more here....
And here...
Oh Look! we are close to the end.
Oh yeah, this is the end"
Oh no I lied ! This is the real end """

print "what is the lenght of an unicode string?", ("\uE400"), len ("\uE400")

print("12345 in binary is "+bin(12345))

print("And he yelled G"+ ("o"*10) +"al!")

print("12345"[0:-1] + "does not have 5 or 1")
print("Remove the Xs: " +"AXnZdXrXe"[::2])

print("Interview question: invert a string: " + "123456789"[::-1])

print("Repr is not the same as \tstr - " + repr("Repr is not the same as \tstr"))




