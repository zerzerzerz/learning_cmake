import os

# remove *.out, *.so, *.o, *.a
for root, dirs, files in os.walk('.'):
    for file in files:
        if file.endswith('.out') or file.endswith('.so') or file.endswith('.o') or file.endswith('.a'):
            os.remove(os.path.join(root, file))
