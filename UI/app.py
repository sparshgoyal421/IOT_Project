from flask import Flask, render_template, jsonify, request
import requests
import random
import json
import matplotlib.pyplot as plt


app = Flask(__name__)

def redGreen(cars, light):
    if light == 0:
        return 1.5 * cars
    else:
        return 0.75 * cars 

@app.route('/')
@app.route('/home')
def home():
    return render_template('home.html')

@app.route('/stats')
def stats():
    return render_template('stats.html')

@app.route('/junca')
def junca():
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-1/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["lt"]
    data = data.split("T")
    retStr = ''
    retStr += data[1][0:2]
    retStr += ":"
    retStr += data[1][2:4]
    retStr += ":"
    retStr += data[1][4:6]
    retStr += "  "
    retStr += data[0][6:8]
    retStr += "-"
    retStr += data[0][4:6]
    retStr += "-"
    retStr += data[0][0:4]
    print(data)
    return render_template('junca.html', timestamp = retStr)

@app.route('/juncb')
def juncb():
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-2/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["lt"]
    data = data.split("T")
    retStr = ''
    retStr += data[1][0:2]
    retStr += ":"
    retStr += data[1][2:4]
    retStr += ":"
    retStr += data[1][4:6]
    retStr += "  "
    retStr += data[0][6:8]
    retStr += "-"
    retStr += data[0][4:6]
    retStr += "-"
    retStr += data[0][0:4]
    print(data)
    return render_template('juncb.html', timestamp = retStr)

@app.route('/juncc')
def juncc():
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-3/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["lt"]
    data = data.split("T")
    retStr = ''
    retStr += data[1][0:2]
    retStr += ":"
    retStr += data[1][2:4]
    retStr += ":"
    retStr += data[1][4:6]
    retStr += "  "
    retStr += data[0][6:8]
    retStr += "-"
    retStr += data[0][4:6]
    retStr += "-"
    retStr += data[0][0:4]
    print(data)
    return render_template('juncc.html', timestamp = retStr)

@app.route('/juncd')
def juncd():
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-4/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["lt"]
    data = data.split("T")
    retStr = ''
    retStr += data[1][0:2]
    retStr += ":"
    retStr += data[1][2:4]
    retStr += ":"
    retStr += data[1][4:6]
    retStr += "  "
    retStr += data[0][6:8]
    retStr += "-"
    retStr += data[0][4:6]
    retStr += "-"
    retStr += data[0][0:4]
    print(data)
    return render_template('juncd.html', timestamp = retStr)

@app.route('/junce')
def junce():
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-5/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["lt"]
    data = data.split("T")
    retStr = ''
    retStr += data[1][0:2]
    retStr += ":"
    retStr += data[1][2:4]
    retStr += ":"
    retStr += data[1][4:6]
    retStr += "  "
    retStr += data[0][6:8]
    retStr += "-"
    retStr += data[0][4:6]
    retStr += "-"
    retStr += data[0][0:4]
    print(data)
    return render_template('junce.html', timestamp = retStr)

@app.route('/test', methods=["GET", "POST"])
def maps():
    weights = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-1/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    dataA = data[1:-1].split(", ")
    weights[7] = redGreen(int(dataA[0]), int(dataA[4]))
    weights[6] = redGreen(int(dataA[1]), int(dataA[5]))
    weights[12] = redGreen(int(dataA[2]), int(dataA[6]))
    weights[19] = redGreen(int(dataA[3]), int(dataA[7])) 
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-2/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    dataB = data[1:-1].split(", ")
    
    weights[1] = redGreen(int(dataB[0]), int(dataB[3]))
    weights[0] = redGreen(int(dataB[1]), int(dataB[4]))
    weights[4] = redGreen(int(dataB[2]), int(dataB[5]))
    weights[15] = redGreen(int(dataA[2]), int(dataA[5])) 
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-3/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    dataC = data[1:-1].split(", ")
    
    weights[10] = redGreen(int(dataC[2]), int(dataC[5]))
    weights[11] = redGreen(int(dataC[2]), int(dataC[5]))
    weights[17] = redGreen(int(dataC[1]), int(dataC[4]))
    weights[16] = redGreen(int(dataC[0]), int(dataC[3])) 
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-4/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    dataD = data[1:-1].split(", ")
    
    weights[19] = redGreen(int(dataD[0]), int(dataD[3]))
    weights[13] = redGreen(int(dataD[1]), int(dataD[4]))
    weights[20] = redGreen(int(dataD[2]), int(dataD[5])) 
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-5/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    dataE = data[1:-1].split(", ")
    
    weights[8] = redGreen(int(dataE[0]), int(dataE[3]))
    weights[9] = redGreen(int(dataE[1]), int(dataE[4]))
    weights[2] = redGreen(int(dataE[2]), int(dataE[5])) 
    print(weights)
    # weights
    
    if request.method == "POST":
        start = request.form.get("startString")
        start = "N" + start
        end = request.form.get("endString")
        end = "N" + end
        startEnd = []
        startEnd.append(start)
        startEnd.append(end)
        return render_template("test.html", data=weights, startEnd=startEnd)
    else:
        start = "N1"
        end = "N10"
        startEnd = []
        startEnd.append(start)
        startEnd.append(end)
        return render_template('test.html', data=weights, startEnd=startEnd)

