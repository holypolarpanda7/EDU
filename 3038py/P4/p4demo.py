
from p4primetest import is_prime

for i in range(3,104):          ## we are guaranteed will be > 2
    if is_prime(i):
        print(i)
