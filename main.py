from flask import Flask, render_template, jsonify
import requests
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# Configure the SQLite database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///visitors.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

# Initialize the database
db = SQLAlchemy(app)

# Define the Visitor model
class Visitor(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    visitor_id = db.Column(db.String(50), nullable=False)
    body_temperature = db.Column(db.Float, nullable=False)
    date = db.Column(db.DateTime, nullable=False)

# Create database tables if they don't exist
def create_database():
    with app.app_context():
        db.create_all()  # Creates the database and tables

# ESP8266 IP address (replace with the actual IP address)
ESP8266_IP = 'http://192.168.1.6'  # Replace with your ESP8266's IP address

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/entrance_servo_on', methods=['GET'])
def entrance_turn_on_servo():
    try:
        requests.get(f'{ESP8266_IP}/entrance_servo_on')
        return jsonify({"status": "success", "message": "Entrance servo turned on."}), 200
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/entrance_servo_off', methods=['GET'])
def entrance_turn_off_servo():
    try:
        requests.get(f'{ESP8266_IP}/entrance_servo_off')
        return jsonify({"status": "success", "message": "Entrance servo turned off."}), 200
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/exit_servo_on', methods=['GET'])
def exit_turn_on_servo():
    try:
        requests.get(f'{ESP8266_IP}/exit_servo_on')
        return jsonify({"status": "success", "message": "Exit servo turned on."}), 200
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/exit_servo_off', methods=['GET'])
def exit_turn_off_servo():
    try:
        requests.get(f'{ESP8266_IP}/exit_servo_off')
        return jsonify({"status": "success", "message": "Exit servo turned off."}), 200
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/laser_on', methods=['GET'])
def laser_turn_on():
    try:
        requests.get(f'{ESP8266_IP}/laser_on')
        return jsonify({"status": "success", "message": "Laser turned on."}), 200
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/laser_off', methods=['GET'])
def laser_turn_off():
    try:
        requests.get(f'{ESP8266_IP}/laser_off')
        return jsonify({"status": "success", "message": "Laser turned off."}), 200
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    create_database()  # Create the database and tables before running the app
    app.run(debug=True)