@app.route('/dataA')
def get_dataA():
    # Generate random data for the bar graph for the traffic light status
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-1/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    # conn = sqlite3.connect('lostAndFound.db')
    # db = conn.cursor()
    
    # for con in dataResponse["m2m:cnt"]["m2m:cin"]:
    #     db.execute("INSERT INTO junction1 (road1,road2,road3,road4,signal1,signal2,signal3,signal4) VALUES (?, ?, ?, ?, ?, ?, ?, ?);", (con["con"][0], con["con"][1], con["con"][2], con["con"][3], con["con"][4], con["con"][5], con["con"][6], con["con"][7]))
         
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    data = data[1:-1].split(", ")
    
    # print(data)
    
    return jsonify(data)

@app.route('/dataB')
def get_dataB():
    # Generate random data for the bar graph for the traffic light status
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-2/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    # conn = sqlite3.connect('lostAndFound.db')
    # db = conn.cursor()
    
    # for con in dataResponse["m2m:cnt"]["m2m:cin"]:
    #     db.execute("INSERT INTO junction1 (road1,road2,road3,road4,signal1,signal2,signal3,signal4) VALUES (?, ?, ?, ?, ?, ?, ?, ?);", (con["con"][0], con["con"][1], con["con"][2], con["con"][3], con["con"][4], con["con"][5], con["con"][6], con["con"][7]))
         
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    data = data[1:-1].split(", ")
    print(data)
    return jsonify(data)

@app.route('/dataC')
def get_dataC():
    # Generate random data for the bar graph for the traffic light status
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-3/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    # conn = sqlite3.connect('lostAndFound.db')
    # db = conn.cursor()
    
    # for con in dataResponse["m2m:cnt"]["m2m:cin"]:
    #     db.execute("INSERT INTO junction1 (road1,road2,road3,road4,signal1,signal2,signal3,signal4) VALUES (?, ?, ?, ?, ?, ?, ?, ?);", (con["con"][0], con["con"][1], con["con"][2], con["con"][3], con["con"][4], con["con"][5], con["con"][6], con["con"][7]))
         
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    data = data[1:-1].split(", ")
    return jsonify(data)

@app.route('/dataD')
def get_dataD():
    # Generate random data for the bar graph for the traffic light status
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-4/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    # conn = sqlite3.connect('lostAndFound.db')
    # db = conn.cursor()
    
    # for con in dataResponse["m2m:cnt"]["m2m:cin"]:
    #     db.execute("INSERT INTO junction1 (road1,road2,road3,road4,signal1,signal2,signal3,signal4) VALUES (?, ?, ?, ?, ?, ?, ?, ?);", (con["con"][0], con["con"][1], con["con"][2], con["con"][3], con["con"][4], con["con"][5], con["con"][6], con["con"][7]))
         
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    data = data[1:-1].split(", ")
    return jsonify(data)

@app.route('/dataE')
def get_dataE():
    # Generate random data for the bar graph for the traffic light status
    
    url = "https://c0f4-218-185-248-66.ngrok-free.app/~/in-cse/in-name/Database/Junction-5/Data?rcn=4"
    payload={}
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Accept': 'application/json'
    }
    response = requests.request("GET", url, headers=headers, data=payload)
    dataResponse = eval(response.text)
    
    # conn = sqlite3.connect('lostAndFound.db')
    # db = conn.cursor()
    
    # for con in dataResponse["m2m:cnt"]["m2m:cin"]:
    #     db.execute("INSERT INTO junction1 (road1,road2,road3,road4,signal1,signal2,signal3,signal4) VALUES (?, ?, ?, ?, ?, ?, ?, ?);", (con["con"][0], con["con"][1], con["con"][2], con["con"][3], con["con"][4], con["con"][5], con["con"][6], con["con"][7]))
         
    data = dataResponse["m2m:cnt"]["m2m:cin"][-1]["con"]
    data = data[1:-1].split(", ")
    return jsonify(data)

if __name__ == '__main__':
    app.run()
