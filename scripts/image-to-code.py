#!/usr/bin/env python
# Script to generate image header file
# Add images directory in scripts and put images in that directory

import os
import argparse
import shutil

script_dir = os.path.dirname(os.path.realpath(__file__))

path = os.path.join(script_dir, "images")

img_ext = ['.jpg', '.bmp', '.png', '.gif']
images = [fn for fn in os.listdir(path)
              if any(fn.endswith(ext) for ext in img_ext)]

out_path = os.path.join(script_dir, "generated")

try:
    os.mkdir(out_path)
except OSError as exception:
    print exception

header_file = open(os.path.join(out_path, "screens.h"), "w")
header_file.write("/* this is a generated file */\n")
header_file.write("""#ifndef SCREENS_H
#define SCREENS_H

""")


c_images = "image_t images[] = {"
enum = "enum screen_index {\n"

for image in images:
    print "processing image: " + image
    stripped_image = image.replace('.','').replace('-','')
    xbm_file = os.path.join(out_path, stripped_image + ".xbm")

    cmd = "convert " + os.path.join(path, image) + " -monochrome -resize 200x200 " + xbm_file
    os.system(cmd)
    xbm_f = open(xbm_file, "r")
    header_file.write(xbm_f.read())
    os.remove(xbm_file)

    xpos = 0
    ypos = 0
    width = stripped_image + "_width"
    height = stripped_image + "_height"
    c_images += "{ %d, %d, %s, %s, %s_bits}," % (xpos, ypos, width, height, stripped_image)
    enum += "  " + stripped_image.upper() + ",\n"

c_images += "};"
enum += "};"

header_file.write(enum+"\n")
header_file.write(c_images +"\n")
header_file.write("void display_images(enum screen_index index);\n\n")

header_file.write("#endif")
header_file.close()

shutil.move(os.path.join(out_path, "screens.h"), os.path.join(script_dir, "..", "source", "screens.h"))