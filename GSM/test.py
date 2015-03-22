#! /usr/bin/env python
import argparse
from datetime import datetime
import logging
from serial import Serial
from sim900 import Sim900, SMSReader
from time import sleep


LOG_FILE = 'sensor.log'
LOG_LEVEL = logging.INFO
LOG_FORMAT = '%(levelname)s - %(message)s'


def main():
    # Parse command line arguments
    #
    # The default settings will work well for the pcDuino. If you
    # are using a laptop or Raspberry Pi, then you will need to set
    # the serial baud rate to 9600 and make sure the shield is running at 
    # 4800. An alternative is to increase buffer size in the Arduino SoftwareSerial
    # library.
    parser = argparse.ArgumentParser(description='Run SMS Data Logger.')
    parser.add_argument('-p', '--port', help='Serial port', default='/dev/ttyAMA0')
    parser.add_argument('-b', '--baudrate', type=int, help='Baudrate of Sim900 GSM shield', default=9600)
    args = parser.parse_args()

    port = args.port
    baudrate = args.baudrate


    # Setup logger
    logging.basicConfig(level=LOG_LEVEL, format=LOG_FORMAT)

    logger = logging.getLogger()
    file_log_handler = logging.FileHandler(LOG_FILE)
    logger.addHandler(file_log_handler)

    formatter = logging.Formatter(LOG_FORMAT)
    file_log_handler.setFormatter(formatter)

    # Creates a serial connection to Sim900 shield
    sim900 = Sim900(Serial(port, baudrate=baudrate, timeout=0), delay=0.5)

    # Listens for incoming SMS
    reader = SMSReader(sim900)

    # For non-pcDuino devices, there looks to be a delay before commands
    # are sent and read correctly. Waiting two seconds seems to work.
    print "Initializing serial connection..."
    sleep(2)

    print ""
    print "Sim900 SMS Data Reader"
    print "----------------------"
    print ""
    print "Press CTRL+C to stop the program."
    print ""

    print reader.init_reader()

    while True:
        text_msg = reader.listen()
        if text_msg is not None:
            logger.info("Text message received at {0}.".format(datetime.now().strftime("%m/%d/%Y %H:%M:%S")))
            logger.info(text_msg)


if __name__ == '__main__':
    main()
