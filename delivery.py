import os
from json import load, dumps

try:
    from requests import request
    from dotenv import dotenv_values
except:
    os.system("pip install requests")
    os.system("pip install python-dotenv")
    from requests import request
    from dotenv import dotenv_values

config = dotenv_values(".env")

url = "https://kartrace-1ea9.restdb.io/rest/teams"
headers = {
    'content-type': "application/json",
    'x-apikey': config['RESTDB_API_KEY'],
    'cache-control': "no-cache"
    }

# get data from json file
with open('web/results.json') as json_file:
    data = load(json_file)

for x in range(len(data)):
    payload = dumps( {"name": data[x]["name"], "minutes": data[x]["minutes"], "seconds": data[x]["seconds"], "miliseconds": data[x]["miliseconds"], "mean": data[x]["timeMean"].replace(",","."), "position": data[x]["position"], "created_year": data[x]["year"]} )
    response = request("POST", url, data=payload, headers=headers)
    print(f"Registro {x + 1} exportado para web com sucesso!" if response.status_code == 201 else f"Registro {x + 1} obteve falha ao ser exportado para web!")
