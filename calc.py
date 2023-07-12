import math
import ui
from ili9XXX import st7789
import lvgl as lv

class calc:
    
    def __init__(self):
        self.ta = None

    def bufferUpdate(self, buffer, key):
        if key == "<DEL>":
            buffer = buffer[:-1]
        elif key == "<AC>":
            buffer = ""
        elif key:
            buffer += key
        ui.buffer_update(buffer)
        return buffer
    
    def evaluate_expression(self, expression):
        try:
            result = str(eval(expression))
            return result
        except Exception as e:
            return f"uwu"

    
    def initgraph(self, minX, maxX, minY, maxY):
        chart = lv.chart(lv.scr_act())
        chart.set_size(270, 160)
        chart.align(lv.ALIGN.CENTER, 5, 20)

        chart.set_axis_tick(lv.chart.AXIS.PRIMARY_Y, 10, 5, math. ceil(maxX*(160/270)), 5, True, 30)
        chart.set_axis_tick(lv.chart.AXIS.PRIMARY_X, 10, 5, maxX, 5, True, 30)

        chart.refresh_ext_draw_size()

        self.cursor = chart.add_cursor(lv.palette_main(lv.PALETTE.BLUE), lv.DIR.LEFT | lv.DIR.BOTTOM)

        self.ser = chart.add_series(lv.palette_main(lv.PALETTE.RED), lv.chart.AXIS.PRIMARY_Y)
    
    def 