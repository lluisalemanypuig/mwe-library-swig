import mwe
import time

print(mwe.return_hello_world())
print(mwe.return_goodbye_world())
print(mwe.return_0())

begin = time.time()
print(mwe.uses_omp())
end = time.time()
print("Exe time:", end - begin, "s")

begin = time.time()
print(mwe.not_uses_omp())
end = time.time()
print("Exe time:", end - begin, "s")
