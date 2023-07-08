

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

        return buffer
