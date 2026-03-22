import serial
import time
from flask import Flask, jsonify, render_template

app = Flask(__name__)

# Setup Serial - Update '/dev/ttyUSB0' if your port is different
try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    time.sleep(2) # Give Arduino a moment to wake up
    print("Connected to Arduino!")
except Exception as e:
    print(f"Error: {e}")

@app.route('/api/walk')
def walk():
    ser.write(b'W')
    return jsonify(status="Pedestrian Mode Triggered")

@app.route('/api/dance')
def dance():
    ser.write(b'D')
    return jsonify(status="Morse Dance Triggered")

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)