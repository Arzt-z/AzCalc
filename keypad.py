from machine import Pin
import time

class keypad:
    
    keypadOUT = [Pin(13, Pin.OUT), Pin(12, Pin.OUT), Pin(14, Pin.OUT), Pin(27, Pin.OUT)]
    kpMulxOUT = [Pin(26, Pin.OUT), Pin(25, Pin.OUT), Pin(33, Pin.OUT), Pin(32, Pin.OUT)]
    kpFilas = 13
    keymapmode = 0
    kpMulxDAT = Pin(34, Pin.IN)
    strLastKey="Inicio"
    
    def __init__(self):
        self.ta = None
        
    def __new__(cls):
        if not hasattr(cls, 'instance'):
          cls.instance = super(keypad, cls).__new__(cls)
        return cls.instance

    for pin in keypadOUT:
        pin.off()

    for pin in kpMulxOUT:
        pin.off()


    Caracteres = [
        [["0",    ".",    " "  ,  "<ANS>",  "=",    ""  ,    ""  ,  "<UP>","<DOWN>", "<LOG>" , "^(1/" ,  "<CALC>",  "<SEND>",   ""     ],
         ["1",    "2",    "3"  ,    "+"  ,  "-",  "<IN>", "<OUT>",   ","  ,  "**"  ,  "**2"  ,  "**3" , "<SOLVE>", "<ALPHA>",   ""     ],
         ["4",    "5",    "6"  ,    "*"  ,  "/",  "(-)" ,   ";"  , "<HYP>", "math.sin(" , "COS("  , "TAN(" ,  "<STO>" ,  "<LEFT>",  "<AC>"  ],
         ["7",    "8",    "9"  , "<DEL>" ,   "",   "<"  ,   ">"  ,     "(",   ")"  , "<ab/c>", "<M+>" ,   "<LN>" ,  "<RIGH>", "<OMEGA>"]],
        
        [["0",    ".",    "x"  ,    "y"  ,  "=",   ""   ,    ""  ,  "<UP>","<DOWN>",   "d"   ,   "e"  , "<SEND+>",  "<SEND>",   ""     ],
         ["1",    "2",    "3"  ,    "+"  ,  "-",   "f"  ,   "g"  ,   "h"  ,   "i"  ,   "j"   ,   "k"  ,     "a"  , "<ALPHA>",   ""     ],
         ["4",    "5",    "6"  ,    "*"  ,  "/",   "l"  ,   "m"  ,   "n"  ,   "o"  ,   "p"   ,   "q"  ,     "b"  ,  "<LEFT>",  "<AC>"  ],
         ["7",    "8",    "9"  , "<DEL>" ,   "",   "r"  ,   "s"  ,   "t"  ,   "v"  ,   "w"   ,   "z"  ,     "c"  ,  "<RIGH>", "<OMEGA>"]],
        
        [["0",    ".",    " "  ,  "<ANS>",  "=",   ""   ,    ""  ,  "<UP>","<DOWN>",   "d"   ,   "e"  , "<SEND+>",  "<SEND>",   ""     ],
         ["1",    "2",    "3"  ,    "+"  ,  "-",   "f"  ,   "g"  ,   "h"  ,   "i"  ,   "j"   ,   "k"  ,     "a"  , "<ALPHA>",   ""     ],
         ["4",    "5",    "6"  ,    "*"  ,  "/",   "l"  ,   "m"  ,   "n"  ,   "o"  ,   "p"   ,   "q"  ,     "b"  ,  "<LEFT>",  "<AC>"  ],
         ["7",    "8",    "9"  , "<DEL>" ,   "",   "r"  ,   "s"  ,   "t"  ,   "v"  ,   "w"   ,   "z"  ,     "c"  ,  "<RIGH>", "<OMEGA>"]]]

    modeLabelTxt=["Calc","Alpha","Shift"]
    

    idMode=0
    idCntl=False

    keyTimeout=1000
    
    #obtener la tecla
    def get_key(self):
        strValue=""
        keyPressed=0
        for idKP,keypadOUT in enumerate( self.keypadOUT):
            keypadOUT.on()
            for idFila in range(14):
                for i in range(4):
                    self.kpMulxOUT[i].on() if (idFila >> i) & 1 else self.kpMulxOUT[i].off()
                if self.kpMulxDAT.value() == 1:
                    strValue=self.Caracteres[self.idMode][idKP][idFila]
                    keyPressed=time.ticks_ms()
                    print("mode"+str(self.idMode)+"F:"+str(idFila)+" C:"+str(idKP))
                if strValue == "<ALPHA>":
                    strValue = ""
                    if self.idMode < 2:
                        self.idMode += 1
                    else:
                        self.idMode = 0
                    
            keypadOUT.off()
            
        if (strValue == self.strLastKey):
            #print("self.lastKeyPressed-keyPressed: "+str( self.lastKeyPressed-keyPressed )+" keyTimeout: "+str( self.keyTimeout ))
            if  (keyPressed-self.lastKeyPressed<self.keyTimeout):
                return ""
            else:
                #print("key: "+strValue+" keyTimeout: "+str( self.keyTimeout ))
                self.keyTimeout=200
                return strValue
        else:
            #print("return key:"+strValue)
            self.keyTimeout=1000
            self.strLastKey=strValue
            self.lastKeyPressed=keyPressed
            return strValue
        
        
    def getModeString(self):
        return self.modeLabelTxt[self.idMode]
    


        
        
        
        
        
        
        
        
