import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import pylab
from pylab import *

class Plots():
    def __init__(self):
        xAchse=pylab.arange(0,100,1)
        yAchse=pylab.array([0]*100)

        #Settings for Gyro Graph
        fig = pylab.figure(1)
        grph1 = fig.add_subplot(311)
        grph1.grid(True)
        grph1.set_title("Radial Acceleration")
      #  grph1.set_xlabel("sample")
        grph1.set_ylabel("rad/sec")
        grph1.axis([0,100,0,200])
        line1=grph1.plot(xAchse,yAchse,'-')

        #Settings for Ax Graph
        grph2=fig.add_subplot(312)
        grph2.grid(True)
        grph2.set_title("Acceleration in X Axis")
       # grph2.set_xlabel("sample")
        grph2.set_ylabel("g")
        grph2.axis([0,100,0,200])
        line2=grph2.plot(xAchse,yAchse,'-')

        #Settings for Az Graph
        grph3=fig.add_subplot(313)
        grph3.grid(True)
        grph3.set_title("Acceleration in Z Axis")
       # grph3.set_xlabel("Time")
        grph3.set_ylabel("g")
        grph3.axis([0,100,0,200])
        line3=grph3.plot(xAchse,yAchse,'-')
        

        manager = pylab.get_current_fig_manager()


        def animate(i):
            global values
            pullData = open('testdata.txt', 'r').read()
            dataArray = pullData.split('\n')
            iteration = []
            Force_list = []
            Gyro_list = []
            ax_list = []
            az_list = []
            for eachline in dataArray:
              try:
                  if len (eachline) > 1:
                   #u=xbee tx chars, v=iteration,w=Force,x=Gyro,y=Ax,z=Az
                   u,v,w,x,y,z = eachline.split(',')
                   iteration.append(int(v))
                   Force_list.append(float(w))
                   Gyro_list.append(float(x))
                   ax_list.append(float(y))
                   az_list.append(float(z))
              except Exception:
                   #print("Error occured")
                   pass

            
             #Setting the scrolling Xaxis
            CurrentXAxis=pylab.arange((len(iteration)-200),len(iteration),1)
            
            #Plotting the Gyroscope
            Gyro = pylab.array(Gyro_list[(len(Gyro_list)-200):])
            line1[0].set_data(CurrentXAxis,Gyro)
            grph1.axis([CurrentXAxis.min(),CurrentXAxis.max(),-200,200])

            #Plotting the Ax
            Ax = pylab.array(ax_list[(len(ax_list)-200):])
            line2[0].set_data(CurrentXAxis,Ax)
            grph2.axis([CurrentXAxis.min(),CurrentXAxis.max(),-0.4,0.4])

            #Plotting the Az
            Az = pylab.array(az_list[(len(az_list)-200):])
            line3[0].set_data(CurrentXAxis,Az)
            grph3.axis([CurrentXAxis.min(),CurrentXAxis.max(),-2,3])

            try:
                manager.canvas.draw()
            except Exception:
                pass

        timer = fig.canvas.new_timer(interval=20)
        timer.add_callback(animate, ())
        timer.start()

        fig.tight_layout()
        pylab.show()


plot = Plots()