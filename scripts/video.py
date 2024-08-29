#  __  __                 _      _ _               _   
# |  \/  |               | |    | | |             | |  
# | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
# | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
# | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
# |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
#        https://github.com/adkoprek/Mandelbrot
#
# This script can be used to create a compressed mp4
# video from the frames calculated by mandelbrot_video
#
# @Author: Adam Koprek
# @Contributors: -
# @Licence: MIT

import cv2  # pip install opencv-python
import glob # standart lib

# End with a slash (e.g. Backslash)
PATH = "/Path/To/Your/Calculated/Frames/Directory/"


sample_img = cv2.imread(PATH + "0.png", cv2.IMREAD_UNCHANGED)
height, width, layers = sample_img.shape

fourcc = cv2.VideoWriter.fourcc(*'mp4v')
video = cv2.VideoWriter("video.mp4", fourcc, 40, (width, height))

file_names = glob.glob(PATH + "*.png")
for file_name in file_names:
    img = cv2.imread(file_name)
    video.write(img)

cv2.destroyAllWindows()
video.release()
