from flask import Flask, render_template, jsonify
from flask import request
import requests
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

app = Flask(__name__)

# Configure the SQLite database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///visitors.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

# Initialize the database
db = SQLAlchemy(app)

# Define the Visitor model
class Visitor(db.Model):
    visitor_id = db.Column(db.String(50), primary_key=True)
    body_temperature = db.Column(db.Float, nullable=False)
    date = db.Column(db.DateTime, nullable=False)

# Create database tables if they don't exist
def create_database():
    with app.app_context():
        db.create_all()  # Creates the database and tables

# ESP8266 IP address (replace with the actual IP address)
ESP8266_IP = 'http://192.168.1.2'  # Replace with your ESP8266's IP address

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_counter', methods=['GET'])
def get_counter():
    try:
        response = requests.get(f'{ESP8266_IP}/get_counter')
        if response.status_code == 200:
            counter_value = response.text
            return jsonify({"status": "success", "counter": counter_value}), 200
        else:
            return jsonify({"status": "error", "message": "Failed to retrieve counter"}), 500
    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
        return jsonify({"status": "error", "message": str(e)}), 500
    
# @app.route('/visitor_db', methods=['GET'])
# def store_visit_history():
#     try:
#         response = requests.get(f'{ESP8266_IP}/visitor_db')
#         if response.status_code == 200:
#             print(response.text)
#             temp_value = response.text
#             new_visitor = Visitor(visitor_id=str(datetime.utcnow), body_temperature=temp_value, date=datetime.now())
#             db.session.add(new_visitor)
#             db.session.commit()
#             return jsonify({"status": "success", "counter": temp_value}), 200
#         else:
#             return jsonify({"status": "error", "message": "Failed to retrieve counter"}), 500
#     except requests.exceptions.RequestException as e:
#         print(f"Error: {e}")
#         return jsonify({"status": "error", "message": str(e)}), 500
    
@app.route('/data', methods=['POST'])
def receive_data():
    data = request.get_json()
    temp_val = data.get('Temperature')
    visitor_id = datetime.utcnow().strftime('%Y%m%d%H%M%S')
    now = datetime.utcnow()
    new_visitor = Visitor(
        visitor_id=visitor_id,
        body_temperature=temp_val,
        date=now
    )
    # Add and commit to the database
    db.session.add(new_visitor)
    try:
        db.session.commit()
        return jsonify({"status": "success"}), 201
    except Exception as e:
        db.session.rollback()  # Rollback in case of error
        return jsonify({"error": str(e)}), 500


@app.route('/entrance_servo_on', methods=['GET'])
def entrance_turn_on_servo():
    return control_servo('entrance_servo_on', "Entrance servo turned on.")

@app.route('/entrance_servo_off', methods=['GET'])
def entrance_turn_off_servo():
    return control_servo('entrance_servo_off', "Entrance servo turned off.")

@app.route('/exit_servo_on', methods=['GET'])
def exit_turn_on_servo():
    return control_servo('exit_servo_on', "Exit servo turned on.")

@app.route('/exit_servo_off', methods=['GET'])
def exit_turn_off_servo():
    return control_servo('exit_servo_off', "Exit servo turned off.")

@app.route('/laser_on', methods=['GET'])
def laser_turn_on():
    return control_device('laser_on', "Laser turned on.")

@app.route('/laser_off', methods=['GET'])
def laser_turn_off():
    return control_device('laser_off', "Laser turned off.")

@app.route('/lights_on', methods=['GET'])
def lights_turn_on():
    return control_device('lights_on', "Lights turned on.")

@app.route('/lights_off', methods=['GET'])
def lights_turn_off():
    return control_device('lights_off', "Lights turned off.")

@app.route('/history.html')
def visitor_list():
    visitors = Visitor.query.all()
    return render_template('history.html', visitors=visitors)


def control_device(action, success_message):
    """Helper function to control devices."""
    try:
        response = requests.get(f'{ESP8266_IP}/{action}')
        if response.status_code == 200:
            return jsonify({"status": "success", "message": success_message}), 200
        else:
            return jsonify({"status": "error", "message": "Failed to control device."}), 500
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": str(e)}), 500

def control_servo(action, success_message):
    """Helper function to control servos."""
    return control_device(action, success_message)

if __name__ == '__main__':
    create_database()  # Create the database and tables before running the app
    app.run(host='0.0.0.0', port=5000, debug=True)