import lvgl as lv
from ili9XXX import st7789
from machine import Pin
import time
import keypad 
import ui
import calc
import math
import gc
mykeypad = keypad.keypad()
calc1 = calc.calc()

ui.ui_init()
ui.styleModulebuttons(2, 3)
ui.moduleButtons(2, 3, 6)
ui.moduleButtonstext(0,0,"calc")
ui.moduleButtonstext(1,0,"graph")
ui.moduleButtonstext(0,1,"AI")
ui.setoutlineModules("")
ui.buffer()
ui.mainbox_style()
ui.mainbox()
ui.hideMainbox()

screenmode = "menu"
buffer=""
result=""
menuModules = [["calc","graph",""],
               ["AI","",""]]
exitloop = False



def evaluate_expression(expression):
    try:
        result = str(eval(expression))
        return result
    except Exception as e:
        return f"uwu"
    
def calcmode():
    global key
    global buffer
    global result
    global screenmode
    ui.switchScreen(screenmode)
    print(screenmode)
    screenmode="calc"
    print("enter mode calc")
    gc.collect()
    print(gc.mem_free())
    a = bytearray(5_000)
    while key!="<OMEGA>":
        print("mode")
        key = mykeypad.get_key()
        buffer = calc1.bufferUpdate(buffer, key)
        result = calc1.evaluate_expression(buffer)
        ui.mainbox_update(result)
        print("Key pressed:", key)
        time.sleep(0.1)                        
    buffer = calc1.bufferUpdate(buffer, "<AC>")

def graphmode():
    global key
    global buffer
    global result
    key = mykeypad.get_key()
    buffer = calc1.bufferUpdate(buffer, key)
    ui.buffer_update(buffer)
    result = evaluate_expression(buffer)
    ui.mainbox_update(result)
    print("Key pressed:", key)
    time.sleep(0.1)
    
while True:
    exitloop = False

    screenmode="menu"
    while exitloop == False :
        key = mykeypad.get_key()
        
        if key != "":
            print("Key pressed:", key)
            if key=="<SEND>" or key=="5" :
                row=ui.getCurrentRow()
                colum=ui.getCurrentColum()
                if menuModules[row][colum] == "calc":
                    exitloop= True
                    calcmode()
                elif menuModules[row][colum] == "graph":
                    exitloop= True
                    calc1.initgraph( 5, 5, 5, 5)
                    calcmode()
                    
                elif menuModules[row][colum] == "AI":
                    screenmode="AI"
                    print("enter mode AI")
            else:
                ui.setoutlineModules(key)
    ui.switchScreen(screenmode)
                    
                
            

#lv.scr_load(scr)

    
    
    
    
    
    
    
    
    
    

    