
# sorta dumb program to test whether a number is prime or not

from math import sqrt

def is_prime(n):
    if ( n % 2 ) == 0:
        return False
    i = 3
    while i < sqrt(n)+1:
        if ( n % i == 0 ):
            return False
        else:
            i += 2
    return True
