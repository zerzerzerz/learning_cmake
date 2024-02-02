import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), 'build'))

import pybind11_example
print(dir(pybind11_example))
print(pybind11_example.__file__)
print(pybind11_example.__doc__)

tmp_name = "Yukino Yukinoshita"
pybind11_example.greet(tmp_name)
pybind11_example.hello(tmp_name)
pybind11_example.goodbye(tmp_name)

s = pybind11_example.Student("John", 20)
print("Name is {}".format(s.getName()))
print("Age is {}".format(s.getAge()))
s.setAge(21)
print("Age is {}".format(s.getAge()))

ans = pybind11_example.calc_e(10000)
print(ans)

ans = pybind11_example.calc_pi(10000)
print(ans)

ans = pybind11_example.calc_sqrt(123)
print(ans)

