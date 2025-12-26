# test.py

# ООП МК (ІІ)+

# ================================= 1 ===============================

# import sys
#
# mylist = range(0, 10000)
# print(sys.getsizeof(mylist))
# 48
#
# myreallist = [x for x in range(0, 10000)]
# print(sys.getsizeof(myreallist))
# 85176

# ================================= 2 ===============================

# original = [('a', 'b'), ('c', 'd'), ('e', 'f')]
# transposed = zip(*original)
# print(list(transposed))
# [('a', 'c', 'e'), ('b', 'd', 'f')]

# ================================= 3 ===============================

# from itertools import starmap
#
# # квадрати
# x = starmap(pow, [(2, 5), (3, 2), (10, 3)])
# print(list(x))
# # [32, 9, 1000]
#
# # max
# x = starmap(max, [(2, 5, 4), (3, 2, 1), (10, 3, 8)])
# print(list(x))
# # [5, 3, 10]
#
# # min
# x = starmap(min, [(2, 5, 9, 3), (3, 2, 6, 8), (1, 0, 10, 3)])
# print(list(x))
# # [2, 2, 0]

# ================================= 4 ===============================

# a = '1,2,3'
# d = dict.fromkeys(a)
# print(len(d.keys()))

# ================================= 5 ===============================

# s = {i**2 for i in range(10)}
# d = {i: i**2 for i in range(10)}
#
# print(s)
# # {0, 1, 64, 4, 36, 9, 16, 49, 81, 25}
# print(d)
# # {0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81}

# ================================= 6 ===============================

# fruit = iter(['apple', 'banana', 'cherry'])
#
# print(next(fruit, 'STOP'))
# # apple
# print(next(fruit, 'STOP'))
# # banana
# print(next(fruit, 'STOP'))
# # cherry
# print(next(fruit, 'STOP'))
# # STOP

# ================================= 7 ===============================

# import collections
#
# d = collections.OrderedDict()
# d[1] = 100
# d[2] = 200
#
# print(d)
# # OrderedDict({1: 100, 2: 200})

# ================================= 8 ===============================

# keys = ['a', 'b', 'c']
# vals = [1, 2, 3]
#
# zipped = dict(zip(keys, vals))
# print(zipped)
