import mwedebug
import time

print(mwedebug.return_hello_world())
print(mwedebug.return_goodbye_world())
print(mwedebug.return_0())

begin = time.time()
print(mwedebug.uses_omp())
end = time.time()
print("Exe time:", end - begin, "s")

begin = time.time()
print(mwedebug.not_uses_omp())
end = time.time()
print("Exe time:", end - begin, "s")
