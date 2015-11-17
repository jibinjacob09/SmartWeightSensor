import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import pylab
from pylab import *

class Plots():
    def __init__(self):
        xAchse=pylab.arange(0,100,1)
        yAchse=pylab.array([0]*100)

        fig = pylab.figure(1)
        ax = fig.add_subplot(311)
        ax.grid(True)
        ax.set_title("Acceleration in Z Axis")
        ax.set_xlabel("Time")
        ax.set_ylabel("g")
        ax.axis([0,100,0,200])
        line1=ax.plot(xAchse,yAchse,'-')

        ax2=fig.add_subplot(312)
        ax2.grid(True)
        ax2.set_title("Acceleration in X Axis")
        ax2.set_xlabel("Time")
        ax2.set_ylabel("g")
        ax2.axis([0,100,0,200])

        ax2=fig.add_subplot(312)
        ax2.grid(True)
        ax2.set_title("Acceleration in X Axis")
        ax2.set_xlabel("Time")
        ax2.set_ylabel("g")
        ax2.axis([0,100,0,200])


        line2=ax2.plot(xAchse,yAchse,'-')

        manager = pylab.get_current_fig_manager()


        def animate(i):
            global values
            pullData = open('testdata.txt', 'r').read()
            dataArray = pullData.split('\n')
            xar = []
            yar = []
            zar = []
            for eachline in dataArray:
              try:
                  if len (eachline) > 1:
                   x,y,z = eachline.split(',')
                   #print(x + " " + y + "  " + z)
                   xar.append(int(x))
                   yar.append(int(y))
                   zar.append(float(z))
              except Exception:
                   #print("Error occured")
                   pass

            CurrentXAxis=pylab.arange((len(yar)-100),len(yar),1)
            yval = pylab.array(yar[(len(yar)-100):])
            line1[0].set_data(CurrentXAxis,yval)
            ax.axis([CurrentXAxis.min(),CurrentXAxis.max(),-1.5,200])

            zval = pylab.array(zar[(len(zar)-100):])
            line2[0].set_data(CurrentXAxis,zval)
            ax2.axis([CurrentXAxis.min(),CurrentXAxis.max(),-1.5,600])

            manager.canvas.draw()


        timer = fig.canvas.new_timer(interval=50)
        timer.add_callback(animate, ())
        timer.start()


        pylab.show()


plot = Plots()