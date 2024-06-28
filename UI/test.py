import requests


#code to get data from thingspeak
# request = requests.get("https://api.thingspeak.com/channels/2160241/fields/1.json?api_key=A96Z3U63JEAJJ4UY&results=100")
# print(type(request.json))
# #print(request.text)
# print(request.json()['feeds'])

#code to get data from OM2M
url = "https://c499-14-139-82-6.ngrok-free.app/~/in-cse/in-name/Database/Junction-4/Data?rcn=4"
#https://2ca8-14-139-82-6.ngrok-free.app/webpage/welcome/index.html?context=/~&cseId=in-cse  
payload={}
headers = {
  'X-M2M-Origin': 'admin:admin',
  'Accept': 'application/json'
}

response = requests.request("GET", url, headers=headers, data=payload)
print(response.text)