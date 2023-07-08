import lvgl as lv
from ili9XXX import st7789
from machine import Pin
import time
import keypad 
import ui
import calc
import math

mykeypad = keypad.keypad()
calc1 = calc.calc()

ui.ui_init()
#ui.buffer()
#ui.mainbox_style()
#ui.mainbox()
buffer=""
result=""
menuModules = [["calc"],[""]]

ui.moduleButtons(2, 2, 4)
ui.moduleButtonstext(0,0,"calc")
ui.moduleButtonstext(0,0,"graph")

def evaluate_expression(expression):
    try:
        result = str(eval(expression))
        return result
    except Exception as e:
        return f"uwu"


while True:
    key = mykeypad.get_key()
    buffer = calc1.bufferUpdate(buffer, key)
    ui.buffer_update(buffer)
    result = evaluate_expression(buffer)
    ui.mainbox_update(result)
    print("Key pressed:", key)
        
    time.sleep(0.1)

#lv.scr_load(scr)

    
    
    
    
    
    
    
    
    
    

    