from tkinter import *
import pylab
from pylab import *
import time

# The code segment that handles the GUI

class GUI():

    def __init__(self):
        global reps
        global repcount_bool

        self.root = Tk()


        frame1 = Frame(self.root)
        frame1.pack(side = LEFT)

        #setting the min row and col size for smooth effects
        frame1.rowconfigure(1, minsize =150)
        frame1.rowconfigure(3, minsize =150)
        frame1.columnconfigure(0,minsize = 50)
        frame1.columnconfigure(1,minsize = 120)
        frame1.columnconfigure(3,minsize = 120)
        frame1.columnconfigure(4,minsize = 50)

        #adding the 4 arrows as pic, and the acel lbls
        self.label = []
        arrowpic = []
        self.acel_lbl = []
        for i in [1,2,3,4]:
            filepath = "arrow"+str(i)+".gif"
            arrowpic.append (PhotoImage(file = filepath))  
            self.label.append ( Label(frame1, image = arrowpic[i-1]))
            self.acel_lbl.append(Label(frame1, text="  "))
    
        #adding the barbell pic
        barbellpic = PhotoImage(file = "barbell.gif")
        barbell_label = Label(frame1, image = barbellpic)

        #arranging the pics and acel Labels in the correct order
        self.label[0].grid(row=3,column=2)
        self.label[1].grid(row=1,column =2)
        self.label[2].grid(row =2,column =1)
        self.label[3].grid(row =2, column=3)
        barbell_label.grid(row = 2, column = 2)

        self.acel_lbl[0].grid(row=4,column=2)
        self.acel_lbl[1].grid(row=0,column =2)
        self.acel_lbl[2].grid(row =2,column =0)
        self.acel_lbl[3].grid(row =2, column=4)

        #adding the Squeeze Pressure
        self.forcelabel = Label(frame1, text = "Force Applied = 0 lb", font = "Helvetica 12 bold italic")
        self.forcelabel.grid(row =5, column = 2)
     
        self._update()
        self.root.mainloop()


    #the method to update the graphics based on the value in the data
    def _update(self): 
        global reps, repcount_bool
        #global repcount_bool
       
        pullData = open('testdata.txt', 'r').read()
        dataArray = pullData.split('\n')

        for eachline in dataArray:
            try:
                if len (eachline) > 1:
                    u,v,w,x,y,z = eachline.split(',')
            except Exception:
                #print("Error occured")
                pass
        try :
            Gyro = float(x)
            Az = float(z)
        except Exception:
            Gyro = 0
            Az = 1
        
        #Turning the pics on/off
        for i in range(4):
            self.label[i].grid_remove()
            self.acel_lbl[i].configure(text = "  ")

        if ( Gyro > 5):
            self.label[2].grid()
        elif (Gyro < -5):    
            self.label[3].grid()

        if ( Az > 1.05):
            self.label[1].grid()
        elif (Az < 0.85):    
            self.label[0].grid()
        
        #updating the ForceApplied Label
        self.forcelabel.configure(text = "Force Applied: %s lb" %w)
        self.root.after(30,self._update)


test = GUI()
