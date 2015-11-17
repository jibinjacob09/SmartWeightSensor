import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

import tkinter as tk
from tkinter import ttk


print ("Hello")

class Interface(tk.Tk):
     def __init__(self):
         pass
        
#     def animate(self):
#        Frame.__init__(self, *args, **kwargs)
#        fig = plt.figure()
#        ax1 = fig.add_subplot(1,1,1,)
#        pullData = open('RawData.txt', 'r').read()
#        dataArray = pullData.split('\n')
#        xar = []
#        yar = []

#        for eachline in dataArray:       
#                 x = float(eachline)
#                 xar.append(x)
#                 #  yar.append(int(y))
#        ax1.clear()
#        ax1.plot(xar)
#        ani = animation.FuncAnimation(fig,animate,interval = 500)


#     plt.show()
 
class Plot(tk.Frame):
    def __init__(self):
        tk.Frame.__init__(self)

        f = Figure(figsize=(5,5), dpi=100)
        a = f.add_subplot(111)
        a.plot([1,2,3,4,5,6,7,8],[5,6,1,3,8,9,3,5])

        canvas = FigureCanvasTkAgg(f,self)
        canvas.show()
        canvas.get_tk_widget()
        canvas.get_tk_widget().pack(side = RIGHT)

app = Plot()
app.mainloop()