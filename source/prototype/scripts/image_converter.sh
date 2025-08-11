convert image.png -resize 130x131! -alpha off -define bmp:format=bmp3 -compress none image.bmp

xxd -i image.bmp > image.h
