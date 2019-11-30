import serial
import pyautogui
from time import sleep
ser=serial.Serial('com7',9600)
pyautogui.FAILSAFE = False
pyautogui.MINIMUM_DURATION=0.3
while 1:
    
    k=ser.read(15)
    k=k.decode('utf-8')
    print(k)
    
    xi=k.find("x")
    yi=k.find("y")
    li=k.find("l")
    ri=k.find("r")
    # cursor=k[:6]
    # click=k[6:]
    # x=cursor[:3]
    
    # y=cursor[3:]
    
    l=k[li+1:ri]
    r=k[ri+1:]
    xcor=int(k[xi+1:yi])
    ycor=int(k[yi+1:li].strip())
    if xcor>1366:
        xcor=1366
    if ycor>768:
        ycor=768
    if xcor<0:
        xcor=0
    if ycor<0:
        ycor=0
    pyautogui.moveTo(xcor,ycor)
    
