#!/bin/bash
BASE_URL='https://registroaziende.it'
ATECO_CODE='27.11'
#ATECO_CODE='35.11'
mkdir -p aziende/index
for index in {1..99} ; do
    if [[ ! -f "aziende/index/tmp-$index-$ATECO_CODE.html" ]]; then
        echo "curl $i index"
        curl -s "$BASE_URL/ateco/$ATECO_CODE?page=$index&ordering=-ultimo_fatturato"  | grep '<b class="dark-blue">' | cut -d '>' -f 2  | cut -d'<' -f 1 | awk '{print tolower($0)}'| sed 's/\ /-/g' > aziende/index/tmp-$index-$ATECO_CODE.html
    fi
    cat aziende/index/tmp-$index-$ATECO_CODE.html | while read azienda ; do
    if [[ ! -f "aziende/$azienda.html" ]]; then
        echo "curl $azienda file"
        curl -s "$BASE_URL/azienda/$azienda"> aziende/"$azienda".html
        fi

    done 
done
