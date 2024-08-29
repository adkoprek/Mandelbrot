#  __  __                 _      _ _               _   
# |  \/  |               | |    | | |             | |  
# | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
# | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
# | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
# |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
#        https://github.com/adkoprek/Mandelbrot
#
# This script is used to create a color palette with 
# monotone cubic interpolation to color the Mandelbrot
# set
#
# @Author: Adam Koprek
# @Contributors: -
# @Licence: MIT

import matplotlib.pyplot as plt     # pip install matplotlib
import numpy as np                  # Ships with matplotlib


# Class to calculate Monotone cubic interpolation
# From: https://github.com/antdvid/MonotonicCubicInterpolation/tree/master
class monospline:
    def __init__(self, x, y):
        self.x = np.array(x)
        self.y = np.array(y)
        self.n = self.y.size
        self.h = self.x[1:] - self.x[:-1]
        self.m = (self.y[1:] - self.y[:-1]) / self.h
        self.a = self.y[:]
        self.b = self.compute_b()
        self.c = (3 * self.m - self.b[1:] - 2 * self.b[:-1]) / self.h
        self.d = (self.b[1:] + self.b[:-1] - 2 * self.m) / (self.h * self.h)

    def compute_b(self):
        b = np.empty(self.n)
        for i in range(1, self.n - 1):
            is_mono = self.m[i - 1] * self.m[i] > 0
            if is_mono:
                b[i] = 3 * self.m[i - 1] * self.m[i] / (max(self.m[i - 1], self.m[i]) + 2 * min(self.m[i - 1], self.m[i]))
            else:
                b[i] = 0
            if is_mono and self.m[i] > 0:
                b[i] = min(max(0, b[i]), 3 * min(self.m[i - 1], self.m[i]))
            elif is_mono and self.m[i] < 0:
                b[i] = max(min(0, b[i]), 3 * max(self.m[i - 1], self.m[i]))

        b[0] = ((2 * self.h[0] + self.h[1]) * self.m[0] - self.h[0] * self.m[1]) / (self.h[0] + self.h[1])
        b[self.n - 1] = ((2 * self.h[self.n - 2] + self.h[self.n - 3]) * self.m[self.n - 2]
                         - self.h[self.n - 2] * self.m[self.n - 3]) / (self.h[self.n - 2] + self.h[self.n - 3])
        return b

    def evaluate(self, t_intrp):
        ans = []
        for tau in t_intrp:
            i = np.where(tau >= self.x)[0]
            if i.size == 0:
                i = 0
            else:
                i = i[-1]
            i = min(i, self.n-2)
            res = self.a[i] + self.b[i] * (tau - self.x[i]) + self.c[i] * np.power(tau - self.x[i], 2.0) + self.d[i] * np.power(tau - self.x[i], 3.0) #original curve r(t)
            ans.append(res)
        return ans

    def evaluate_derivative(self, t_intrp):
        ans = []
        if not hasattr(t_intrp, "__len__"):
            t_intrp = np.array([t_intrp])
        for tau in t_intrp:
            i = np.where(tau >= self.x)[0]
            if i.size == 0:
                i = 0
            else:
                i = i[-1]
            i = min(i, self.n-2)
            res = self.b[i] + 2 * self.c[i] * (tau - self.x[i]) + 3 * self.d[i] * np.power(tau - self.x[i], 2.0)
            ans.append(res)
        if len(ans) == 1:
            return ans[0]
        else:
            return ans

    def evaluate_forward(self, t_intrp):
        ans = []
        for tau in t_intrp:
            i = np.where(tau >= self.x)[0]
            if i.size == 0:
                i = 0
            else:
                i = i[-1]
            i = min(i, self.n-2)
            res = self.a[i] + self.b[i] * (2 * tau - self.x[i]) + self.c[i] * (tau - self.x[i]) * (3*tau - self.x[i]) \
                  + self.d[i] * np.power(tau - self.x[i], 2.0) * (4 * tau - self.x[i]) # d(xy)/dx
            ans.append(res)
        return ans


if __name__ == "__main__":
    # Define the RGB chanel points
    # From: https://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
    x       = [  0, 0.16, 0.42, 0.6425, 0.8575,   1]
    y_red   = [  0,   32,  237,    255,      0,   0]
    y_green = [  7,  107,  255,    170,      0,   0]
    y_blue  = [100,  203,  255,    0,        0, 100]

    x_intrp = np.linspace(0, 1, 2048)
    intrp_red   = monospline(x, y_red).evaluate(x_intrp)
    intrp_green = monospline(x, y_green).evaluate(x_intrp)
    intrp_blue  = monospline(x, y_blue).evaluate(x_intrp)
    
    for i in range(len(x_intrp)):
        intrp_red[i]   = max(intrp_red[i],   0)
        intrp_red[i]   = min(intrp_red[i],   255)
        intrp_green[i] = max(intrp_green[i], 0)
        intrp_green[i] = min(intrp_green[i], 255)
        intrp_blue[i]  = max(intrp_blue[i],  0)
        intrp_blue[i]  = min(intrp_blue[i],  255)

    plt.plot(x_intrp, intrp_red,   'r-',)
    plt.plot(x_intrp, intrp_green, 'g-',)
    plt.plot(x_intrp, intrp_blue,  'b-',)

    data_row = []
    file = open("cpp_array.txt", "w+")
    file.write("const unsigned char rgb[][3] = {\n")
    text = "\t"
    for i in range(len(intrp_red)):
        data_row.append([intrp_red[i], intrp_green[i], intrp_blue[i]])
        text += "{" + str(int(intrp_red[i])) + ", " + str(int(intrp_green[i])) + ", "
        text += str(int(intrp_blue[i])) + "}, "
        if (i + 1) % 5 == 0:
            text += "\n"
            file.write(text)
            text = "\t"
        
    file.write("};")
    file.close()

    data = []
    for i in range(300):
        data.append(data_row)
    rgb_array = np.array(data, dtype=np.uint8)
    plt.imshow(rgb_array)
    plt.axis('off') 
    plt.show()
