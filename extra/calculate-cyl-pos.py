import numpy as np
 
list1 = [-2.5,0,0]
list2 = [-4.5,-3,4]
vector1 = np.array(list1)
vector2 = np.array(list2)
direction = vector2 - vector1
middle = direction / 2
middle = middle + vector1
norm = direction / np.sqrt(np.sum(np.square(vector1-vector2)))
print("point: " + str(middle))
print("direction: " + str(norm))
