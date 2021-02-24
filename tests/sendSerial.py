import serial
import sys
import time

from pynput import keyboard

arc_test_string_cw  = "joy right 0.3 0.0"
arc_test_string_ccw  = "joy right -0.3 -0.0"
arc_test_string_stop = "joy right 0.0 0.0"

arc_test_string_fwd  = "joy right 0.0 0.3"
arc_test_string_bkw  = "joy right -0.0 -0.3"

ser = serial.Serial(
    port='/dev/ttyACM1',\
    baudrate=115200,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=1)

print("connected to: " + ser.portstr)
i = 0x00

def test5(s):
    b = arc_test_string_fwd
    s.write(b.encode())

def test2(s):
    print "CCW"
    b = arc_test_string_ccw
    s.write(b.encode())
    time.sleep(5.0)
    print "CW"
    b = arc_test_string_cw
    s.write(b.encode())
    time.sleep(5.0)
    print "stop"
    b = arc_test_string_stop
    s.write(b.encode())
    time.sleep(5.0)




def keyboard_joystick(s):
  with keyboard.Events() as events:
      event = events.get(1e6)
      if event.key == keyboard.KeyCode.from_char('w'):
         s.write(arc_test_string_fwd.encode())
         return 0
      if event.key == keyboard.KeyCode.from_char('s'):
         s.write(arc_test_string_bkw.encode())
         return 0
      if event.key == keyboard.KeyCode.from_char('a'):
         s.write(arc_test_string_ccw.encode())
         return 0
      if event.key == keyboard.KeyCode.from_char('d'):
         s.write(arc_test_string_cw.encode())
         return 0

test5(ser)

ser.close()
