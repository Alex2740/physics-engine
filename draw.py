from matplotlib import pyplot as plt

import numpy as np

LEN = 40000


if __name__ == '__main__':
    # data = list()
    data2 = np.zeros((LEN, 3))

    with open("./log.txt") as f:
        for i in range(0, LEN):
            f.readline()
            # data.append(f.readline())
            line = f.readline()[8:-2].split(',')
            if (len(line) == 1  ):
                break
            data2[i][0] = line[0]
            data2[i][1] = line[1]
            data2[i][2] = line[2]
            # data2[i] = f.readline()

    x = np.arange(0, LEN)
    plt.plot(x, data2.T[0], x, data2.T[1], x, data2.T[2])
    # plt.plot(x, np.linalg.norm(data2.T, axis=0))
    plt.show()
    
    print(data2)