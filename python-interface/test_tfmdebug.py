import tfmdebug
import time

print(tfmdebug.return_hello_world())
print(tfmdebug.return_goodbye_world())
print(tfmdebug.return_0())

begin = time.time()
print(tfmdebug.uses_omp())
end = time.time()
print("Exe time:", end - begin, "s")

begin = time.time()
print(tfmdebug.not_uses_omp())
end = time.time()
print("Exe time:", end - begin, "s")
