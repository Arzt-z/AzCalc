from ili9XXX import st7789
import lvgl as lv
from machine import Pin
import time

labelBuffer = None
mainboxStyle = None
labelMainbox = None
colorBuffer = None
colorMain1 = None
colorMain2 = None
colorBG = None
objModuleButton = None
labelmodule = None

def ui_init():
    lv.init()
    disp = st7789()
    global colorBuffer
    global colorMainBg
    global colorMainB
    global colorBG
    colorBuffer = lv.color_hex(0x118dfa)
    colorMainBg = lv.color_hex(0xa1c5ff)
    colorMainB = lv.color_hex(0xbed5fa)
    colorBG = lv.color_hex(0x709Cb3)
    #colorBG = lv.color_hex(0x082C63)
    #screen
    scr = lv.scr_act()
    scr.set_style_bg_color(colorBG, lv.PART.MAIN)
    #style
    
def moduleButtons(rows, colums, nModules):
    global colorMainBg 
    global colorMainB
    global mainboxStyle
    global objModuleButton
    global labelmodule
    if (int((240/rows)-15)<int((300/colums)-15)):
        button_size=int((240/rows)-15)
    else:
        button_size=int((300/colums)-15)
    objModuleButton = [[lv.obj(lv.scr_act()) for _ in range(rows)] for _ in range(colums)]
    labelmodule = [[lv.label(objModuleButton) for _ in range(rows)] for _ in range(colums)]
    style_module = lv.style_t()
    style_module.init()
    style_module.set_bg_color(colorMainB)
    #style_buffer.set_border_color(lv.palette_darken(lv.PALETTE.LIGHT_BLUE, 3))
    style_module.set_border_color(colorMainBg)
    style_module.set_border_width(4)
    style_module.set_radius(10)
    style_module.set_shadow_width(10)
    style_module.set_shadow_ofs_y(2)
    style_module.set_shadow_opa(lv.OPA._50)
    style_module.set_text_color(lv.color_white())
    style_module.set_height(button_size)
    style_module.set_width(button_size)
    
    count = 0;

    for r in range(rows):
        for c in range(colums):
            if count<nModules:
                objModuleButton[c][r].add_style(style_module, 0)
                labelmodule[c][r] = lv.label(objModuleButton[c][r])
                labelmodule[c][r].set_style_text_color(lv.color_hex(0x00040B), lv.PART.MAIN)
                objModuleButton[c][r].set_pos(((button_size+15)*c)+int((300-((button_size+15)*colums))/2)+15,int(7+240/rows * r))
                labelmodule[c][r].align(lv.ALIGN.CENTER, 0, 0)
                labelmodule[c][r].set_text(str(c)+ "," + str(r))
                                
            else:
                objModuleButton[c][r].delete()
            count+=1;
            
def moduleButtonstext(c,r,text):
    global labelmodule 
    labelmodule[c][r].set_text(text)

def buffer():
    global labelBuffer
    global colorBuffer
    style_buffer = lv.style_t()
    style_buffer.init()
    style_buffer.set_bg_color(colorBuffer)
    #style_buffer.set_border_color(lv.palette_darken(lv.PALETTE.LIGHT_BLUE, 3))
    style_buffer.set_border_width(0)
    style_buffer.set_radius(10)
    style_buffer.set_shadow_width(10)
    style_buffer.set_shadow_ofs_y(2)
    style_buffer.set_shadow_opa(lv.OPA._50)
    style_buffer.set_text_color(lv.color_white())
    style_buffer.set_width(290)
    style_buffer.set_height(30)

    obj_buffer = lv.obj(lv.scr_act())
    obj_buffer.add_style(style_buffer, 0)
    obj_buffer.align(lv.ALIGN.TOP_MID, 0, 8)
    labelBuffer = lv.label(obj_buffer)
    labelBuffer.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN)
    labelBuffer.align(lv.ALIGN.LEFT_MID, 0, 0)
    labelBuffer.set_text("")

def buffer_update(buffer):
    global labelBuffer
    labelBuffer.set_text(buffer)


def mainbox():
    global mainboxStyle
    global labelMainbox
    objMainbox = lv.obj(lv.scr_act())
    labelMainbox = lv.label(objMainbox)
    labelMainbox.set_text("")
    labelMainbox.set_style_text_color(lv.color_hex(0x00040B), lv.PART.MAIN)
    objMainbox.add_style(mainboxStyle, 0)
    objMainbox.align(lv.ALIGN.CENTER, 0, 20)
    
def mainbox_update(result):
    global labelMainbox
    labelMainbox.set_text(result)


def mainbox_style():
    global mainboxStyle
    global colorMainBg 
    global colorMainB
    mainboxStyle = lv.style_t()
    mainboxStyle.init()
    mainboxStyle.set_bg_color(colorMainBg )
    mainboxStyle.set_border_color(colorMainB)
    mainboxStyle.set_border_width(4)
    mainboxStyle.set_radius(10)
    mainboxStyle.set_shadow_width(5)
    mainboxStyle.set_shadow_ofs_y(2)
    mainboxStyle.set_shadow_opa(lv.OPA._50)
    mainboxStyle.set_text_color(lv.color_white())
    mainboxStyle.set_width(300)
    mainboxStyle.set_height(190)
