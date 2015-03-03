import picamera
import datetime
from time import sleep

camera = picamera.PiCamera()

while (1==1):
	# Save video to the SD card in 10m chunks
	current_time = datetime.now().strftime('%M:%S.%f')
    camera.start_recording(current_time + '.h264')
	sleep(600)
	camera.stop_recording()