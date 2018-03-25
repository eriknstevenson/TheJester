import serial

scriptTitle = "The Jester"
scriptDescription = "Gesture Controlled Wheelchair"


# After performing the unlock gesture, Jester is activated.
def onUnlock():
  arduinoPort = '/dev/ttyACM1'

  print("Setting locking policy to none.")
  myo.setLockingPolicy("none")
  myo.rotSetCenter()

  # Connect to arduino if not already
  if not hasattr(myo, 'ser'):
    print("Connecting to Arduino on " + arduinoPort)
    myo.ser=serial.Serial(arduinoPort)
    print(myo.ser.portstr)

  myo.moving = False
  myo.turning = False
  

def onPoseEdge(pose, edge):
  
  print(pose)
  
  if not hasattr(myo, 'ser'): return
  if not hasattr(myo, 'moving'): return
  if not hasattr(myo, 'turning'): return
  if edge == 'off': return
  
  if pose == 'fist':   
    myo.rotSetCenter()
    print('sending: ' + str(0x00))
    myo.ser.write(chr(0x00))
    myo.moving = True
    myo.turning = False
  elif pose == 'waveIn':
    myo.ser.write(chr(0x11))
    myo.turning = True
  elif pose == 'waveOut':
    myo.ser.write(chr(0x12))
    myo.turning = True
  elif pose == 'rest' and (myo.moving == True or myo.turning == True):
    print('sending: ' + str(0xFF))
    myo.ser.write(chr(0xff))
    myo.moving = False
    myo.turning = False


# Read and display serial messages from the Arduino.
def onPeriodic():
  if not hasattr(myo, 'ser'): return

  while myo.ser.in_waiting:
    line = myo.ser.readline()
    print('received msg: ' + line)

def onBoxChange(box, edge):
  if not hasattr(myo, 'ser'): return
  if not hasattr(myo, 'moving'): return
  if not hasattr(myo, 'turning'): return
  
  if not myo.moving or myo.turning: return

  print("sending: " + str(box))
  myo.ser.write(chr(box))


