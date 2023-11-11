from time import sleep
import requests
import os

#to do 1 -> 46

headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/114.0'
}

url = "https://registroaziende.it/ateco/27.12?page="
ordering = "&ordering=-ultimo_fatturato"

subdir = "Cartella"
baseFilename = "FatturatoPagina"

#print(url+str(7)+ordering)


for i in range(1, 3):
    response = requests.get(url+str(i)+ordering, headers=headers)
    print(response)
    print("scrapping"+ url+str(i)+ordering )
    if b"Abbiamo notato" in response.content:
        print("we done being goofed")

    filename = baseFilename+str(i)+".html"
    path = os.path.join(subdir, filename)

    with open(path, mode='wb') as localfile:     
        localfile.write(response.content)

    sleep(5)




