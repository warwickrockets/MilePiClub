# GSM

The GSM board in use is a SIM900 based board, there is various documentation for this but the most consistent I've found is at http://www.geeetech.com/wiki/index.php/Arduino_GPRS_Shield

## Wiring

To simply set up the wiring for local usage, one can simply directly connect:

RasPi | GSM Module
:----:|:----------:
4     | VCC5
6     | GND
8     | D7
10    | D8

The jumpers on the GSM board must be set to software serial, this enables the usage of D7 for Tx and D8 for Rx.

Eventually we will want to have something connected to the power button wiring as this must currently be pressed manually.

## Initial RasPi setup

By default the RasPi is set up to output kernel debugging information over the serial port that we wish to use for communication with the GSM module.  To disable this follow the instructions at http://www.raspberrypi-spy.co.uk/2013/12/free-your-raspberry-pi-serial-port/

To use the serial port as a non-root user it may also be necessary to run `sudo chmod a+rw /dev/ttyAMA0`

If screen is not installed it can be installed using `sudo apt-get install screen`

## Manual operation

To manually send an SMS one can do the following:
- Connect the board, as specified in the Wiring section
- Boot up the RasPi
- Turn on the GSM board by pressing the power button
- Run `screen /dev/ttyAMA0 19200`
- Type in `AT+IPR=19200` and press enter to set the baud rate (this shouldn't be necessary unless it's been changed somehow)
- Type in `AT+CMGF=1` and press enter to set the communication mode to text (as opposed to binary)
- Type in `AT+CMGS="+441111222233"` and press enter to set the number to send the SMS to (replace with the number you wish to use, including country code), the console should now show a '>' to prompt for a message.
- Type in the text which you wish to send, newlines can be included in this.
- The message is ended with a hex signal of 0x1A, this can be input by pressing Ctrl+Z
- If everything has been done correctly then the SMS should be recieved within 10 seconds or so.
